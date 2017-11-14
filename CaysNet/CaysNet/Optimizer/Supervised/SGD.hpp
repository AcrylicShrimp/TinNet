
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

namespace CaysNet::Optimizer::Supervised
{
	template<class LossFunc> void SGD::train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch)
	{
		assert(sInput.size() == sOutput.size());
		assert(!sInput.empty());

		std::vector<std::vector<std::vector<float>>> sOutputBuffer(nBatchSize);
		std::vector<std::vector<std::vector<float>>> sActivationInput(nBatchSize);
		std::vector<std::vector<std::vector<float>>> sActivationOutput(nBatchSize);
		std::vector<std::vector<std::vector<float>>> sBackwardBuffer(nBatchSize);
		std::vector<std::vector<float>> sBackwardInput(nBatchSize);

		const auto nLayerSize{this->sNN.layer().size()};

		for (std::size_t nIndex{0}; nIndex < nBatchSize; ++nIndex)
		{
			sOutputBuffer[nIndex].resize(nLayerSize);
			sActivationInput[nIndex].resize(nLayerSize);
			sActivationOutput[nIndex].resize(nLayerSize);
			sBackwardBuffer[nIndex].resize(nLayerSize);
			sBackwardInput[nIndex].resize(this->sNN.layer().back()->fanOut());

			for (std::size_t nLayerIndex{0}; nLayerIndex < nLayerSize; ++nLayerIndex)
			{
				sOutputBuffer[nIndex][nLayerIndex].resize(this->sNN[nLayerIndex]->fanOut());
				sActivationInput[nIndex][nLayerIndex].resize(this->sNN[nLayerIndex]->fanOut());
				sActivationOutput[nIndex][nLayerIndex].resize(this->sNN[nLayerIndex]->fanOut());
				sBackwardBuffer[nIndex][nLayerIndex].resize(this->sNN[nLayerIndex]->fanIn());
			}
		}

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
				auto nActualBatchSize{sInput.size() - nBatchIndex > nBatchSize ? nBatchSize : sInput.size() - nBatchIndex};

				//Initialize the delta buffers.
				for (auto &sBias : this->sBiasDelta)
					for (auto &nBias : sBias)
						nBias = .0f;

				for (auto &sWeight : this->sWeightDelta)
					for (auto &nWeight : sWeight)
						nWeight = .0f;

				this->sNN.forward(nBatchIndex, nActualBatchSize, sInput, sOutputBuffer, sActivationInput, sActivationOutput);

				for (std::size_t nIndex{0}; nIndex < nActualBatchSize; ++nIndex)
					LossFunc::derivative(nDimension, sOutputBuffer[nIndex].back().data(), sOutput[nIndex + nBatchIndex].data(), sBackwardInput[nIndex].data());

				this->sNN.backward(
					nBatchIndex,
					nActualBatchSize,
					sOutputBuffer,
					sActivationInput,
					sActivationOutput,
					this->sBiasDelta,
					this->sWeightDelta,
					sBackwardBuffer,
					sInput,
					sBackwardInput);

				nBatchIndex += nActualBatchSize;

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