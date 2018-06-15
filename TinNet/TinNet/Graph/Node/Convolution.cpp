
/*
	2018.06.09
	Created by AcrylicShrimp.
*/

#include "Convolution.h"

namespace TinNet::Graph::Node
{
	Convolution::Convolution(const std::string &sName, Graph *pGraph,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nHStride,
		std::size_t nVStride,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel) :
		VariableGraphNode(sName, pGraph),
		sInputShape{},
		sInputInternalShape{},
		sOutputShape{1, nOutputChannel, nOutputHeight, nOutputWidth},
		sKernelShape{nOutputChannel, nKernelHeight * nKernelWidth},
		sInputAccessor{Shape{}},
		sResultAccessor{Shape{}},
		nKernelWidth{nKernelWidth},
		nKernelHeight{nKernelHeight},
		nHStride{nHStride},
		nVStride{nVStride}
	{
		//Empty.
	}

	const Shape &Convolution::shape() const
	{
		return this->sOutputShape;
	}

	std::size_t Convolution::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Convolution::initNode()
	{
		if (!this->sVariableSizeList.empty())
			return;

		if ((this->sInputShape = this->sBackwardList.front()->shape()).rank() > 4)
			throw std::invalid_argument("dimension too high");

		if (this->sInputShape.rank() < 4)
			this->sInputShape = this->sInputShape.expand(4);

		this->sOutputShape.set(0, this->sInputShape[0]);
		this->sKernelShape.set(1, this->sInputShape[1] * this->sKernelShape[1]);
		this->sInputInternalShape = {
			this->sKernelShape[1],
			this->sOutputShape[2] * this->sOutputShape[3]};

		this->nHPaddingN = this->nHPaddingP = ((this->sOutputShape[3] - 1) * this->nHStride + this->nKernelWidth - this->sInputShape[3]) / 2;
		this->nVPaddingN = this->nVPaddingP = ((this->sOutputShape[2] - 1) * this->nVStride + this->nKernelHeight - this->sInputShape[2]) / 2;

		if (this->nHPaddingN + this->nHPaddingP != (this->sOutputShape[3] - 1) * this->nHStride + this->nKernelWidth - this->sInputShape[3])
			++this->nHPaddingP;

		if (this->nVPaddingN + this->nVPaddingP != (this->sOutputShape[2] - 1) * this->nVStride + this->nKernelHeight - this->sInputShape[2])
			++this->nVPaddingP;

		this->sInputAccessor = this->sInputShape;
		this->sResultAccessor = Shape{this->sInputShape[0], this->sKernelShape[0], this->sInputInternalShape[1]};

		Shape sResultShape{this->sKernelShape[0], this->sInputInternalShape[1]};
		this->sIterator.init(sResultShape, Accessor{sResultShape}, Accessor{this->sKernelShape}, Accessor{this->sInputInternalShape});

		this->sInputIndexList.reserve(this->sInputInternalShape.element());

		for (std::size_t nOutputY{0}; nOutputY < this->sOutputShape[2]; ++nOutputY)
		{
			auto nInputBaseY{nOutputY * this->nVStride};

			for (std::size_t nOutputX{0}; nOutputX < this->sOutputShape[3]; ++nOutputX)
			{
				auto nInputBaseX{nOutputX * this->nHStride};

				for (std::size_t nChannelIn{0}; nChannelIn < this->sInputShape[1]; ++nChannelIn)
				{
					auto nInputChannelOffset{nChannelIn * this->sInputShape[2] * this->sInputShape[3]};

					for (std::size_t nKernelY{0}; nKernelY < this->nKernelHeight; ++nKernelY)
					{
						auto nInputY{nInputBaseY + nKernelY};

						for (std::size_t nKernelX{0}; nKernelX < this->nKernelWidth; ++nKernelX)
						{
							auto nInputX{nInputBaseX + nKernelX};

							std::size_t nInputIndex;

							if (nInputY < this->nVPaddingN)
								nInputIndex = 0;
							else if (nInputY >= this->nVPaddingN + this->sInputShape[2])
								nInputIndex = 0;
							else if (nInputX < this->nHPaddingN)
								nInputIndex = 0;
							else if (nInputX >= this->nHPaddingN + this->sInputShape[3])
								nInputIndex = 0;
							else
								nInputIndex = nInputChannelOffset + (nInputY - this->nVPaddingN) * this->sInputShape[3] + nInputX - this->nHPaddingN + 1;

							this->sInputIndexList.emplace_back(nInputIndex);
						}
					}
				}
			}
		}

		this->variable(this->sInputInternalShape.element());
		this->variable(this->sKernelShape.element());
		this->variable(this->sOutputShape[1]);
	}

	void Convolution::forwardPass(Cache sDestination)
	{
		auto sBatchForward{this->sBackwardList.front()->forward()};

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			auto sForward{sBatchForward + this->sInputAccessor(nBatch, 0, 0, 0)};

			for (std::size_t nIndex{0}, nMaxIndex{this->sInputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sInputIndexList[nIndex])
					this->sVariableList[0]->sCache[nIndex] = sForward[this->sInputIndexList[nIndex] - 1];
				else
					this->sVariableList[0]->sCache[nIndex] = .0f;

			GraphOp::matmulTransposedAVX(
				this->sKernelShape,
				this->sInputInternalShape,
				this->sVariableList[1]->sCache,
				this->sVariableList[0]->sCache,
				sDestination + this->sResultAccessor(nBatch, 0, 0),
				this->sIterator
			);

			for (std::size_t nFilter{0}, nMaxFilter{this->sOutputShape[1]}; nFilter < nMaxFilter; ++nFilter)
			{
				auto sFilterDest{sDestination + this->sResultAccessor(nBatch, nFilter, 0)};

				for (std::size_t nIndex{0}, nMaxIndex{this->sInputInternalShape[1]}; nIndex < nMaxIndex; ++nIndex)
					sFilterDest[nIndex] += this->sVariableList[2]->sCache[nFilter];
			}
		}
	}

	void Convolution::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.zero();

		auto sBatchBackward{this->backward()};

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			GraphOp::dMatmulRightTransposedAVX(
				this->sKernelShape,
				this->sInputInternalShape,
				sBatchBackward + this->sResultAccessor(nBatch, 0, 0),
				this->sVariableList[1]->sCache,
				this->sVariableList[0]->sCache,
				this->sIterator
			);

			auto sDest{sDestination + this->sInputAccessor(nBatch, 0, 0, 0)};

			for (std::size_t nIndex{0}, nMaxIndex{this->sInputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sInputIndexList[nIndex])
					sDest[this->sInputIndexList[nIndex] - 1] += this->sVariableList[0]->sCache[nIndex];
		}
	}

	std::size_t Convolution::fanIn() const
	{
		return this->sInputShape[1] * this->sInputShape[2] * this->sInputShape[3];
	}

	std::size_t Convolution::fanOut() const
	{
		return this->sOutputShape[1] * this->sOutputShape[2] * this->sOutputShape[3];
	}

	void Convolution::backwardVariablePass()
	{
		this->sVariableBackwardList[1]->sCache.zero();
		this->sVariableBackwardList[2]->sCache.zero();

		auto sBatchForward{this->sBackwardList.front()->forward()};
		auto sBatchBackward{this->backward()};

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			auto sForward{sBatchForward + this->sInputAccessor(nBatch, 0, 0, 0)};

			for (std::size_t nIndex{0}, nMaxIndex{this->sInputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sInputIndexList[nIndex])
					this->sVariableList[0]->sCache[nIndex] = sForward[this->sInputIndexList[nIndex] - 1];
				else
					this->sVariableList[0]->sCache[nIndex] = .0f;

			GraphOp::dMatmulAccumulateLeftTransposedAVX(
				this->sKernelShape,
				this->sInputInternalShape,
				sBatchBackward + this->sResultAccessor(nBatch, 0, 0),
				this->sVariableList[0]->sCache,
				this->sVariableBackwardList[1]->sCache,
				this->sIterator
			);

			for (std::size_t nFilter{0}, nMaxFilter{this->sOutputShape[1]}; nFilter < nMaxFilter; ++nFilter)
			{
				auto sFilterBackward{sBatchBackward + this->sResultAccessor(nBatch, nFilter, 0)};

				for (std::size_t nIndex{0}, nMaxIndex{this->sInputInternalShape[1]}; nIndex < nMaxIndex; ++nIndex)
					this->sVariableBackwardList[2]->sCache[nFilter] += sFilterBackward[nIndex];
			}
		}
	}
}