
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

namespace TinNet::Optimizer
{
	template<class LossFunc> void OptimizerBase_GPU::train(std::size_t nEpoch, std::size_t nSize, GPUVector &sInput, GPUVector &sOutput)
	{
		auto nInputDimension{sInput.size() / nSize};
		auto nOutputDimension{sOutput.size() / nSize};

		for (std::size_t nEpochCount{0}; nEpochCount < nEpoch; ++nEpochCount)
		{
			//OptimizerHelper::shuffleTrainingSet(nSize, pInput, pOutput);

			std::size_t nBatchIndex{0};

			while (nBatchIndex < nSize)
			{
				auto nActualBatchSize{(std::min)(this->nBatchSize, nSize - nBatchIndex)};

				//Initialize the delta buffers.
				for (std::size_t nIndex{0}, nSize{this->sNN.depth()}; nIndex < nSize; ++nIndex)
				{
					this->sBiasDelta[nIndex].zero();
					this->sWeightDelta[nIndex].zero();
					this->sBackwardOutput[nIndex].zero();
				}

				//Forward.
				this->sNN.forward(
					nInputDimension * nBatchIndex,
					nActualBatchSize,
					sInput,
					this->sForwardOutput.data(),
					true);

				LossFunc::derivative(
					nOutputDimension * nBatchIndex,
					nActualBatchSize,
					nOutputDimension,
					this->sForwardOutput.back(),
					sOutput,
					this->sBackwardInput);

				//Backward.
				this->sNN.backward(
					nInputDimension * nBatchIndex,
					nActualBatchSize,
					sInput,
					this->sBackwardInput,
					this->sForwardOutput.data(),
					this->sBackwardOutput.data(),
					this->sBiasDelta.data(),
					this->sWeightDelta.data());

				if (nActualBatchSize > 1)
					for (std::size_t nIndex{0}, nSize{this->sNN.depth()}; nIndex < nSize; ++nIndex)
					{
						std::size_t nBiasDeltaSize;
						std::size_t nWeightDeltaSize;

						this->sNN[nIndex]->specifySize(nBiasDeltaSize, nWeightDeltaSize);

						if (nBiasDeltaSize)
							::mergeBatch(nActualBatchSize, nBiasDeltaSize, this->sBiasDelta[nIndex], this->sBiasDelta[nIndex]);

						if (nWeightDeltaSize)
							::mergeBatch(nActualBatchSize, nWeightDeltaSize, this->sWeightDelta[nIndex], this->sWeightDelta[nIndex]);
					}

				nBatchIndex += nActualBatchSize;

				this->applyGradient(nActualBatchSize, 1.f);
			}
		}
	}
}