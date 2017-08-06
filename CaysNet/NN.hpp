
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

namespace CaysNet
{
	template<class LossFunc> NN<LossFunc>::NN(std::initializer_list<Layer> sLayerList) :
		sLayerList(sLayerList)
	{
		for (const auto &sLayer : this->sLayerList)
			this->sOutputBuffer.emplace_back(sLayer.fanOut(), .0f);
	}

	template<class LossFunc> NN<LossFunc>::NN(const NN &sSrc) :
		sLayerList{sSrc.sLayerList},
		sOutputBuffer{sSrc.sOutputBuffer}
	{
		//Empty.
	}

	template<class LossFunc> NN<LossFunc>::NN(NN &&sSrc) :
		sLayerList{std::move(sSrc.sLayerList)},
		sOutputBuffer{std::move(sSrc.sOutputBuffer)}
	{
		//Empty.
	}

	template<class LossFunc> NN<LossFunc> &NN<LossFunc>::operator=(const NN &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sLayerList = sSrc.sLayerList;
		this->sOutputBuffer = sSrc.sOutputBuffer;

		return *this;
	}

	template<class LossFunc> NN<LossFunc> &NN<LossFunc>::operator=(NN &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sLayerList = std::move(sSrc.sLayerList);
		this->sOutputBuffer = std::move(sSrc.sOutputBuffer);

		return *this;
	}

	template<class LossFunc> template<class Initializer, class ...InitializerParam> void NN<LossFunc>::initWeight(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto &sLayer : this->sLayerList)
			sInitialier.initializeWeight(sLayer);
	}

	template<class LossFunc> template<class Initializer, class ...InitializerParam> void NN<LossFunc>::initBias(InitializerParam && ...sParam)
	{
		Initializer sInitialier(std::forward<InitializerParam>(sParam)...);

		for (auto &sLayer : this->sLayerList)
			sInitialier.initializeBias(sLayer);
	}

	template<class LossFunc> void NN<LossFunc>::calc(const float *pInput)
	{
		this->sLayerList[0].forward(pInput, this->sOutputBuffer[0].data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex].forward(this->sOutputBuffer[nIndex - 1].data(), this->sOutputBuffer[nIndex].data());
	}

	template<class LossFunc> void NN<LossFunc>::calc(const float *pInput, float *pOutput)
	{
		if (!this->sLayerList.size())
			return;

		this->calc(pInput);

		for (auto nValue : this->sOutputBuffer.back())
			*pOutput++ = nValue;
	}

	template<class LossFunc> float NN<LossFunc>::loss(const float *pInput, const float *pOutput)
	{
		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		this->calc(pInput);

		return LossFunc::loss(this->sOutputBuffer.back().size(), this->sOutputBuffer.back().data(), pOutput);
	}

	template<class LossFunc> float NN<LossFunc>::loss(const float **pInput, const float **pOutput, std::size_t nBatchCount)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}; nIndex < nBatchCount; ++nIndex)
			nLossSum += this->loss(pInput[nIndex], pOutput[nIndex]);

		//Take average of the loss.
		return nLossSum / nBatchCount;
	}

	template<class LossFunc> float NN<LossFunc>::loss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList)
	{
		assert(this->sLayerList.size());
		assert(sInputList.size() == sOutputList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}, nSize{sInputList.size()}; nIndex < nSize; ++nIndex)
			nLossSum += this->loss(sInputList[nIndex], sOutputList[nIndex]);

		//Take average of the loss.
		return nLossSum / sInputList.size();
	}

	template<class LossFunc> float NN<LossFunc>::loss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList)
	{
		assert(this->sLayerList.size());
		assert(sInputList.size() == sOutputList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}, nSize{sInputList.size()}; nIndex < nSize; ++nIndex)
			nLossSum += this->loss(sInputList[nIndex].data(), sOutputList[nIndex].data());

		//Take average of the loss.
		return nLossSum / sInputList.size();
	}
}