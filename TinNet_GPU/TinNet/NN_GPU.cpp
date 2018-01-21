
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#include "NN_GPU.h"

namespace TinNet
{
	NN_GPU::~NN_GPU()
	{
		for (auto pOutput : this->sOutput)
			cuMemFree(pOutput);

		this->sOutput.clear();
	}

	void NN_GPU::forward(const float *pInput, float *pOutput)
	{
		CUdeviceptr pGPUInput;

		cuMemAlloc(&pGPUInput, sizeof(float) * this->sLayerList.front()->fanIn());
		cuMemcpyHtoD(pGPUInput, pInput, sizeof(float) * this->sLayerList.front()->fanIn());

		this->forward(pGPUInput);

		cuMemcpyDtoH(pOutput, this->sOutput.back(), sizeof(float) * this->sLayerList.back()->fanOut());
		cuMemFree(pGPUInput);
	}

	void NN_GPU::forward(CUdeviceptr pInput)
	{
		this->sLayerList.front()->forward(pInput, this->sOutput.front());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(this->sOutput[nIndex - 1], this->sOutput[nIndex]);
	}

	void NN_GPU::forward(
		std::size_t nBatchSize,
		CUdeviceptr pInput,
		const CUdeviceptr *pOutput,
		bool bTrainingPhase) const
	{
		this->sLayerList.front()->forward(nBatchSize, pInput, pOutput[0], bTrainingPhase);

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(nBatchSize, pOutput[nIndex - 1], pOutput[nIndex], bTrainingPhase);
	}

	void NN_GPU::backward(
		std::size_t nBatchSize,
		CUdeviceptr pForwardInput,
		CUdeviceptr pBackwardInput,
		const CUdeviceptr *pForwardOutput,
		const CUdeviceptr *pBackwardOutput,
		const CUdeviceptr *pBiasDelta,
		const CUdeviceptr *pWeightDelta)
	{
		for (std::size_t nIndex{this->sLayerList.size() - 1}; ; --nIndex)
		{
			const auto &pLayer{this->sLayerList[nIndex]};
			const auto pLayerForwardInput{nIndex == 0 ? pForwardInput : pForwardOutput[nIndex - 1]};
			const auto pLayerBackwardInput{nIndex + 1 == this->depth() ? pBackwardInput : pBackwardOutput[nIndex + 1]};
			auto pLayerBackwardOutput{pBackwardOutput[nIndex]};

			pLayer->backward(
				nBatchSize,
				pLayerForwardInput,
				pLayerBackwardInput,
				pLayerBackwardOutput,
				pBiasDelta[nIndex],
				pWeightDelta[nIndex]);

			if (!nIndex)
				break;
		}
	}
}