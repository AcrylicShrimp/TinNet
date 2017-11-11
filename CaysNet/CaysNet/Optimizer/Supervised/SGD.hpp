
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

namespace CaysNet::Optimizer::Supervised
{
	//template<class LossFunc> std::pair<float, float> SGD::calcNumericalGradient(const std::vector<float> &sInput, const std::vector<float> &sOutput, std::size_t nLayerIndex, std::size_t nInputIndex, std::size_t nOutputIndex)
	//{
	//	constexpr auto nEpsilon{1e-3f};
	//
	//	float nWeight{this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex]};
	//	
	//	this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight + nEpsilon;
	//	float nFirst{this->sNN.loss<LossFunc>(sInput.data(), sOutput.data())};
	//
	//	this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight - nEpsilon;
	//	float nSecond{this->sNN.loss<LossFunc>(sInput.data(), sOutput.data())};
	//
	//	float nFirstGradient{(nFirst - nSecond) / (2.f * nEpsilon)};
	//
	//	this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight;
	//
	//	//Forward pass.
	//	this->sNN.calcForTrain(sInput.data());
	//
	//	//Give the backward input - derivative of the loss function.
	//	LossFunc::derivative(sOutput.size(), this->sNN.output().back().data(), sOutput.data(), this->sNN.output().back().data());
	//
	//	//Backward pass; accrue the gradients.
	//	for (std::size_t nIndex{this->sNN.depth() - 1}; ; --nIndex)
	//	{
	//		auto pLayer{this->sNN[nIndex]};
	//		auto pLayerInput{nIndex == 0 ? sInput.data() : this->sNN.output()[nIndex - 1].data()};
	//		auto pLayerBackInput{nIndex + 1 == this->sNN.depth() ? this->sNN.output().back().data() : this->sOutput[nIndex + 1].data()};
	//		auto pLayerBackOutput{this->sOutput[nIndex].data()};
	//
	//		pLayer->backward(pLayerBackInput, pLayerBackOutput);
	//
	//		for (std::size_t nOut{0}, nOutSize{pLayer->fanOut()}; nOut < nOutSize; ++nOut)
	//		{
	//			this->sBiasDelta[nIndex][nOut] = pLayerBackInput[nOut];
	//
	//			for (std::size_t nIn{0}, nInSize{pLayer->fanIn()}; nIn < nInSize; ++nIn)
	//				this->sWeightDelta[nIndex][nOut][nIn] = pLayerInput[nIn] * pLayerBackInput[nOut];
	//		}
	//
	//		if (nIndex == 0)
	//			break;
	//	}
	//
	//	float nSecondGradient{this->sWeightDelta[nLayerIndex][nOutputIndex][nInputIndex]};
	//
	//	return std::make_pair(nFirstGradient, nSecondGradient);
	//}

	template<class LossFunc> void SGD::train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch)
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

				for (auto &sBias : this->sBiasDelta)
					for (auto &nBias : sBias)
						nBias *= nFactor;

				for (auto &sWeight : this->sWeightDelta)
					for (auto &nWeight : sWeight)
						nWeight *= nFactor;

				for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
					this->sNN[nIndex]->update(this->sBiasDelta[nIndex].data(), this->sWeightDelta[nIndex].data());
			}
		}
	}
}