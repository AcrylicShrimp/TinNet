
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

namespace CaysNet::Optimizer
{
	template<class LossFunc> SGD<LossFunc>::SGD(NN<LossFunc> &sNN, float nNewLearningRate) :
		nLearningRate{nNewLearningRate},
		sNN{sNN},
		sDeltaList(sNN.depth()),
		sLossDelta(sNN.output().back().size()),
		sInputAverage(sNN[0].fanIn(), .0f),
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
			sDeltaList[nIndex].resize(this->sNN[nIndex].fanOut(), .0f);
	}

	template<class LossFunc> SGD<LossFunc>::SGD(SGD &&sSrc) :
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sDeltaList{std::move(sSrc.sDeltaList)},
		sLossDelta{std::move(sSrc.sLossDelta)},
		sInputAverage{std::move(sSrc.sInputAverage)},
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
				for (auto &nIn : this->sInputAverage)
					nIn = .0f;

				for (auto &sDelta : this->sDeltaList)
					for (auto &nDelta : sDelta)
						nDelta = .0f;

				for (auto &nDelta : this->sLossDelta)
					nDelta = .0f;

				for (std::size_t nBatch{0}; nBatch < nActualBatchSize; ++nBatch, ++nBatchIndex)
				{
					for (std::size_t nIndex{0}, nSize{this->sInputAverage.size()}; nIndex < nSize; ++nIndex)
						this->sInputAverage[nIndex] += sInput[nBatchIndex][nIndex];

					//Forward pass.
					this->sNN.calc(sInput[nBatchIndex].data());

					//Give the backward input - derivative of the loss function.
					LossFunc::derivative(nDimension, this->sNN.output().back().data(), sOutput[nBatchIndex].data(), this->sDeltaList.back().data());

					//Accrue the loss gradients.
					for (std::size_t nIndex{0}, nSize{this->sLossDelta.size()}; nIndex < nSize; ++nIndex)
						this->sLossDelta[nIndex] += this->sDeltaList.back()[nIndex];

					//Backward pass; accrue the gradients.
					for (std::size_t nIndex{this->sNN.depth() - 1}; nIndex > 0; --nIndex)
						this->sNN[nIndex].backward(this->sNN.output()[nIndex].data(), this->sDeltaList[nIndex].data(), this->sDeltaList[nIndex - 1].data());
				}

				auto nFactor{1.f / nActualBatchSize};

				for (auto &nIn : this->sInputAverage)
					nIn *= nFactor;

				//Take the average of the gradients.
				for (std::size_t nIndex{0}, nSize{this->sDeltaList.size() - 1}; nIndex < nSize; ++nIndex)
					for (auto &nDelta : this->sDeltaList[nIndex])
						nDelta *= this->nLearningRate * nFactor;

				for (auto &nDelta : this->sLossDelta)
					nDelta *= this->nLearningRate * nFactor;

				//Update the weights and biases.
				{
					auto &sLastLayer{this->sNN.layer().back()};
					auto &sWeight{sLastLayer.weight()};
					auto &sBias{sLastLayer.bias()};
					auto pInput{this->sNN.depth() >= 2 ? this->sNN.output()[this->sNN.depth() - 1].data() : this->sInputAverage.data()};

					for (std::size_t nOut{0}, nOutSize{sLastLayer.fanOut()}; nOut < nOutSize; ++nOut)
					{
						//b = b - delta
						sBias[nOut] -= sLastLayer.activation()->derivative(sLastLayer.output()[nOut], this->sNN.output().back()[nOut]) * this->sLossDelta[nOut];

						//w = w - in * delta
						//TODO : multiply derivation of the activation function here.
						for (std::size_t nIn{0}, nInSize{sLastLayer.fanIn()}; nIn < nInSize; ++nIn)
							sWeight[nOut][nIn] -= pInput[nIn] * sLastLayer.activation()->derivative(sLastLayer.output()[nOut], this->sNN.output().back()[nOut]) * this->sLossDelta[nOut];
					}
				}

				for (std::size_t nIndex{1}, nSize{this->sNN.depth() - 1}; nIndex < nSize; ++nIndex)
				{
					auto &sLayer{this->sNN.layer().front()};
					auto &sWeight{sLayer.weight()};
					auto &sBias{sLayer.bias()};
					auto pInput{this->sNN.output()[nIndex - 1].data()};

					for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}; nOut < nOutSize; ++nOut)
					{
						//b = b - delta
						sBias[nOut] -= sLayer.activation()->derivative(sLayer.output()[nOut], this->sNN.output()[nIndex][nOut]) * this->sDeltaList[nIndex][nOut];

						//w = w - in * delta
						for (std::size_t nIn{0}, nInSize{sLayer.fanIn()}; nIn < nInSize; ++nIn)
							sWeight[nOut][nIn] -= pInput[nIn] * sLayer.activation()->derivative(sLayer.output()[nOut], this->sNN.output().front()[nOut]) * this->sDeltaList[nIndex][nOut];
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
						sBias[nOut] -= sFirstLayer.activation()->derivative(sFirstLayer.output()[nOut], this->sNN.output().front()[nOut]) * this->sDeltaList.front()[nOut];

						//w = w - in * delta
						for (std::size_t nIn{0}, nInSize{sFirstLayer.fanIn()}; nIn < nInSize; ++nIn)
							sWeight[nOut][nIn] -= pInput[nIn] * sFirstLayer.activation()->derivative(sFirstLayer.output()[nOut], this->sNN.output().front()[nOut]) * this->sDeltaList.front()[nOut];
					}
				}
			}
		}
	}
}