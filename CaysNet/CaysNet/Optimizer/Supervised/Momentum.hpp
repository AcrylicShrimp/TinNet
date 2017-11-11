
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

namespace CaysNet::Optimizer::Supervised
{
	template<class LossFunc> void Momentum::train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch)
	{
		assert(sInput.size() == sOutput.size());
		assert(!sInput.empty());

		auto nDimension{sOutput.front().size()};

		for (std::size_t nEpochCount{0}; nEpochCount < nEpoch; ++nEpochCount)
		{
			//Shuffle the input/output vector.
			for (std::size_t nRand{0}, nSize{sInput.size() - 1}; nRand < nSize; ++nRand)
			{
				auto nIndex = std::uniform_int_distribution<std::size_t>{nRand + 1, nSize}(this->sEngine);

				sInput[nRand].swap(sInput[nIndex]);
				sOutput[nRand].swap(sOutput[nIndex]);
			}

			std::size_t nBatchIndex{0};

			while (nBatchIndex < sInput.size())
			{
				std::size_t nActualBatchSize{sInput.size() - nBatchIndex > nBatchSize ? nBatchSize : sInput.size() - nBatchIndex};

				//Initialize the delta buffers.
				for (auto &sBias : this->sBiasDelta)
					for (auto &nBias : sBias)
						nBias = .0f;

				for (auto &sWeight : this->sWeightDelta)
					for (auto &nWeight : sWeight)
						nWeight = .0f;

				for (std::size_t nBatch{0}; nBatch < nActualBatchSize; ++nBatch, ++nBatchIndex)
				{
					//Forward pass.
					this->sNN.forward(sInput[nBatchIndex].data(), this->sActivationInput, this->sActivationOutput);

					//Give the backward input - derivative of the loss function.
					LossFunc::derivative(nDimension, this->sNN.output().back().data(), sOutput[nBatchIndex].data(), this->sNN.output().back().data());

					//Backward pass.
					this->sNN.backward(
						this->sActivationInput,
						this->sActivationOutput,
						this->sBiasDeltaBuffer,
						this->sWeightDeltaBuffer,
						this->sBackward,
						sInput[nBatchIndex].data(),
						this->sNN.output().back().data());

					for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
					{
						for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasDelta[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
							this->sBiasDelta[nIndex][nBiasIndex] += this->sBiasDeltaBuffer[nIndex][nBiasIndex];

						for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightDelta[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
							this->sWeightDelta[nIndex][nWeightIndex] += this->sWeightDeltaBuffer[nIndex][nWeightIndex];
					}
				}

				auto nFactor{-this->nLearningRate / nActualBatchSize};

				for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
				{
					for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasDelta[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
						this->sBiasMomentum[nIndex][nBiasIndex] = this->nMomentumTerm * this->sBiasMomentum[nIndex][nBiasIndex] + nFactor * this->sBiasDelta[nIndex][nBiasIndex];

					for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightDelta[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
						this->sWeightMomentum[nIndex][nWeightIndex] = this->nMomentumTerm * this->sWeightMomentum[nIndex][nWeightIndex] + nFactor * this->sWeightDelta[nIndex][nWeightIndex];
				}

				for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
					this->sNN[nIndex]->update(this->sBiasMomentum[nIndex].data(), this->sWeightMomentum[nIndex].data());
			}
		}
	}
}