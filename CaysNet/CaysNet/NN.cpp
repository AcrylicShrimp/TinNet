
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "NN.h"

namespace CaysNet
{
	NN::NN(std::initializer_list<Layer::Layer *> sLayerList) :
		sLayerList(sLayerList)
	{
		for (const auto pLayer : this->sLayerList)
			this->sOutput.emplace_back(pLayer->fanOut(), .0f);
	}

	NN::NN(const NN &sSrc) :
		sOutput{sSrc.sOutput}
	{
		for (const auto pLayer : sSrc.sLayerList)
			this->sLayerList.emplace_back(pLayer->duplicate());
	}

	NN::NN(NN &&sSrc) :
		sLayerList{std::move(sSrc.sLayerList)},
		sOutput{std::move(sSrc.sOutput)}
	{
		//Empty.
	}

	NN::~NN()
	{
		for (auto pLayer : this->sLayerList)
			delete pLayer;

		this->sLayerList.clear();
		this->sOutput.clear();
	}

	NN &NN::operator=(const NN &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~NN();

		this->sLayerList = sSrc.sLayerList;
		this->sOutput = sSrc.sOutput;

		return *this;
	}

	NN &NN::operator=(NN &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~NN();

		this->sLayerList = std::move(sSrc.sLayerList);
		this->sOutput = std::move(sSrc.sOutput);

		return *this;
	}

	void NN::forward(const float *pInput)
	{
		assert(this->sLayerList.size());

		this->sLayerList.front()->forward(pInput, this->sOutput.front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(this->sOutput[nIndex - 1].data(), this->sOutput[nIndex].data());
	}

	void NN::forward(const float *pInput, float *pOutput)
	{
		this->forward(pInput);

		for (auto nValue : this->sOutput.back())
			*pOutput++ = nValue;
	}

	void NN::forward(
		const float *pInput,
		std::vector<std::vector<float>> &sActivationInputBuffer,
		std::vector<std::vector<float>> &sActivationOutputBuffer)
	{
		assert(this->sLayerList.size());
		assert(this->sLayerList.size() == sActivationInputBuffer.size());
		assert(this->sLayerList.size() == sActivationOutputBuffer.size());

		this->sLayerList.front()->forward(pInput, this->sOutput.front().data(), sActivationInputBuffer.front().data(), sActivationOutputBuffer.front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(this->sOutput[nIndex - 1].data(), this->sOutput[nIndex].data(), sActivationInputBuffer[nIndex].data(), sActivationOutputBuffer[nIndex].data());
	}

	void NN::backward(
		const std::vector<std::vector<float>> &sActivationInputBuffer,
		const std::vector<std::vector<float>> &sActivationOutputBuffer,
		std::vector<std::vector<float>> &sBiasDeltaBuffer,
		std::vector<std::vector<float>> &sWeightDeltaBuffer,
		std::vector<std::vector<float>> &sBackwardBuffer,
		const float *pForwardInput,
		const float *pBackwardInput) const
	{
		for (std::size_t nIndex{this->sLayerList.size() - 1}; ; --nIndex)
		{
			auto pLayer{this->sLayerList[nIndex]};
			auto pLayerForwardInput{nIndex == 0 ? pForwardInput : this->sOutput[nIndex - 1].data()};
			auto pLayerBackwardInput{nIndex + 1 == this->sLayerList.size() ? pBackwardInput : sBackwardBuffer[nIndex + 1].data()};
			auto pLayerBackwardOutput{sBackwardBuffer[nIndex].data()};

			pLayer->backward(
				sActivationInputBuffer[nIndex].data(),
				sActivationOutputBuffer[nIndex].data(),
				pLayerForwardInput,
				pLayerBackwardInput,
				pLayerBackwardOutput,
				sBiasDeltaBuffer[nIndex].data(),
				sWeightDeltaBuffer[nIndex].data());

			if (!nIndex)
				break;
		}
	}

	std::size_t NN::classify(const float *pInput)
	{
		assert(this->sLayerList.size());

		this->forward(pInput);

		std::size_t nMaxIndex{0};
		auto nMaxValue{this->sOutput.back().front()};

		for (std::size_t nOut{1}, nOutSize{this->sOutput.back().size()}; nOut < nOutSize; ++nOut)
			if (nMaxValue < this->sOutput.back()[nOut])
				nMaxValue = this->sOutput.back()[nMaxIndex = nOut];

		return nMaxIndex;
	}

	float NN::classificationLoss(const float *const *pInput, const float *const *pOutput, std::size_t nBatchCount)
	{
		assert(this->sLayerList.size());

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
		//IO::Serializable::write(sOutput, this->sLayerList.size());
		//
		//for (auto &pLayer : this->sLayerList)
		//	pLayer->serialize(sOutput);
	}

	void NN::deserialize(std::ifstream &sInput)
	{
		//this->sLayerList.clear();
		//this->sOutput.clear();
		//
		//for (std::size_t nIndex{0}, nSize{IO::Serializable::read<std::size_t>(sInput)}; nIndex < nSize; ++nIndex)
		//{
		//	auto nFanIn{IO::Serializable::read<std::size_t>(sInput)};
		//	auto nFanOut{IO::Serializable::read<std::size_t>(sInput)};
		//
		//	this->sLayerList.emplace_back(nFanIn, nFanOut, Activation::Activations::createByName(IO::Serializable::readWideString(sInput), sInput));
		//	this->sOutput.emplace_back(nFanOut, .0f);
		//
		//	this->sLayerList.back().deserialize(sInput);
		//}
	}
}