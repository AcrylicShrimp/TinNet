
/*
	2018.06.23
	Created by AcrylicShrimp.
*/

#include "TransposedConvolution.h"

namespace TinNet::GraphNode
{
	TransposedConvolution::TransposedConvolution(Graph *pGraph, const std::string &sName, NodePtr pSharingNode,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nHStride,
		std::size_t nVStride,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel) :
		VariableNode(pGraph, sName, pSharingNode),
		sInputShape{},
		sOutputShape{1, nOutputChannel, nOutputHeight, nOutputWidth},
		sOutputInternalShape{},
		sKernelShape{1, 1},
		sOutputAccessor{Shape{}},
		sInputAccessor{Shape{}},
		nKernelWidth{nKernelWidth},
		nKernelHeight{nKernelHeight},
		nHStride{nHStride},
		nVStride{nVStride}
	{
		//Empty.
	}

	Shape TransposedConvolution::shape() const
	{
		return this->sOutputShape;
	}

	std::string TransposedConvolution::type() const
	{
		return TransposedConvolution::typeName();
	}

	void TransposedConvolution::notifyShapeUpdated()
	{
		this->sInputShape = this->sInputList.front()->shape();

		if (this->sInputShape.rank() < 4)
			this->sInputShape = this->sInputShape.expand(4);

		this->sOutputShape.set(0, this->sInputShape[0]);

		if (this->sVariableSizeList.empty())
		{
			this->sKernelShape.set(0, this->sInputShape[1]);
			this->sKernelShape.set(1, this->sOutputShape[1] * this->nKernelHeight * this->nKernelWidth);
			this->sOutputInternalShape = {
				this->sKernelShape[1],
				this->sInputShape[2] * this->sInputShape[3]};

			this->nHPaddingN = this->nHPaddingP = ((this->sInputShape[3] - 1) * this->nHStride + this->nKernelWidth - this->sOutputShape[3]) / 2;
			this->nVPaddingN = this->nVPaddingP = ((this->sInputShape[2] - 1) * this->nVStride + this->nKernelHeight - this->sOutputShape[2]) / 2;

			if (this->nHPaddingN + this->nHPaddingP != (this->sInputShape[3] - 1) * this->nHStride + this->nKernelWidth - this->sOutputShape[3])
				++this->nHPaddingP;

			if (this->nVPaddingN + this->nVPaddingP != (this->sInputShape[2] - 1) * this->nVStride + this->nKernelHeight - this->sOutputShape[2])
				++this->nVPaddingP;

			this->sOutput.resize(this->sOutputInternalShape.element());
			this->sOutputIndexList.reserve(this->sOutputInternalShape.element());
			this->sOutputCache = this->sOutput;

			for (std::size_t nInputY{0}; nInputY < this->sInputShape[2]; ++nInputY)
			{
				auto nOutputBaseY{nInputY * this->nVStride};

				for (std::size_t nInputX{0}; nInputX < this->sInputShape[3]; ++nInputX)
				{
					auto nOutputBaseX{nInputX * this->nHStride};

					for (std::size_t nChannelOut{0}; nChannelOut < this->sOutputShape[1]; ++nChannelOut)
					{
						auto nOutputChannelOffset{nChannelOut * this->sOutputShape[2] * this->sOutputShape[3]};

						for (std::size_t nKernelY{0}; nKernelY < this->nKernelHeight; ++nKernelY)
						{
							auto nOutputY{nOutputBaseY + nKernelY};

							for (std::size_t nKernelX{0}; nKernelX < this->nKernelWidth; ++nKernelX)
							{
								auto nOutputX{nOutputBaseX + nKernelX};

								std::size_t nOutputIndex;

								if (nOutputY < this->nVPaddingN)
									nOutputIndex = 0;
								else if (nOutputY >= this->nVPaddingN + this->sOutputShape[2])
									nOutputIndex = 0;
								else if (nOutputX < this->nHPaddingN)
									nOutputIndex = 0;
								else if (nOutputX >= this->nHPaddingN + this->sOutputShape[3])
									nOutputIndex = 0;
								else
									nOutputIndex = nOutputChannelOffset + (nOutputY - this->nVPaddingN) * this->sOutputShape[3] + nOutputX - this->nHPaddingN + 1;

								this->sOutputIndexList.emplace_back(nOutputIndex);
							}
						}
					}
				}
			}

			this->registerVariable(this->sOutputShape[1]);
			this->registerVariable(this->sKernelShape.element());
		}

		this->sInputAccessor = this->sInputShape;
		this->sOutputAccessor = this->sOutputShape;

		Shape sResultShape{this->sKernelShape[0], this->sOutputInternalShape[1]};
		this->sIterator.init(sResultShape, Accessor{sResultShape}, Accessor{this->sKernelShape}, Accessor{this->sOutputInternalShape});

		this->VariableNode::notifyShapeUpdated();
	}

	std::size_t TransposedConvolution::fanIn() const
	{
		return this->sInputShape[1] * this->sInputShape[2] * this->sInputShape[3];
	}

	std::size_t TransposedConvolution::fanOut() const
	{
		return this->sOutputShape[1] * this->sOutputShape[2] * this->sOutputShape[3];
	}

	void TransposedConvolution::initialize(std::function<float()> fInitializer)
	{
		this->sVariableList.front()->sCache.zero();

		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.back()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.back()->sCache[nIndex] = fInitializer();
	}

	void TransposedConvolution::variablePass()
	{
		auto sBatchInput{this->sInputList.front()->forward()};
		auto sBatchGradient{this->backward()};

		this->sVariableGradientList.front()->sCache.zero();
		this->sVariableGradientList.back()->sCache.zero();

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			auto sGradient{sBatchGradient + this->sOutputAccessor(nBatch, 0, 0, 0)};

			for (std::size_t nIndex{0}, nMaxIndex{this->sOutputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sOutputIndexList[nIndex])
					this->sOutputCache[nIndex] = sGradient[this->sOutputIndexList[nIndex] - 1];
				else
					this->sOutputCache[nIndex] = .0f;

			GraphOp::dMatmulAccumulateLeftTransposedAVX(
				this->sKernelShape,
				this->sOutputInternalShape,
				sBatchInput + this->sInputAccessor(nBatch, 0, 0, 0),
				this->sOutputCache,
				this->sVariableGradientList.back()->sCache,
				this->sIterator
			);

			for (std::size_t nFilter{0}, nMaxFilter{this->sOutputShape[1]}; nFilter < nMaxFilter; ++nFilter)
			{
				auto sFilterGradient{sBatchGradient + this->sOutputAccessor(nBatch, nFilter, 0, 0)};

				for (std::size_t nIndex{0}, nMaxIndex{this->sOutputShape[2] * this->sOutputShape[3]}; nIndex < nMaxIndex; ++nIndex)
					this->sVariableGradientList.front()->sCache[nFilter] += sFilterGradient[nIndex];
			}
		}
	}

	void TransposedConvolution::applyGradient(float nFactor)
	{
		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.front()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.front()->sCache[nIndex] += nFactor * this->sVariableGradientList.front()->sCache[nIndex];

		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.back()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.back()->sCache[nIndex] += nFactor * this->sVariableGradientList.back()->sCache[nIndex];
	}

	void TransposedConvolution::forwardPass(Cache sDestination)
	{
		auto sBatchInput{this->sInputList.front()->forward()};

		sDestination.zero();

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			GraphOp::dMatmulRightTransposedAVX(
				this->sKernelShape,
				this->sOutputInternalShape,
				sBatchInput + this->sInputAccessor(nBatch, 0, 0, 0),
				this->sVariableList.back()->sCache,
				this->sOutputCache,
				this->sIterator
			);

			auto sDest{sDestination + this->sOutputAccessor(nBatch, 0, 0, 0)};

			for (std::size_t nIndex{0}, nMaxIndex{this->sOutputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sOutputIndexList[nIndex])
					sDest[this->sOutputIndexList[nIndex] - 1] += this->sOutputCache[nIndex];

			for (std::size_t nFilter{0}, nMaxFilter{this->sOutputShape[1]}; nFilter < nMaxFilter; ++nFilter)
			{
				auto nBias{this->sVariableList.front()->sCache[nFilter]};
				auto sFilterDest{sDestination + this->sOutputAccessor(nBatch, nFilter, 0, 0)};

				for (std::size_t nIndex{0}, nMaxIndex{this->sOutputShape[2] * this->sOutputShape[3]}; nIndex < nMaxIndex; ++nIndex)
					sFilterDest[nIndex] += nBias;
			}
		}
	}

	void TransposedConvolution::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sBatchGradient{this->backward()};

		for (std::size_t nBatch{0}, nMaxBatch{this->sInputShape[0]}; nBatch < nMaxBatch; ++nBatch)
		{
			auto sGradient{sBatchGradient + this->sOutputAccessor(nBatch, 0, 0, 0)};

			this->sOutputCache.zero();

			for (std::size_t nIndex{0}, nMaxIndex{this->sOutputIndexList.size()}; nIndex < nMaxIndex; ++nIndex)
				if (this->sOutputIndexList[nIndex])
					this->sOutputCache[nIndex] = sGradient[this->sOutputIndexList[nIndex] - 1];
				else
					this->sOutputCache[nIndex] = .0f;

			GraphOp::matmulAccumulateTransposedAVX(
				this->sKernelShape,
				this->sOutputInternalShape,
				this->sVariableList.back()->sCache,
				this->sOutputCache,
				sDestination + this->sInputAccessor(nBatch, 0, 0, 0),
				this->sIterator
			);
		}
	}
}