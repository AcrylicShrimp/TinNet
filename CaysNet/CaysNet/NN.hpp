
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

	template<class LossFunc> float NN::loss(const float *const *pInput, const float *const *pOutput, std::size_t nBatchCount)
	{
		assert(this->sLayerList.size());

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}; nIndex < nBatchCount; ++nIndex)
			nLossSum += this->loss<LossFunc>(pInput[nIndex], pOutput[nIndex]);

		//Take average of the loss.
		return nLossSum / nBatchCount;
	}

	template<class LossFunc> float NN::loss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList)
	{
		assert(this->sLayerList.size());
		assert(sInputList.size() == sOutputList.size());

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}, nSize{sInputList.size()}; nIndex < nSize; ++nIndex)
			nLossSum += this->loss<LossFunc>(sInputList[nIndex], sOutputList[nIndex]);

		//Take average of the loss.
		return nLossSum / sInputList.size();
	}

	template<class LossFunc> float NN::loss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList)
	{
		assert(this->sLayerList.size());
		assert(sInputList.size() == sOutputList.size());

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}, nSize{sInputList.size()}; nIndex < nSize; ++nIndex)
			nLossSum += this->loss<LossFunc>(sInputList[nIndex].data(), sOutputList[nIndex].data());

		//Take average of the loss.
		return nLossSum / sInputList.size();
	}
}