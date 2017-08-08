
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

			this->sBiasDelta[nIndex].resize(sLayer.fanOut(), .0f);
			this->sWeightDelta[nIndex].resize(sLayer.fanOut());

			for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}, nInSize{sLayer.fanIn()}; nOut < nOutSize; ++nOut)
				this->sWeightDelta[nIndex][nOut].resize(nInSize, .0f);
		}
	}

	template<class LossFunc> SGD<LossFunc>::SGD(SGD &&sSrc) :
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
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
					//Forward pass.
					this->sNN.calc(sInput[nBatchIndex].data());

					//Give the backward input - derivative of the loss function.
					LossFunc::derivative(nDimension, this->sNN.output().back().data(), sOutput[nBatchIndex].data(), this->sNN.output().back().data());

					//Backward pass; accrue the gradients.
					for (std::size_t nIndex{this->sNN.depth() - 1}; nIndex >= 0; --nIndex)
					{
						auto &sLayer{this->sNN[nIndex]};
						auto pLayerBackOutput{nIndex == 0 ? nullptr : this->sNN.output()[nIndex - 1].data()};

						//FIX : Make copy of the outputs.
						sLayer.backward(this->sNN.output()[nIndex].data(), pLayerBackOutput);


					}

					this->sNN.layer().back().backward(this->sLossDelta.data(), this->sBiasDeltaBuffer.back());

					for (std::size_t nOut{0}, nOutSize{this->sNN.layer().back().fanOut()}; nOut < nOutSize; ++nOut)
					{
						this->sBiasDelta[nOut] += this->sBiasDeltaBuffer[nOut];

						auto &sLayerInput{this->sNN.depth() > 1 ? this->sNN.output()[this->sNN.depth() - 2] : sInput[nBatchIndex]};

						for (std::size_t nIn{0}, nInSize{this->sNN.layer().back().fanIn()}; nIn < nInSize; ++nIn)
							this->sWeightDelta.back()[nOut][nIn] += sLayerInput[nIn] * this->sBiasDeltaBuffer[nOut];
					}

					if (this->sNN.depth() > 2)
						for (std::size_t nIndex{this->sNN.depth() - 2}; nIndex > 0; --nIndex)
						{
							auto &sLayer{this->sNN[nIndex]};

							sLayer.backward(this->sBiasDeltaBuffer[nIndex + 1].data(), this->sBiasDeltaBuffer[nIndex].data());



						}
				}

				auto nFactor{this->nLearningRate / nActualBatchSize};

				//Update the weights and biases.
				{
					auto &sLastLayer{this->sNN.layer().back()};
					auto &sWeight{sLastLayer.weight()};
					auto &sBias{sLastLayer.bias()};
					auto pInput{this->sNN.depth() >= 2 ? this->sNN.output()[this->sNN.depth() - 2].data() : this->sInputAverage.data()};

					for (std::size_t nOut{0}, nOutSize{sLastLayer.fanOut()}; nOut < nOutSize; ++nOut)
					{
						//b = b - delta
						sBias[nOut] -= sLastLayer.derivative()[nOut] * this->sLossDelta[nOut];

						//w = w - in * delta
						//TODO : multiply derivation of the activation function here.
						for (std::size_t nIn{0}, nInSize{sLastLayer.fanIn()}; nIn < nInSize; ++nIn)
							sWeight[nOut][nIn] -= pInput[nIn] * sLastLayer.derivative()[nOut] * this->sLossDelta[nOut];
					}
				}

				for (std::size_t nIndex{1}, nSize{this->sNN.depth() - 1}; nIndex < nSize; ++nIndex)
				{
					auto &sLayer{this->sNN[nIndex]};
					auto &sWeight{sLayer.weight()};
					auto &sBias{sLayer.bias()};
					auto pInput{this->sNN.output()[nIndex - 1].data()};

					for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}; nOut < nOutSize; ++nOut)
					{
						//b = b - delta
						sBias[nOut] -= sLayer.derivative()[nOut] * this->sDeltaList[nIndex][nOut];

						//w = w - in * delta
						for (std::size_t nIn{0}, nInSize{sLayer.fanIn()}; nIn < nInSize; ++nIn)
							sWeight[nOut][nIn] -= pInput[nIn] * sLayer.derivative()[nOut] * this->sDeltaList[nIndex][nOut];
					}
				}

				if (this->sNN.depth() > 1)
				{
					auto &sFirstLayer{this->sNN.layer().front()};
					auto &sWeight{sFirstLayer.weight()};
					auto &sBias{sFirstLayer.bias()};
					auto pInput{this->sInputAverage.data()};

					for (std::size_t nOut{0}, nOutSize{sFirstLayer.fanOut()}; nOut < nOutSize; ++nOut)
					{
						//b = b - delta
						sBias[nOut] -= sFirstLayer.derivative()[nOut] * this->sDeltaList.front()[nOut];

						//w = w - in * delta
						for (std::size_t nIn{0}, nInSize{sFirstLayer.fanIn()}; nIn < nInSize; ++nIn)
							sWeight[nOut][nIn] -= pInput[nIn] * sFirstLayer.derivative()[nOut] * this->sDeltaList.front()[nOut];
					}
				}
			}
		}
	}
}