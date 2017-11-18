
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

namespace CaysNet::Optimizer::Supervised
{
	template<class LossFunc> std::pair<float, float> SGD::calcNumericalGradient(const std::vector<float> &sInput, const std::vector<float> &sOutput, std::size_t nLayerIndex, std::size_t nOutIndex, std::size_t nInIndex)
	{
		auto pLayer{reinterpret_cast<Layer::FullLayer *>(this->sNN[nLayerIndex])};
		auto &nWeight = pLayer->weight()[nOutIndex][nInIndex];
		auto nOriginal = nWeight;

		nWeight = nOriginal + 1e-3f;
		auto nFirstLoss = this->sNN.loss<LossFunc>(sInput.data(), sOutput.data());

		nWeight = nOriginal - 1e-3f;
		auto nSecondLoss = this->sNN.loss<LossFunc>(sInput.data(), sOutput.data());

		auto nFirstGradient{(nFirstLoss - nSecondLoss) / 2e-3f};

		nWeight = nOriginal;

		for (auto &sBias : this->sBiasDelta)
			std::fill(sBias.begin(), sBias.end(), .0f);

		for (auto &sWeight : this->sWeightDelta)
			std::fill(sWeight.begin(), sWeight.end(), .0f);

		this->sNN.forward(
			1,
			&sInput,
			this->sForwardOutput.data(),
			this->sActivationInput.data(),
			this->sActivationOutput.data());

		LossFunc::derivative(
			sOutput.size(),
			this->sForwardOutput.back().front().data(),
			sOutput.data(),
			this->sForwardOutput.back().front().data());

		this->sNN.backward(
			1,
			&sInput,
			this->sForwardOutput.back().data(),
			this->sForwardOutput.data(),
			this->sActivationInput.data(),
			this->sActivationOutput.data(),
			this->sBiasDelta.data(),
			this->sWeightDelta.data(),
			this->sBiasDeltaBuffer.data(),
			this->sBackwardOutput.data());

		auto nSecondGradient{this->sWeightDelta[nLayerIndex][nOutIndex * pLayer->fanIn() + nInIndex]};

		return std::make_pair(nFirstGradient, nSecondGradient);
	}

	template<class LossFunc> void SGD::train(std::size_t nEpoch, std::size_t nSize, std::vector<float> *pInput, std::vector<float> *pOutput)
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
				auto nActualBatchSize{std::min(this->nBatchSize, nSize - nBatchIndex)};

				//Initialize the delta buffers.
				for (auto &sBias : this->sBiasDelta)
					std::fill(sBias.begin(), sBias.end(), .0f);

				for (auto &sWeight : this->sWeightDelta)
					std::fill(sWeight.begin(), sWeight.end(), .0f);

				//Forward.
				this->sNN.forward(
					nActualBatchSize,
					pInput + nBatchIndex,
					this->sForwardOutput.data(),
					this->sActivationInput.data(),
					this->sActivationOutput.data());

				for (std::size_t nIndex{0}; nIndex < nActualBatchSize; ++nIndex)
					LossFunc::derivative(
						nDimension,
						this->sForwardOutput.back()[nIndex].data(),
						pOutput[nBatchIndex + nIndex].data(),
						this->sForwardOutput.back()[nIndex].data());

				//Backward.
				this->sNN.backward(
					nActualBatchSize,
					pInput + nBatchIndex,
					this->sForwardOutput.back().data(),
					this->sForwardOutput.data(),
					this->sActivationInput.data(),
					this->sActivationOutput.data(),
					this->sBiasDelta.data(),
					this->sWeightDelta.data(),
					this->sBiasDeltaBuffer.data(),
					this->sBackwardOutput.data());

				nBatchIndex += nActualBatchSize;

				const auto nFactor{-this->nLearningRate / nActualBatchSize};

				for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
					this->sNN[nIndex]->update(nFactor, this->sBiasDelta[nIndex].data(), this->sWeightDelta[nIndex].data());
			}
		}
	}
}