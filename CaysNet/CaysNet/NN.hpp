
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
		this->forward(pInput);

		return LossFunc::loss(this->sOutput.back().size(), this->sOutput.back().data(), pOutput);
	}

	template<class LossFunc> float NN::loss(std::size_t nBatchSize, const std::vector<float> *pInput, const std::vector<float> *pOutput)
	{
		std::size_t nIndex{0};
		std::vector<std::vector<std::vector<float>>> sOutput(this->sLayerList.size());

		for (auto &sOutputBuffer : sOutput)
		{
			sOutputBuffer.resize(nBatchSize);

			for (auto &sLayerBuffer : sOutputBuffer)
				sLayerBuffer.resize(this->sLayerList[nIndex]->fanOut());

			++nIndex;
		}

		this->forward(nBatchSize, pInput, sOutput.data());

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}; nIndex < nBatchSize; ++nIndex)
			nLossSum += LossFunc::loss(sOutput.back()[nIndex].size(), sOutput.back()[nIndex].data(), pOutput[nIndex]);

		//Take average of the loss.
		return nLossSum / nBatchSize;
	}
}