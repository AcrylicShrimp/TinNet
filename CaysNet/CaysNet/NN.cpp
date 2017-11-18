
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
		std::size_t nBatchSize,
		const std::vector<float> *pInput,
		std::vector<std::vector<float>> *pOutputBuffer) const
	{
		this->sLayerList.front()->forward(nBatchSize, pInput, pOutputBuffer->data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(nBatchSize, pOutputBuffer[nIndex - 1].data(), pOutputBuffer[nIndex].data());
	}

	void NN::forward(
		const float *pInput,
		std::vector<float> *pOutputBuffer,
		std::vector<float> *pActivationInputBuffer,
		std::vector<float> *pActivationOutputBuffer) const
	{
		this->sLayerList.front()->forward(pInput, pOutputBuffer->data(), pActivationInputBuffer->data(), pActivationOutputBuffer->data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(pOutputBuffer[nIndex - 1].data(), pOutputBuffer[nIndex].data(), pActivationInputBuffer[nIndex].data(), pActivationOutputBuffer[nIndex].data());
	}

	void NN::forward(
		std::size_t nBatchSize,
		const std::vector<float> *pInput,
		std::vector<std::vector<float>> *pOutputBuffer,
		std::vector<std::vector<float>> *pActivationInputBuffer,
		std::vector<std::vector<float>> *pActivationOutputBuffer) const
	{
		this->sLayerList.front()->forward(nBatchSize, pInput, pOutputBuffer->data(), pActivationInputBuffer->data(), pActivationOutputBuffer->data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(nBatchSize, pOutputBuffer[nIndex - 1].data(), pOutputBuffer[nIndex].data(), pActivationInputBuffer[nIndex].data(), pActivationOutputBuffer[nIndex].data());
	}

	void NN::backward(
		const float *pForwardInput,
		const float *pBackwardInput,
		const std::vector<float> *pForwardOutputBuffer,
		const std::vector<float> *pActivationInputBuffer,
		const std::vector<float> *pActivationOutputBuffer,
		std::vector<float> *pBiasDelta,
		std::vector<float> *pWeightDelta,
		std::vector<float> *pBackwardOutputBuffer) const
	{
		for (std::size_t nIndex{this->sLayerList.size() - 1}; ; --nIndex)
		{
			auto pLayer{this->sLayerList[nIndex]};
			auto pLayerForwardInput{nIndex == 0 ? pForwardInput : pForwardOutputBuffer[nIndex - 1].data()};
			auto pLayerBackwardInput{nIndex + 1 == this->sLayerList.size() ? pBackwardInput : pBackwardOutputBuffer[nIndex + 1].data()};
			auto pLayerBackwardOutput{pBackwardOutputBuffer[nIndex].data()};

			pLayer->backward(
				pActivationInputBuffer[nIndex].data(),
				pActivationOutputBuffer[nIndex].data(),
				pLayerForwardInput,
				pLayerBackwardInput,
				pLayerBackwardOutput,
				pBiasDelta[nIndex].data(),
				pWeightDelta[nIndex].data());

			if (!nIndex)
				break;
		}
	}

	void NN::backward(
		std::size_t nBatchSize,
		const std::vector<float> *pForwardInput,
		const std::vector<float> *pBackwardInput,
		const std::vector<std::vector<float>> *pForwardOutputBuffer,
		const std::vector<std::vector<float>> *pActivationInputBuffer,
		const std::vector<std::vector<float>> *pActivationOutputBuffer,
		std::vector<float> *pBiasDelta,
		std::vector<float> *pWeightDelta,
		std::vector<float> *pBiasDeltaBuffer,
		std::vector<std::vector<float>> *pBackwardOutputBuffer) const
	{
		for (std::size_t nIndex{this->sLayerList.size() - 1}; ; --nIndex)
		{
			auto pLayer{this->sLayerList[nIndex]};
			auto pLayerForwardInput{nIndex == 0 ? pForwardInput : pForwardOutputBuffer[nIndex - 1].data()};
			auto pLayerBackwardInput{nIndex + 1 == this->sLayerList.size() ? pBackwardInput : pBackwardOutputBuffer[nIndex + 1].data()};
			auto pLayerBackwardOutput{pBackwardOutputBuffer[nIndex].data()};

			pLayer->backward(
				nBatchSize,
				pActivationInputBuffer[nIndex].data(),
				pActivationOutputBuffer[nIndex].data(),
				pLayerForwardInput,
				pLayerBackwardInput,
				pLayerBackwardOutput,
				pBiasDelta[nIndex].data(),
				pWeightDelta[nIndex].data(),
				pBiasDeltaBuffer[nIndex].data());

			if (!nIndex)
				break;
		}
	}

	std::size_t NN::classify(const float *pInput)
	{
		this->forward(pInput);

		std::size_t nMaxIndex{0};
		auto nMaxValue{this->sOutput.back().front()};

		for (std::size_t nOut{1}, nOutSize{this->sOutput.back().size()}; nOut < nOutSize; ++nOut)
			if (nMaxValue < this->sOutput.back()[nOut])
				nMaxValue = this->sOutput.back()[nMaxIndex = nOut];

		return nMaxIndex;
	}

	void NN::classify(std::size_t nBatchSize, const std::vector<float> *pInput, std::size_t *pOutput)
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

		for (const auto &sOutputBuffer : sOutput.back())
		{
			std::size_t nMaxIndex{0};
			auto nMaxValue{sOutputBuffer.back()};

			for (std::size_t nOut{1}, nOutSize{sOutputBuffer.size()}; nOut < nOutSize; ++nOut)
				if (nMaxValue < sOutputBuffer[nOut])
					nMaxValue = sOutputBuffer[nMaxIndex = nOut];

			*pOutput++ = nMaxIndex;
		}
	}

	float NN::classificationLoss(std::size_t nBatchSize, const std::vector<float> *pInput, const std::vector<float> *pOutput)
	{
		std::vector<std::size_t> sResult(nBatchSize);
		this->classify(nBatchSize, pInput, sResult.data());

		auto nResult{.0f};

		for (std::size_t nIndex{0u}; nIndex < nBatchSize; ++nIndex)
			nResult += pOutput[nIndex][sResult[nIndex]];

		return 1.f - nResult / nBatchSize;
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