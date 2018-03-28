
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

namespace TinNet
{
	template<class NewLayer, class ...NewLayerInitializerParam> void NN_GPU::addLayer(NewLayerInitializerParam && ...sParam)
	{
		this->sLayerList.emplace_back(std::make_unique<NewLayer>(std::forward<NewLayerInitializerParam>(sParam)...));
		this->sOutput.emplace_back(this->sLayerList.back()->fanOut());
	}

	template<class Initializer, class ...InitializerParam> void NN_GPU::initBias(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto &pLayer : this->sLayerList)
			sInitialier.initializeBias(*pLayer);
	}

	template<class Initializer, class ...InitializerParam> void NN_GPU::initWeight(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto &pLayer : this->sLayerList)
			sInitialier.initializeWeight(*pLayer);
	}

	template<class LossFunc> float NN_GPU::loss(const GPUVector &sInput, const GPUVector &sOutput)
	{
		this->forward(sInput);
		return LossFunc::loss(this->sOutput.back().size(), this->sOutput.back().data(), pOutput);
	}

	template<class LossFunc> float NN_GPU::loss(std::size_t nBatchSize, const GPUVector *pInput, const GPUVector *pOutput)
	{
		auto nLossSum{.0f};

		for (std::size_t nBatch{0u}; nBatch < nBatchSize; ++nBatch)
			nLossSum += this->loss<LossFunc>(pInput[nBatch].data(), pOutput[nBatch].data());

		return nLossSum / nBatchSize;
	}
}