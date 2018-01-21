
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

namespace TinNet::Optimizer::Supervised
{
	template<class LossFunc> void SupervisedOptimizerBase_GPU::train(std::size_t nEpoch)
	{
		auto nDimension{this->sNN.layer().back()->fanOut()};

		for (std::size_t nEpochCount{0}; nEpochCount < nEpoch; ++nEpochCount)
		{
			//OptimizerHelper::shuffleTrainingSet(nSize, pInput, pOutput);

			std::size_t nBatchIndex{0};

			while (nBatchIndex < this->nTrainingSize)
			{
				auto nActualBatchSize{this->nBatchSize < this->nTrainingSize - nBatchIndex ? this->nBatchSize : this->nTrainingSize - nBatchIndex};

				//Initialize the delta buffers.
				//for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
				//{
				//	std::size_t nBiasDeltaSize;
				//	std::size_t nWeightDeltaSize;
				//
				//	this->sNN[nIndex]->specifySize(nBiasDeltaSize, nWeightDeltaSize);
				//
				//	cuMemsetD32(this->sBiasDelta[nIndex], 0, this->nBatchSize * nBiasDeltaSize);
				//	cuMemsetD32(this->sWeightDelta[nIndex], 0, this->nBatchSize * nWeightDeltaSize);
				//	cuMemsetD32(this->sBackwardOutput[nIndex], 0, this->nBatchSize * this->sNN[nIndex]->fanIn());
				//}

				//Forward.
				this->sNN.forward(
					nActualBatchSize,
					this->pTrainingInput + sizeof(float) * this->sNN.layer().front()->fanIn() * nBatchIndex,
					this->sForwardOutput.data(),
					true);

				LossFunc::derivative(
					nActualBatchSize,
					nDimension,
					this->sForwardOutput.back(),
					this->pTrainingOutput + sizeof(float) * nDimension * nBatchIndex,
					this->pBackwardInput);

				//Backward.
				this->sNN.backward(
					nActualBatchSize,
					this->pTrainingInput + sizeof(float) * this->sNN.layer().front()->fanIn() * nBatchIndex,
					this->pBackwardInput,
					this->sForwardOutput.data(),
					this->sBackwardOutput.data(),
					this->sBiasDelta.data(),
					this->sWeightDelta.data());

				if (nActualBatchSize > 1)
					for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
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

				this->applyGradient(nActualBatchSize);
			}
		}
	}
}