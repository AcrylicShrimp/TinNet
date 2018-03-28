
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#include "NN_GPU.h"

namespace TinNet
{
	void NN_GPU::forward(const GPUVector &sInput)
	{
		this->sLayerList.front()->forward(sInput, this->sOutput.front());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(this->sOutput[nIndex - 1], this->sOutput[nIndex]);
	}

	void NN_GPU::forward(const GPUVector &sInput, GPUVector &sOutput)
	{
		this->forward(sInput);

		sOutput = this->sOutput.back();
	}

	void NN_GPU::forward(
		std::size_t nBatchSize,
		const GPUVector &sInput,
		GPUVector *pOutput,
		bool bTrainingPhase) const
	{
		this->sLayerList.front()->forward(0, nBatchSize, sInput, *pOutput, bTrainingPhase);

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(0, nBatchSize, pOutput[nIndex - 1], pOutput[nIndex], bTrainingPhase);
	}

	void NN_GPU::forward(
		std::size_t nIndex,
		std::size_t nBatchSize,
		const GPUVector &sInput,
		GPUVector *pOutput,
		bool bTrainingPhase) const
	{
		this->sLayerList.front()->forward(nIndex, nBatchSize, sInput, *pOutput, bTrainingPhase);

		for (std::size_t nLayer{1}, nSize{this->sLayerList.size()}; nLayer < nSize; ++nLayer)
			this->sLayerList[nLayer]->forward(0, nBatchSize, pOutput[nLayer - 1], pOutput[nLayer], bTrainingPhase);
	}

	void NN_GPU::backward(
		std::size_t nIndex,
		std::size_t nBatchSize,
		const GPUVector &sForwardInput,
		const GPUVector &sBackwardInput,
		const GPUVector *pForwardOutput,
		GPUVector *pBackwardOutput,
		GPUVector *pBiasDelta,
		GPUVector *pWeightDelta) const
	{
		for (std::size_t nLayer{this->sLayerList.size() - 1}; ; --nLayer)
		{
			const auto &pLayer{this->sLayerList[nLayer]};
			const auto &sLayerForwardInput{nLayer == 0 ? sForwardInput : pForwardOutput[nLayer - 1]};
			const auto &sLayerBackwardInput{nLayer + 1 == this->depth() ? sBackwardInput : pBackwardOutput[nLayer + 1]};
			auto &sLayerBackwardOutput{pBackwardOutput[nLayer]};

			pLayer->backward(
				nLayer == 0 ? nIndex : 0,
				nBatchSize,
				sLayerForwardInput,
				sLayerBackwardInput,
				sLayerBackwardOutput,
				pBiasDelta[nLayer],
				pWeightDelta[nLayer]);

			if (!nLayer)
				break;
		}
	}

	std::size_t NN_GPU::classify(const GPUVector &sInput)
	{
		this->forward(sInput);

		auto sResult{this->sOutput.back().to()};

		std::size_t nMaxIndex{0};
		auto nMaxValue{sResult[0]};

		for (std::size_t nOut{1}, nOutSize{sResult.size()}; nOut < nOutSize; ++nOut)
			if (nMaxValue < sResult[nOut])
				nMaxValue = sResult[nMaxIndex = nOut];

		return nMaxIndex;
	}

	void NN_GPU::classify(std::size_t nBatchSize, const GPUVector *pInput, std::size_t *pOutput)
	{
		std::vector<float> sResult(this->sOutput.back().size());

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
		{
			this->forward(pInput[nBatch]);

			this->sOutput.back().to(sResult);

			std::size_t nMaxIndex{0};
			auto nMaxValue{sResult[0]};

			for (std::size_t nOut{1}, nOutSize{sResult.size()}; nOut < nOutSize; ++nOut)
				if (nMaxValue < sResult[nOut])
					nMaxValue = sResult[nMaxIndex = nOut];

			pOutput[nBatch] = nMaxIndex;
		}
	}

	float NN_GPU::classificationLoss(std::size_t nBatchSize, const GPUVector *pInput, const GPUVector *pOutput)
	{
		std::vector<std::size_t> sResult(nBatchSize);
		this->classify(nBatchSize, pInput, sResult.data());

		auto nResult{.0f};

		for (std::size_t nIndex{0u}; nIndex < nBatchSize; ++nIndex)
			nResult += pOutput[nIndex][sResult[nIndex]];

		return 1.f - nResult / nBatchSize;
	}
}