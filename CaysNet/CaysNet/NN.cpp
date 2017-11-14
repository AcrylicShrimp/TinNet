
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
		assert(pInput);
		assert(this->sLayerList.size());

		this->sLayerList.front()->forward(pInput, this->sOutput.front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(this->sOutput[nIndex - 1].data(), this->sOutput[nIndex].data());
	}

	void NN::forward(const float *pInput, float *pOutput)
	{
		assert(pInput);
		assert(pOutput);

		this->forward(pInput);

		for (auto nValue : this->sOutput.back())
			*pOutput++ = nValue;
	}

	void NN::forward(
		const float *pInput,
		std::vector<std::vector<float>> &sActivationInputBuffer,
		std::vector<std::vector<float>> &sActivationOutputBuffer)
	{
		assert(pInput);
		assert(this->sLayerList.size());
		assert(this->sLayerList.size() == sActivationInputBuffer.size());
		assert(this->sLayerList.size() == sActivationOutputBuffer.size());

		this->sLayerList.front()->forward(pInput, this->sOutput.front().data(), sActivationInputBuffer.front().data(), sActivationOutputBuffer.front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			this->sLayerList[nIndex]->forward(this->sOutput[nIndex - 1].data(), this->sOutput[nIndex].data(), sActivationInputBuffer[nIndex].data(), sActivationOutputBuffer[nIndex].data());
	}

	void NN::forward(const float *const *pInput, std::vector<std::vector<std::vector<float>>> &sOutputBuffer)
	{
		assert(pInput);
		assert(sOutputBuffer.size());
		assert(this->sLayerList.size());
		assert(sOutputBuffer.size() == this->sLayerList.size());

		for (auto &sOutput : sOutputBuffer)
			this->sLayerList.front()->forward(*pInput++, sOutput.front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			for (auto &sOutput : sOutputBuffer)
				this->sLayerList[nIndex]->forward(sOutput[nIndex - 1].data(), sOutput[nIndex].data());
	}

	void NN::forward(
		const float *const *pInput,
		std::vector<std::vector<std::vector<float>>> &sOutputBuffer,
		std::vector<std::vector<std::vector<float>>> &sActivationInputBuffer,
		std::vector<std::vector<std::vector<float>>> &sActivationOutputBuffer)
	{
		assert(pInput);
		assert(sOutputBuffer.size());
		assert(this->sLayerList.size());
		assert(sOutputBuffer.size() == sActivationInputBuffer.size());
		assert(sOutputBuffer.size() == sActivationOutputBuffer.size());

		for (std::size_t nOutputIndex{0}, nOutputSize{sOutputBuffer.size()}; nOutputIndex < nOutputSize; ++nOutputIndex)
			this->sLayerList.front()->forward(*pInput++, sOutputBuffer[nOutputIndex].front().data(), sActivationInputBuffer[nOutputIndex].front().data(), sActivationOutputBuffer[nOutputIndex].front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			for (std::size_t nOutputIndex{0}, nOutputSize{sOutputBuffer.size()}; nOutputIndex < nOutputSize; ++nOutputIndex)
				this->sLayerList[nIndex]->forward(sOutputBuffer[nOutputIndex][nIndex - 1].data(), sOutputBuffer[nOutputIndex][nIndex].data(), sActivationInputBuffer[nOutputIndex][nIndex].data(), sActivationOutputBuffer[nOutputIndex][nIndex].data());
	}

	void NN::forward(const std::vector<std::vector<float>> &sInput, std::vector<std::vector<std::vector<float>>> &sOutputBuffer)
	{
		assert(sOutputBuffer.size());
		assert(this->sLayerList.size());
		assert(sOutputBuffer.size() == sInput.size());

		for (std::size_t nOutputIndex{0}, nOutputSize{sOutputBuffer.size()}; nOutputIndex < nOutputSize; ++nOutputIndex)
			this->sLayerList.front()->forward(sInput[nOutputIndex].data(), sOutputBuffer[nOutputIndex].front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			for (auto &sOutput : sOutputBuffer)
				this->sLayerList[nIndex]->forward(sOutput[nIndex - 1].data(), sOutput[nIndex].data());
	}

	void NN::forward(
		const std::vector<std::vector<float>> &sInput,
		std::vector<std::vector<std::vector<float>>> &sOutputBuffer,
		std::vector<std::vector<std::vector<float>>> &sActivationInputBuffer,
		std::vector<std::vector<std::vector<float>>> &sActivationOutputBuffer)
	{
		assert(sOutputBuffer.size());
		assert(this->sLayerList.size());
		assert(sOutputBuffer.size() == sInput.size());
		assert(sOutputBuffer.size() == sActivationInputBuffer.size());
		assert(sOutputBuffer.size() == sActivationOutputBuffer.size());

		for (std::size_t nOutputIndex{0}, nOutputSize{sOutputBuffer.size()}; nOutputIndex < nOutputSize; ++nOutputIndex)
			this->sLayerList.front()->forward(sInput[nOutputIndex].data(), sOutputBuffer[nOutputIndex].front().data(), sActivationInputBuffer[nOutputIndex].front().data(), sActivationOutputBuffer[nOutputIndex].front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			for (std::size_t nOutputIndex{0}, nOutputSize{sOutputBuffer.size()}; nOutputIndex < nOutputSize; ++nOutputIndex)
				this->sLayerList[nIndex]->forward(sOutputBuffer[nOutputIndex][nIndex - 1].data(), sOutputBuffer[nOutputIndex][nIndex].data(), sActivationInputBuffer[nOutputIndex][nIndex].data(), sActivationOutputBuffer[nOutputIndex][nIndex].data());
	}

	void NN::forward(
		std::size_t nOffset,
		std::size_t nCount,
		const std::vector<std::vector<float>> &sInput,
		std::vector<std::vector<std::vector<float>>> &sOutputBuffer,
		std::vector<std::vector<std::vector<float>>> &sActivationInputBuffer,
		std::vector<std::vector<std::vector<float>>> &sActivationOutputBuffer)
	{
		assert(sOutputBuffer.size());
		assert(this->sLayerList.size());
		assert(sOutputBuffer.size() == sActivationInputBuffer.size());
		assert(sOutputBuffer.size() == sActivationOutputBuffer.size());

		for (std::size_t nOutputIndex{0}; nOutputIndex < nCount; ++nOutputIndex)
			this->sLayerList.front()->forward(sInput[nOutputIndex + nOffset].data(), sOutputBuffer[nOutputIndex].front().data(), sActivationInputBuffer[nOutputIndex].front().data(), sActivationOutputBuffer[nOutputIndex].front().data());

		for (std::size_t nIndex{1}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
			for (std::size_t nOutputIndex{0}; nOutputIndex < nCount; ++nOutputIndex)
				this->sLayerList[nIndex]->forward(sOutputBuffer[nOutputIndex][nIndex - 1].data(), sOutputBuffer[nOutputIndex][nIndex].data(), sActivationInputBuffer[nOutputIndex][nIndex].data(), sActivationOutputBuffer[nOutputIndex][nIndex].data());
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

	void NN::backward(
		std::vector<std::vector<std::vector<float>>> &sOutputBuffer,
		const std::vector<std::vector<std::vector<float>>> &sActivationInputBuffer,
		const std::vector<std::vector<std::vector<float>>> &sActivationOutputBuffer,
		std::vector<std::vector<float>> &sBiasDeltaBuffer,
		std::vector<std::vector<float>> &sWeightDeltaBuffer,
		std::vector<std::vector<std::vector<float>>> &sBackwardBuffer,
		const float *const *pForwardInput,
		const float *const *pBackwardInput) const
	{
		std::vector<std::vector<float>> sBiasDelta(this->sLayerList.size());
		std::vector<std::vector<float>> sWeightDelta(this->sLayerList.size());

		for (std::size_t nIndex{0}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
		{
			sBiasDelta[nIndex].resize(sBiasDeltaBuffer[nIndex].size(), .0f);
			sWeightDelta[nIndex].resize(sWeightDeltaBuffer[nIndex].size(), .0f);
		}

		for (std::size_t nIndex{this->sLayerList.size() - 1}; ; --nIndex)
		{
			for (std::size_t nOutputIndex{0}, nOutputSize{sOutputBuffer.size()}; nOutputIndex < nOutputSize; ++nOutputIndex)
			{
				auto pLayer{this->sLayerList[nIndex]};
				auto pLayerForwardInput{nIndex == 0 ? *pForwardInput++ : sOutputBuffer[nOutputIndex][nIndex - 1].data()};
				auto pLayerBackwardInput{nIndex + 1 == this->sLayerList.size() ? *pBackwardInput++ : sBackwardBuffer[nOutputIndex][nIndex + 1].data()};
				auto pLayerBackwardOutput{sBackwardBuffer[nOutputIndex][nIndex].data()};

				pLayer->backward(
					sActivationInputBuffer[nOutputIndex][nIndex].data(),
					sActivationOutputBuffer[nOutputIndex][nIndex].data(),
					pLayerForwardInput,
					pLayerBackwardInput,
					pLayerBackwardOutput,
					sBiasDelta[nIndex].data(),
					sWeightDelta[nIndex].data());

				for (std::size_t nBiasIndex{0}, nBiasSize{sBiasDelta.size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
					sBiasDeltaBuffer[nIndex][nBiasIndex] += sBiasDelta[nIndex][nBiasIndex];

				for (std::size_t nWeightIndex{0}, nWeightSize{sWeightDelta.size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
					sWeightDeltaBuffer[nIndex][nWeightIndex] += sWeightDelta[nIndex][nWeightIndex];
			}

			if (!nIndex)
				break;
		}
	}

	void NN::backward(
		std::vector<std::vector<std::vector<float>>> &sOutputBuffer,
		const std::vector<std::vector<std::vector<float>>> &sActivationInputBuffer,
		const std::vector<std::vector<std::vector<float>>> &sActivationOutputBuffer,
		std::vector<std::vector<float>> &sBiasDeltaBuffer,
		std::vector<std::vector<float>> &sWeightDeltaBuffer,
		std::vector<std::vector<std::vector<float>>> &sBackwardBuffer,
		const std::vector<std::vector<float>> &sForwardInput,
		const std::vector<std::vector<float>> &sBackwardInput) const
	{
		std::vector<std::vector<float>> sBiasDelta(this->sLayerList.size());
		std::vector<std::vector<float>> sWeightDelta(this->sLayerList.size());

		for (std::size_t nIndex{0}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
		{
			sBiasDelta[nIndex].resize(sBiasDeltaBuffer[nIndex].size(), .0f);
			sWeightDelta[nIndex].resize(sWeightDeltaBuffer[nIndex].size(), .0f);
		}

		for (std::size_t nIndex{this->sLayerList.size() - 1}; ; --nIndex)
		{
			for (std::size_t nOutputIndex{0}, nOutputSize{sOutputBuffer.size()}; nOutputIndex < nOutputSize; ++nOutputIndex)
			{
				auto pLayer{this->sLayerList[nIndex]};
				auto pLayerForwardInput{nIndex == 0 ? sForwardInput[nOutputIndex].data() : sOutputBuffer[nOutputIndex][nIndex - 1].data()};
				auto pLayerBackwardInput{nIndex + 1 == this->sLayerList.size() ? sBackwardInput[nOutputIndex].data() : sBackwardBuffer[nOutputIndex][nIndex + 1].data()};
				auto pLayerBackwardOutput{sBackwardBuffer[nOutputIndex][nIndex].data()};

				pLayer->backward(
					sActivationInputBuffer[nOutputIndex][nIndex].data(),
					sActivationOutputBuffer[nOutputIndex][nIndex].data(),
					pLayerForwardInput,
					pLayerBackwardInput,
					pLayerBackwardOutput,
					sBiasDelta[nIndex].data(),
					sWeightDelta[nIndex].data());

				for (std::size_t nBiasIndex{0}, nBiasSize{sBiasDelta.size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
					sBiasDeltaBuffer[nIndex][nBiasIndex] += sBiasDelta[nIndex][nBiasIndex];

				for (std::size_t nWeightIndex{0}, nWeightSize{sWeightDelta.size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
					sWeightDeltaBuffer[nIndex][nWeightIndex] += sWeightDelta[nIndex][nWeightIndex];

				
			}

			if (!nIndex)
				break;
		}
	}

	void NN::backward(
		std::size_t nOffset,
		std::size_t nCount,
		std::vector<std::vector<std::vector<float>>> &sOutputBuffer,
		const std::vector<std::vector<std::vector<float>>> &sActivationInputBuffer,
		const std::vector<std::vector<std::vector<float>>> &sActivationOutputBuffer,
		std::vector<std::vector<float>> &sBiasDeltaBuffer,
		std::vector<std::vector<float>> &sWeightDeltaBuffer,
		std::vector<std::vector<std::vector<float>>> &sBackwardBuffer,
		const std::vector<std::vector<float>> &sForwardInput,
		const std::vector<std::vector<float>> &sBackwardInput) const
	{
		std::vector<std::vector<float>> sBiasDelta(this->sLayerList.size());
		std::vector<std::vector<float>> sWeightDelta(this->sLayerList.size());

		for (std::size_t nIndex{0}, nSize{this->sLayerList.size()}; nIndex < nSize; ++nIndex)
		{
			sBiasDelta[nIndex].resize(sBiasDeltaBuffer[nIndex].size(), .0f);
			sWeightDelta[nIndex].resize(sWeightDeltaBuffer[nIndex].size(), .0f);
		}

		for (std::size_t nIndex{this->sLayerList.size() - 1}; ; --nIndex)
		{
			for (std::size_t nOutputIndex{0}; nOutputIndex < nCount; ++nOutputIndex)
			{
				auto pLayer{this->sLayerList[nIndex]};
				auto pLayerForwardInput{nIndex == 0 ? sForwardInput[nOutputIndex + nOffset].data() : sOutputBuffer[nOutputIndex][nIndex - 1].data()};
				auto pLayerBackwardInput{nIndex + 1 == this->sLayerList.size() ? sBackwardInput[nOutputIndex].data() : sBackwardBuffer[nOutputIndex][nIndex + 1].data()};
				auto pLayerBackwardOutput{sBackwardBuffer[nOutputIndex][nIndex].data()};

				pLayer->backward(
					sActivationInputBuffer[nOutputIndex][nIndex].data(),
					sActivationOutputBuffer[nOutputIndex][nIndex].data(),
					pLayerForwardInput,
					pLayerBackwardInput,
					pLayerBackwardOutput,
					sBiasDelta[nIndex].data(),
					sWeightDelta[nIndex].data());

				for (std::size_t nBiasIndex{0}, nBiasSize{sBiasDelta.size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
					sBiasDeltaBuffer[nIndex][nBiasIndex] += sBiasDelta[nIndex][nBiasIndex];

				for (std::size_t nWeightIndex{0}, nWeightSize{sWeightDelta.size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
					sWeightDeltaBuffer[nIndex][nWeightIndex] += sWeightDelta[nIndex][nWeightIndex];
			}

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

	void NN::classify(const float *const *pInput, std::size_t *pOutput, std::size_t nBatchCount)
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

		for (const auto &sOutputBuffer : sOutput)
		{
			std::size_t nMaxIndex{0};
			auto nMaxValue{sOutputBuffer.back().front()};

			for (std::size_t nOut{1}, nOutSize{sOutputBuffer.back().size()}; nOut < nOutSize; ++nOut)
				if (nMaxValue < sOutputBuffer.back()[nOut])
					nMaxValue = sOutputBuffer.back()[nMaxIndex = nOut];

			*pOutput++ = nMaxIndex;
		}
	}

	void NN::classify(const std::vector<std::vector<float>> &sInput, std::size_t *pOutput)
	{
		assert(this->sLayerList.size());

		std::vector<std::vector<std::vector<float>>> sOutput(sInput.size());

		for (auto &sOutputBuffer : sOutput)
		{
			sOutputBuffer.resize(this->sLayerList.size());

			std::size_t nIndex{0};

			for (auto &sLayerBuffer : sOutputBuffer)
				sLayerBuffer.resize(this->sLayerList[nIndex++]->fanOut());
		}

		this->forward(sInput, sOutput);

		for (const auto &sOutputBuffer : sOutput)
		{
			std::size_t nMaxIndex{0};
			auto nMaxValue{sOutputBuffer.back().front()};

			for (std::size_t nOut{1}, nOutSize{sOutputBuffer.back().size()}; nOut < nOutSize; ++nOut)
				if (nMaxValue < sOutputBuffer.back()[nOut])
					nMaxValue = sOutputBuffer.back()[nMaxIndex = nOut];

			*pOutput++ = nMaxIndex;
		}
	}

	float NN::classificationLoss(const float *const *pInput, const float *const *pOutput, std::size_t nBatchCount)
	{
		assert(this->sLayerList.size());

		std::vector<std::size_t> sResult(nBatchCount);
		this->classify(pInput, sResult.data(), nBatchCount);

		auto nResult{.0f};

		for (std::size_t nIndex{0u}; nIndex < nBatchCount; ++nIndex)
			nResult += pOutput[nIndex][sResult[nIndex]];

		return 1.f - nResult / nBatchCount;
	}

	float NN::classificationLoss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList)
	{
		assert(this->sLayerList.size());
		assert(sInputList.size() == sOutputList.size());

		std::vector<std::size_t> sResult(sInputList.size());
		this->classify(sInputList, sResult.data());

		auto nResult{.0f};

		for (std::size_t nIndex{0u}, nSize{sInputList.size()}; nIndex < nSize; ++nIndex)
			nResult += sOutputList[nIndex][sResult[nIndex]];

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