
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
				for (auto &sLayer : this->sBiasDelta)
					for (auto &nDelta : sLayer)
						nDelta = .0f;

				for (auto &sLayer : this->sWeightDelta)
					for (auto &sWeight : sLayer)
						for (auto &nDelta : sWeight)
							nDelta = .0f;

				for (std::size_t nBatch{0}; nBatch < nActualBatchSize; ++nBatch, ++nBatchIndex)
				{
					//Forward pass.
					this->sNN.calcForTrain(sInput[nBatchIndex].data());

					//Give the backward input - derivative of the loss function.
					LossFunc::derivative(nDimension, this->sNN.output().back().data(), sOutput[nBatchIndex].data(), this->sNN.output().back().data());

					//Backward pass; accrue the gradients.
					for (std::size_t nIndex{this->sNN.depth() - 1}; ; --nIndex)
					{
						auto &sLayer{this->sNN[nIndex]};
						auto pLayerInput{nIndex == 0 ? sInput[nBatchIndex].data() : this->sNN.output()[nIndex - 1].data()};
						auto pLayerBackInput{nIndex + 1 == this->sNN.depth() ? this->sNN.output().back().data() : this->sOutput[nIndex + 1].data()};
						auto pLayerBackOutput{this->sOutput[nIndex].data()};

						sLayer.backward(pLayerBackInput, pLayerBackOutput);

						for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}; nOut < nOutSize; ++nOut)
						{
							this->sBiasDelta[nIndex][nOut] += pLayerBackInput[nOut];

							for (std::size_t nIn{0}, nInSize{sLayer.fanIn()}; nIn < nInSize; ++nIn)
								this->sWeightDelta[nIndex][nOut][nIn] += pLayerInput[nIn] * pLayerBackInput[nOut];
						}

						if (nIndex == 0)
							break;
					}
				}

				auto nFactor{-this->nLearningRate / nActualBatchSize};

				for (std::size_t nIndex{0}, nSize{this->sNN.depth()}; nIndex < nSize; ++nIndex)
					for (std::size_t nOut{0}, nOutSize{this->sNN[nIndex].fanOut()}; nOut < nOutSize; ++nOut)
					{
						this->sBiasMomentum[nIndex][nOut] = this->nMomentumTerm * this->sBiasMomentum[nIndex][nOut] + nFactor * this->sBiasDelta[nIndex][nOut];

						for (std::size_t nIn{0}, nInSize{this->sNN[nIndex].fanIn()}; nIn < nInSize; ++nIn)
							this->sWeightMomentum[nIndex][nOut][nIn] = this->nMomentumTerm * this->sWeightMomentum[nIndex][nOut][nIn] + nFactor * this->sWeightDelta[nIndex][nOut][nIn];
					}

				for (std::size_t nIndex{0}, nSize{this->sNN.depth()}; nIndex < nSize; ++nIndex)
					for (std::size_t nOut{0}, nOutSize{this->sNN[nIndex].fanOut()}; nOut < nOutSize; ++nOut)
					{
						this->sNN[nIndex].bias()[nOut] += this->sBiasMomentum[nIndex][nOut];

						for (std::size_t nIn{0}, nInSize{this->sNN[nIndex].fanIn()}; nIn < nInSize; ++nIn)
							this->sNN[nIndex].weight()[nOut][nIn] += this->sWeightMomentum[nIndex][nOut][nIn];
					}
			}
		}
	}
}