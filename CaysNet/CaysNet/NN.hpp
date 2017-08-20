
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

namespace CaysNet
{
	template<class Initializer, class ...InitializerParam> void NN::initWeight(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto &sLayer : this->sLayerList)
			sInitialier.initializeWeight(sLayer);
	}

	template<class Initializer, class ...InitializerParam> void NN::initBias(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto &sLayer : this->sLayerList)
			sInitialier.initializeBias(sLayer);
	}

	template<class LossFunc> float NN::loss(const float *pInput, const float *pOutput)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		this->calc(pInput);

		return LossFunc::loss<LossFunc>(this->sOutputBuffer.back().size(), this->sOutputBuffer.back().data(), pOutput);
	}

	template<class LossFunc> float NN::loss(const float **pInput, const float **pOutput, std::size_t nBatchCount)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

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

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

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

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}, nSize{sInputList.size()}; nIndex < nSize; ++nIndex)
			nLossSum += this->loss<LossFunc>(sInputList[nIndex].data(), sOutputList[nIndex].data());

		//Take average of the loss.
		return nLossSum / sInputList.size();
	}
}