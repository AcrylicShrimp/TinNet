
/*
	2018.06.23
	Created by AcrylicShrimp.
*/

#include "DilatedConvolution.h"

namespace TinNet::GraphNode
{
	DilatedConvolution::DilatedConvolution(Graph *pGraph, const std::string &sName,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nHDilation,
		std::size_t nVDilation,
		std::size_t nHStride,
		std::size_t nVStride,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel) :
		VariableNode(pGraph, sName),
		sInputShape{},
		sInputInternalShape{},
		sOutputShape{1, nOutputChannel, nOutputHeight, nOutputWidth},
		sKernelShape{nOutputChannel, 1},
		sInputAccessor{Shape{}},
		sResultAccessor{Shape{}},
		nKernelWidth{nKernelWidth},
		nKernelHeight{nKernelHeight},
		nHDilation{nHDilation},
		nVDilation{nVDilation},
		nHStride{nHStride},
		nVStride{nVStride}
	{
		//Empty.
	}

	const Shape &DilatedConvolution::shape() const
	{
		return this->sOutputShape;
	}

	std::string DilatedConvolution::type() const
	{
		return DilatedConvolution::typeName();
	}

	void DilatedConvolution::notifyShapeUpdated()
	{
		this->sInputShape = this->sInputList.front()->shape();

		if (this->sInputShape.rank() < 4)
			this->sInputShape = this->sInputShape.expand(4);

		this->sOutputShape.set(0, this->sInputShape[0]);

		if (this->sVariableSizeList.empty())
		{
			this->sKernelShape.set(1, this->sInputShape[1] * this->nKernelHeight * this->nKernelWidth);
			this->sInputInternalShape = {
				this->sKernelShape[1],
				this->sOutputShape[2] * this->sOutputShape[3]};

			this->nHPaddingN = this->nHPaddingP = ((this->sOutputShape[3] - 1) * this->nHStride + (this->nKernelWidth - 1) * this->nHDilation + 1 - this->sInputShape[3]) / 2;
			this->nVPaddingN = this->nVPaddingP = ((this->sOutputShape[2] - 1) * this->nVStride + (this->nKernelHeight - 1) * this->nVDilation + 1 - this->sInputShape[2]) / 2;

			if (this->nHPaddingN + this->nHPaddingP != (this->sOutputShape[3] - 1) * this->nHStride + (this->nKernelWidth - 1) * this->nHDilation + 1 - this->sInputShape[3])
				++this->nHPaddingP;

			if (this->nVPaddingN + this->nVPaddingP != (this->sOutputShape[2] - 1) * this->nVStride + (this->nKernelHeight - 1) * this->nVDilation + 1 - this->sInputShape[2])
				++this->nVPaddingP;

			this->sInput.resize(this->sInputInternalShape.element());
			this->sInputIndexList.reserve(this->sInputInternalShape.element());
			this->sInputCache = this->sInput;

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
							auto nInputY{nInputBaseY + nKernelY * this->nVDilation};

							for (std::size_t nKernelX{0}; nKernelX < this->nKernelWidth; ++nKernelX)
							{
								auto nInputX{nInputBaseX + nKernelX * this->nHDilation};

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

			this->registerVariable(this->sOutputShape[1]);
			this->registerVariable(this->sKernelShape.element());
		}

		this->sInputAccessor = this->sInputShape;
		this->sResultAccessor = Shape{this->sInputShape[0], this->sKernelShape[0], this->sInputInternalShape[1]};

		Shape sResultShape{this->sKernelShape[0], this->sInputInternalShape[1]};
		this->sIterator.init(sResultShape, Accessor{sResultShape}, Accessor{this->sKernelShape}, Accessor{this->sInputInternalShape});

		this->VariableNode::notifyShapeUpdated();
	}

	std::size_t DilatedConvolution::fanIn() const
	{
		return this->sInputShape[1] * this->sInputShape[2] * this->sInputShape[3];
	}

	std::size_t DilatedConvolution::fanOut() const
	{
		return this->sOutputShape[1] * this->sOutputShape[2] * this->sOutputShape[3];
	}

	void DilatedConvolution::initialize(std::function<float()> fInitializer)
	{
		this->sVariableList.front()->sCache.zero();

		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.back()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.back()->sCache[nIndex] = fInitializer();
	}

	void DilatedConvolution::variablePass()
	{
		auto sBatchForward{this->sInputList.front()->forward()};
		auto sBatchGradient{this->backward()};

		this->sVariableGradientList.front()->sCache.zero();
		this->sVariableGradientList.back()->sCache.zero();

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			auto sForward{sBatchForward + this->sInputAccessor(nBatch, 0, 0, 0)};

			for (std::size_t nIndex{0}, nMaxIndex{this->sInputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sInputIndexList[nIndex])
					this->sInputCache[nIndex] = sForward[this->sInputIndexList[nIndex] - 1];
				else
					this->sInputCache[nIndex] = .0f;

			GraphOp::dMatmulAccumulateLeftTransposedAVX(
				this->sKernelShape,
				this->sInputInternalShape,
				sBatchGradient + this->sResultAccessor(nBatch, 0, 0),
				this->sInputCache,
				this->sVariableGradientList.back()->sCache,
				this->sIterator
			);

			for (std::size_t nFilter{0}, nMaxFilter{this->sOutputShape[1]}; nFilter < nMaxFilter; ++nFilter)
			{
				auto sFilterGradient{sBatchGradient + this->sResultAccessor(nBatch, nFilter, 0)};

				for (std::size_t nIndex{0}, nMaxIndex{this->sInputInternalShape[1]}; nIndex < nMaxIndex; ++nIndex)
					this->sVariableGradientList.front()->sCache[nFilter] += sFilterGradient[nIndex];
			}
		}
	}

	void DilatedConvolution::applyGradient(float nFactor)
	{
		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.front()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.front()->sCache[nIndex] += nFactor * this->sVariableGradientList.front()->sCache[nIndex];

		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.back()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.back()->sCache[nIndex] += nFactor * this->sVariableGradientList.back()->sCache[nIndex];
	}

	void DilatedConvolution::forwardPass(Cache sDestination)
	{
		auto sBatchForward{this->sInputList.front()->forward()};

		sDestination.zero();

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			auto sForward{sBatchForward + this->sInputAccessor(nBatch, 0, 0, 0)};

			for (std::size_t nIndex{0}, nMaxIndex{this->sInputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sInputIndexList[nIndex])
					this->sInputCache[nIndex] = sForward[this->sInputIndexList[nIndex] - 1];
				else
					this->sInputCache[nIndex] = .0f;

			GraphOp::matmulAccumulateTransposedAVX(
				this->sKernelShape,
				this->sInputInternalShape,
				this->sVariableList.back()->sCache,
				this->sInputCache,
				sDestination + this->sResultAccessor(nBatch, 0, 0),
				this->sIterator
			);

			for (std::size_t nFilter{0}, nMaxFilter{this->sOutputShape[1]}; nFilter < nMaxFilter; ++nFilter)
			{
				auto nBias{this->sVariableList.front()->sCache[nFilter]};
				auto sFilterDest{sDestination + this->sResultAccessor(nBatch, nFilter, 0)};

				for (std::size_t nIndex{0}, nMaxIndex{this->sInputInternalShape[1]}; nIndex < nMaxIndex; ++nIndex)
					sFilterDest[nIndex] += nBias;
			}
		}
	}

	void DilatedConvolution::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sBatchGradient{this->backward()};

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			GraphOp::dMatmulRightTransposedAVX(
				this->sKernelShape,
				this->sInputInternalShape,
				sBatchGradient + this->sResultAccessor(nBatch, 0, 0),
				this->sVariableList.back()->sCache,
				this->sInputCache,
				this->sIterator
			);

			auto sDest{sDestination + this->sInputAccessor(nBatch, 0, 0, 0)};

			for (std::size_t nIndex{0}, nMaxIndex{this->sInputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sInputIndexList[nIndex])
					sDest[this->sInputIndexList[nIndex] - 1] += this->sInputCache[nIndex];
		}
	}
}