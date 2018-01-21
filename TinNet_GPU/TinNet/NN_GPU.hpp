
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

namespace TinNet
{
	template<class NewLayer, class ...NewLayerInitializerParam> void NN_GPU::addLayer(NewLayerInitializerParam && ...sParam)
	{
		this->sLayerList.emplace_back(std::make_unique<NewLayer>(std::forward<NewLayerInitializerParam>(sParam)...));

		CUdeviceptr pOutput;
		cuMemAlloc(&pOutput, sizeof(float) * this->sLayerList.back()->fanOut());

		this->sOutput.emplace_back(pOutput);
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
}