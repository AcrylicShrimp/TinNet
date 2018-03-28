
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

namespace TinNet
{
	template<class NewLayer, class ...NewLayerInitializerParam> void NN::addLayer(NewLayerInitializerParam && ...sParam)
	{
		this->sLayerList.emplace_back(std::make_unique<NewLayer>(std::forward<NewLayerInitializerParam>(sParam)...));
		this->sOutput.emplace_back(this->sLayerList.back()->fanOut(), .0f);
	}

	template<class Initializer, class ...InitializerParam> void NN::initWeight(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto &pLayer : this->sLayerList)
			sInitialier.initializeWeight(*pLayer);
	}

	template<class Initializer, class ...InitializerParam> void NN::initBias(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto &pLayer : this->sLayerList)
			sInitialier.initializeBias(*pLayer);
	}

	template<class LossFunc> float NN::loss(const float *pInput, const float *pOutput)
	{
		this->forward(pInput);
		return LossFunc::loss(this->sOutput.back().size(), this->sOutput.back().data(), pOutput);
	}

	template<class LossFunc> float NN::loss(std::size_t nBatchSize, const std::vector<float> *pInput, const std::vector<float> *pOutput)
	{
		auto nLossSum{.0f};

		for (std::size_t nBatch{0u}; nBatch < nBatchSize; ++nBatch)
			nLossSum += this->loss<LossFunc>(pInput[nBatch].data(), pOutput[nBatch].data());

		return nLossSum / nBatchSize;
	}
}