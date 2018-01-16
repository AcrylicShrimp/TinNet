
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

namespace TinNet::Optimizer::Supervised
{
	template<class LossFunc> void SupervisedOptimizerBase::train(std::size_t nEpoch, std::size_t nSize, std::vector<float> *pInput, std::vector<float> *pOutput)
	{
		auto nDimension{pOutput->size()};

		for (std::size_t nEpochCount{0}; nEpochCount < nEpoch; ++nEpochCount)
		{
			OptimizerHelper::shuffleTrainingSet(nSize, pInput, pOutput);

			std::size_t nBatchIndex{0};

			while (nBatchIndex < nSize)
			{
				auto nActualBatchSize{std::min(this->nBatchSize, nSize - nBatchIndex)};

				//Initialize the delta buffers.
				OptimizerHelper::zeros(this->sBiasDelta);
				OptimizerHelper::zeros(this->sWeightDelta);
				OptimizerHelper::zeros(this->sBackwardOutput);

				//Forward.
				this->sNN.forward(
					nActualBatchSize,
					pInput + nBatchIndex,
					this->sForwardOutput.data(),
					true);

				for (std::size_t nBatch{0}; nBatch < nActualBatchSize; ++nBatch)
					LossFunc::derivative(
					nDimension,
					this->sForwardOutput.back()[nBatch].data(),
					pOutput[nBatchIndex + nBatch].data(),
					this->sBackwardInput[nBatch].data());

				//Backward.
				this->sNN.backward(
					nActualBatchSize,
					pInput + nBatchIndex,
					this->sBackwardInput.data(),
					this->sForwardOutput.data(),
					this->sBackwardOutput.data(),
					this->sBiasDelta.data(),
					this->sWeightDelta.data());

				nBatchIndex += nActualBatchSize;

				this->applyGradient(nActualBatchSize);
			}
		}
	}
}