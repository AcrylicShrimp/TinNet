
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

namespace CaysNet::Optimizer::Supervised
{
	template<class LossFunc> void Momentum::train(std::size_t nEpoch, std::size_t nSize, std::vector<float> *pInput, std::vector<float> *pOutput)
	{
		auto nDimension{pOutput->size()};

		for (std::size_t nEpochCount{0}; nEpochCount < nEpoch; ++nEpochCount)
		{
			//Shuffle the input/output vector.
			for (std::size_t nRand{0}, nRandSize{nSize - 1}; nRand < nRandSize; ++nRand)
			{
				auto nIndex = std::uniform_int_distribution<std::size_t>{nRand + 1, nRandSize}(this->sEngine);

				pInput[nRand].swap(pInput[nIndex]);
				pOutput[nRand].swap(pOutput[nIndex]);
			}

			std::size_t nBatchIndex{0};

			while (nBatchIndex < nSize)
			{
				std::size_t nActualBatchSize{std::min(this->nBatchSize, nSize - nBatchIndex)};

				//Initialize the delta buffers.
				for (auto &sBias : this->sBiasDelta)
					std::fill(sBias.begin(), sBias.end(), .0f);

				for (auto &sWeight : this->sWeightDelta)
					std::fill(sWeight.begin(), sWeight.end(), .0f);

				//Forward pass.
				this->sNN.forward(nActualBatchSize, pInput + nBatchIndex, this->sForwardOutput.data(), this->sActivationInput.data(), this->sActivationOutput.data());

				//Give the backward input - derivative of the loss function.
				for (std::size_t nBatch{0}; nBatch < nActualBatchSize; ++nBatch)
					LossFunc::derivative(nDimension, this->sForwardOutput.back()[nBatch].data(), pOutput[nBatchIndex + nBatch].data(), this->sForwardOutput.back()[nBatch].data());

				//Backward pass.
				this->sNN.backward(
					nActualBatchSize,
					pInput + nBatchIndex,
					this->sForwardOutput.back().data(),
					this->sForwardOutput.data(),
					this->sBackwardOutput.data(),
					this->sActivationInput.data(),
					this->sActivationOutput.data(),
					this->sBiasDelta.data(),
					this->sWeightDelta.data(),
					this->sBiasDeltaBuffer.data());

				nBatchIndex += nActualBatchSize;

				auto nFactor{-this->nLearningRate / nActualBatchSize};

				for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
				{
					for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasMomentum[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
						this->sBiasMomentum[nIndex][nBiasIndex] = this->nMomentumTerm * this->sBiasMomentum[nIndex][nBiasIndex] + nFactor * this->sBiasDelta[nIndex][nBiasIndex];

					for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightMomentum[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
						this->sWeightMomentum[nIndex][nWeightIndex] = this->nMomentumTerm * this->sWeightMomentum[nIndex][nWeightIndex] + nFactor * this->sWeightDelta[nIndex][nWeightIndex];
				}

				for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
					this->sNN[nIndex]->update(this->sBiasMomentum[nIndex].data(), this->sWeightMomentum[nIndex].data());
			}
		}
	}
}