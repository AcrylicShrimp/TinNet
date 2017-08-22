
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "NN.h"

namespace CaysNet
{
	NN::NN(std::initializer_list<Layer> sLayerList) :
		sLayerList(sLayerList)
	{
		for (const auto &sLayer : this->sLayerList)
			this->sOutputBuffer.emplace_back(sLayer.fanOut(), .0f);
	}

	NN::NN(const NN &sSrc) :
		sLayerList{sSrc.sLayerList},
		sOutputBuffer{sSrc.sOutputBuffer}
	{
		//Empty.
	}

	NN::NN(NN &&sSrc) :
		sLayerList{std::move(sSrc.sLayerList)},
		sOutputBuffer{std::move(sSrc.sOutputBuffer)}
	{
		//Empty.
	}

	NN &NN::operator=(const NN &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sLayerList = sSrc.sLayerList;
		this->sOutputBuffer = sSrc.sOutputBuffer;

		return *this;
	}

	NN &NN::operator=(NN &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sLayerList = std::move(sSrc.sLayerList);
		this->sOutputBuffer = std::move(sSrc.sOutputBuffer);

		return *this;
	}

	void NN::calc(const float *pInput)
	{
		assert(this->sLayerList.size());

		this->sLayerList[0].forward(pInput, this->sOutputBuffer[0].data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex].forward(this->sOutputBuffer[nIndex - 1].data(), this->sOutputBuffer[nIndex].data());
	}

	void NN::calc(const float *pInput, float *pOutput)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return;

		this->calc(pInput);

		for (auto nValue : this->sOutputBuffer.back())
			*pOutput++ = nValue;
	}

	void NN::calcForTrain(const float *pInput)
	{
		this->sLayerList[0].forwardForTrain(pInput, this->sOutputBuffer[0].data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex].forwardForTrain(this->sOutputBuffer[nIndex - 1].data(), this->sOutputBuffer[nIndex].data());
	}

	void NN::calcForTrain(const float *pInput, float *pOutput)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return;

		this->calcForTrain(pInput);

		for (auto nValue : this->sOutputBuffer.back())
			*pOutput++ = nValue;
	}

	std::size_t NN::classify(const float *pInput)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<std::size_t>::max();

		this->calc(pInput);

		std::size_t nMaxIndex{0};
		auto nMaxValue{this->sOutputBuffer.back().front()};

		for (std::size_t nOut{1}, nOutSize{this->sOutputBuffer.back().size()}; nOut < nOutSize; ++nOut)
			if (nMaxValue < this->sOutputBuffer.back()[nOut])
				nMaxValue = this->sOutputBuffer.back()[nMaxIndex = nOut];

		return nMaxIndex;
	}

	float NN::classificationLoss(const float **pInput, const float **pOutput, std::size_t nBatchCount)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		auto nResult{.0f};

		for (std::size_t nIndex{0u}; nIndex < nBatchCount; ++nIndex)
			nResult += pOutput[nIndex][this->classify(pInput[nIndex])];

		return 1.f - nResult / nBatchCount;
	}

	float NN::classificationLoss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		auto nResult{.0f};

		for (std::size_t nIndex{0u}, nCount{sInputList.size()}; nIndex < nCount; ++nIndex)
			nResult += sOutputList[nIndex][this->classify(sInputList[nIndex])];

		return 1.f - nResult / sInputList.size();
	}

	float NN::classificationLoss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList)
	{
		assert(this->sLayerList.size());

		if (!this->sLayerList.size())
			return std::numeric_limits<float>::signaling_NaN();

		auto nResult{.0f};

		for (std::size_t nIndex{0u}, nCount{sInputList.size()}; nIndex < nCount; ++nIndex)
			nResult += sOutputList[nIndex][this->classify(sInputList[nIndex].data())];

		return 1.f - nResult / sInputList.size();
	}

	void NN::serialize(std::ofstream &sOutput) const
	{
		IO::Serializable::write(sOutput, this->sLayerList.size());

		for (auto &sLayer : this->sLayerList)
		{
			IO::Serializable::write(sOutput, sLayer.fanIn());
			IO::Serializable::write(sOutput, sLayer.fanOut());
			IO::Serializable::write(sOutput, std::wstring(sLayer.activation()->name()));

			sLayer.serialize(sOutput);
		}
	}

	void NN::deserialize(std::ifstream &sInput)
	{
		this->sLayerList.clear();
		this->sOutputBuffer.clear();

		for (std::size_t nIndex{0}, nSize{IO::Serializable::read<std::size_t>(sInput)}; nIndex < nSize; ++nIndex)
		{
			auto nFanIn{IO::Serializable::read<std::size_t>(sInput)};
			auto nFanOut{IO::Serializable::read<std::size_t>(sInput)};

			this->sLayerList.emplace_back(nFanIn, nFanOut, Activation::Activations::createByName(IO::Serializable::readWideString(sInput), sInput));
			this->sOutputBuffer.emplace_back(nFanOut, .0f);

			this->sLayerList.back().deserialize(sInput);
		}
	}
}