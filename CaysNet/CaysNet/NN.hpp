
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

namespace CaysNet
{
	template<class Initializer, class ...InitializerParam> void NN::initWeight(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto pLayer : this->sLayerList)
			sInitialier.initializeWeight(*pLayer);
	}

	template<class Initializer, class ...InitializerParam> void NN::initBias(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto pLayer : this->sLayerList)
			sInitialier.initializeBias(*pLayer);
	}

	template<class LossFunc> float NN::loss(const float *pInput, const float *pOutput)
	{
		assert(this->sLayerList.size());

		this->forward(pInput);

		return LossFunc::loss(this->sOutput.back().size(), this->sOutput.back().data(), pOutput);
	}

	template<class LossFunc> float NN::loss(std::size_t nBatchSize, const std::vector<float> *pInput, const std::vector<float> *pOutput)
	{
		assert(this->sLayerList.size());

		std::size_t nIndex{0};
		std::vector<std::vector<std::vector<float>>> sOutput(this->depth());

		for (auto &sLayerBuffer : sOutput)
		{
			sLayerBuffer.resize(nBatchSize);

			for (auto &sOutputBuffer : sLayerBuffer)
				sOutputBuffer.resize(this->sLayerList[nIndex]->fanOut());

			++nIndex;
		}

		this->forward(nBatchSize, pInput, sOutput.data());

		auto nLossSum{.0f};

		for (std::size_t nBatch{0u}; nBatch < nBatchSize; ++nBatch)
			nLossSum += LossFunc::loss(sOutput.back()[nBatch].size(), sOutput.back()[nBatch].data(), pOutput[nBatch].data());

		//Take average of the loss.
		return nLossSum / nBatchSize;
	}
}