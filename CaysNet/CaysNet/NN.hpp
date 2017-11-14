
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

		std::vector<std::vector<std::vector<float>>> sOutput(nBatchCount);

		for (auto &sOutputBuffer : sOutput)
		{
			sOutputBuffer.resize(this->sLayerList.size());

			std::size_t nIndex{0};

			for (auto &sLayerBuffer : sOutputBuffer)
				sLayerBuffer.resize(this->sLayerList[nIndex++]->fanOut());
		}

		this->forward(pInput, sOutput);

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}; nIndex < nBatchCount; ++nIndex)
			nLossSum += LossFunc::loss(sOutput[nIndex].back().size(), sOutput[nIndex].back().data(), pOutput[nIndex]);

		//Take average of the loss.
		return nLossSum / nBatchCount;
	}

	template<class LossFunc> float NN::loss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList)
	{
		assert(this->sLayerList.size());
		assert(sInputList.size() == sOutputList.size());

		std::vector<std::vector<std::vector<float>>> sOutput(sInputList.size());

		for (auto &sOutputBuffer : sOutput)
		{
			sOutputBuffer.resize(this->sLayerList.size());

			std::size_t nIndex{0};

			for (auto &sLayerBuffer : sOutputBuffer)
				sLayerBuffer.resize(this->sLayerList[nIndex++]->fanOut());
		}

		this->forward(sInputList, sOutput);

		float nLossSum{.0f};

		for (std::size_t nIndex{0u}, nSize{sInputList.size()}; nIndex < nSize; ++nIndex)
			nLossSum += LossFunc::loss(sOutput[nIndex].back().size(), sOutput[nIndex].back().data(), sOutputList[nIndex]);

		//Take average of the loss.
		return nLossSum / sInputList.size();
	}
}