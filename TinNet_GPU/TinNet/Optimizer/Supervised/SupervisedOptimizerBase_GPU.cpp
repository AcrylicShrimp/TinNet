
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#include "SupervisedOptimizerBase_GPU.h"

namespace TinNet::Optimizer::Supervised
{
	SupervisedOptimizerBase_GPU::SupervisedOptimizerBase_GPU(NN_GPU &sNN, std::size_t nNewBatchSize) :
		sNN{sNN},
		nBatchSize{nNewBatchSize},
		nTrainingSize{0u},
		sBiasDelta(sNN.depth(), 0),
		sWeightDelta(sNN.depth(), 0),
		sForwardOutput(sNN.depth(), 0),
		sBackwardOutput(sNN.depth(), 0),
		pTrainingInput{0},
		pTrainingOutput{0}
	{
		cuMemAlloc(&this->pBackwardInput, sizeof(float) * nNewBatchSize * this->sNN.layer().back()->fanOut());

		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			const auto &pLayer{this->sNN[nIndex]};

			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			pLayer->specifySize(nBiasDeltaSize, nWeightDeltaSize);

			cuMemAlloc(&this->sBiasDelta[nIndex], sizeof(float) * nNewBatchSize * nBiasDeltaSize);
			cuMemAlloc(&this->sWeightDelta[nIndex], sizeof(float) * nNewBatchSize * nWeightDeltaSize);
			cuMemAlloc(&this->sForwardOutput[nIndex], sizeof(float) * nNewBatchSize * pLayer->fanOut());
			cuMemAlloc(&this->sBackwardOutput[nIndex], sizeof(float) * nNewBatchSize * pLayer->fanIn());
		}
	}
	
	SupervisedOptimizerBase_GPU::~SupervisedOptimizerBase_GPU()
	{
		for (auto pBiasDelta : this->sBiasDelta)
			cuMemFree(pBiasDelta);

		for (auto pWeightDelta : this->sWeightDelta)
			cuMemFree(pWeightDelta);

		for (auto pForwardOutput : this->sForwardOutput)
			cuMemFree(pForwardOutput);

		for (auto pBackwardOutput : this->sBackwardOutput)
			cuMemFree(pBackwardOutput);

		cuMemFree(pBackwardInput);

		if (this->pTrainingInput)
			cuMemFree(this->pTrainingInput);

		if (this->pTrainingOutput)
			cuMemFree(this->pTrainingOutput);

		this->sBiasDelta.clear();
		this->sWeightDelta.clear();
		this->sForwardOutput.clear();
		this->sBackwardOutput.clear();
		this->pBackwardInput = 0;
		this->pTrainingInput = 0;
		this->pTrainingOutput = 0;
	}

	void SupervisedOptimizerBase_GPU::addTrainingSet(std::size_t nSetSize, const std::vector<float> *pInput, const std::vector<float> *pOutput)
	{
		if (this->pTrainingInput)
			cuMemFree(this->pTrainingInput);

		if (this->pTrainingOutput)
			cuMemFree(this->pTrainingOutput);

		this->nTrainingSize = nSetSize;

		const auto nInputSize{sizeof(float) * this->sNN.layer().front()->fanIn()};
		const auto nOutputSize{sizeof(float) * this->sNN.layer().back()->fanOut()};

		cuMemAlloc(&this->pTrainingInput, nSetSize * nInputSize);
		cuMemAlloc(&this->pTrainingOutput, nSetSize * nOutputSize);

		for (std::size_t nIndex{0}; nIndex < nSetSize; ++nIndex)
		{
			cuMemcpyHtoD(this->pTrainingInput + nInputSize * nIndex, pInput[nIndex].data(), nInputSize);
			cuMemcpyHtoD(this->pTrainingOutput + nOutputSize * nIndex, pOutput[nIndex].data(), nOutputSize);
		}
	}
}