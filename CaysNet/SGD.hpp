
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

namespace CaysNet::Optimizer
{
	template<class LossFunc> SGD<LossFunc>::SGD(NN<LossFunc> &sNN, float nNewLearningRate) :
		nLearningRate{nNewLearningRate},
		sNN{sNN},
		sOutput(sNN.depth()),
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			auto &sLayer{this->sNN[nIndex]};

			this->sOutput[nIndex].resize(sLayer.fanIn(), .0f);
			this->sBiasDelta[nIndex].resize(sLayer.fanOut(), .0f);
			this->sWeightDelta[nIndex].resize(sLayer.fanOut());

			for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}, nInSize{sLayer.fanIn()}; nOut < nOutSize; ++nOut)
				this->sWeightDelta[nIndex][nOut].resize(nInSize, .0f);
		}
	}

	template<class LossFunc> SGD<LossFunc>::SGD(SGD &&sSrc) :
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sOutput{std::move(sSrc.sOutput)},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}

	template<class LossFunc> std::pair<float, float> SGD<LossFunc>::calcNumericalGradient(const std::vector<float> &sInput, const std::vector<float> &sOutput, std::size_t nLayerIndex, std::size_t nInputIndex, std::size_t nOutputIndex)
	{
		constexpr auto nEpsilon{1e-5f};

		float nWeight{this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex]};
		
		this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight + nEpsilon;
		float nFirst{this->sNN.loss(sInput.data(), sOutput.data())};

		this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight - nEpsilon;
		float nSecond{this->sNN.loss(sInput.data(), sOutput.data())};

		float nFirstGradient{(nFirst - nSecond) / (2.f * nEpsilon)};

		this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight;

		//Forward pass.
		this->sNN.calc(sInput.data());

		//Give the backward input - derivative of the loss function.
		LossFunc::derivative(sOutput.size(), this->sNN.output().back().data(), sOutput.data(), this->sNN.output().back().data());

		//Backward pass; accrue the gradients.
		for (std::size_t nIndex{this->sNN.depth() - 1}; ; --nIndex)
		{
			auto &sLayer{this->sNN[nIndex]};
			auto pLayerInput{nIndex == 0 ? sInput.data() : this->sNN.output()[nIndex - 1].data()};
			auto pLayerBackInput{nIndex + 1 == this->sNN.depth() ? this->sNN.output().back().data() : this->sOutput[nIndex + 1].data()};
			auto pLayerBackOutput{this->sOutput[nIndex].data()};

			sLayer.backward(pLayerBackInput, pLayerBackOutput);

			for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}; nOut < nOutSize; ++nOut)
			{
				this->sBiasDelta[nIndex][nOut] = pLayerBackInput[nOut];

				for (std::size_t nIn{0}, nInSize{sLayer.fanIn()}; nIn < nInSize; ++nIn)
					this->sWeightDelta[nIndex][nOut][nIn] = pLayerInput[nIn] * pLayerBackInput[nOut];
			}

			if (nIndex == 0)
				break;
		}

		float nSecondGradient{this->sWeightDelta[nLayerIndex][nOutputIndex][nInputIndex]};

		return std::make_pair(nFirstGradient, nSecondGradient);
	}

	template<class LossFunc> void SGD<LossFunc>::train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch)
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
					if (std::isnan(this->sNN.output().back()[0]))
					{
						int a = 10;
						printf("WTF %d", a);
					}

					//Forward pass.
					this->sNN.calc(sInput[nBatchIndex].data());
					
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
						this->sNN[nIndex].bias()[nOut] += nFactor * this->sBiasDelta[nIndex][nOut];

						for (std::size_t nIn{0}, nInSize{this->sNN[nIndex].fanIn()}; nIn < nInSize; ++nIn)
							this->sNN[nIndex].weight()[nOut][nIn] += nFactor * this->sWeightDelta[nIndex][nOut][nIn];
					}
			}
		}
	}
}