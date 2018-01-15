
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "NN.h"

namespace CaysNet
{
	NN::NN(const NN &sSrc) :
		sOutput{sSrc.sOutput}
	{
		for (const auto &pLayer : sSrc.sLayerList)
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
		this->sLayerList.clear();
		this->sOutput.clear();
	}

	NN &NN::operator=(const NN &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~NN();

		for (const auto &pLayer : sSrc.sLayerList)
			this->sLayerList.emplace_back(pLayer->duplicate());

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
		std::vector<std::vector<float>> *pOutput,
		bool bTrainingPhase) const
	{
		this->sLayerList.front()->forward(nBatchSize, pInput, pOutput->data(), bTrainingPhase);

		for (std::size_t nIndex{1}, nDepth{this->depth()}; nIndex < nDepth; ++nIndex)
			this->sLayerList[nIndex]->forward(nBatchSize, pOutput[nIndex - 1].data(), pOutput[nIndex].data(), bTrainingPhase);
	}

	void NN::backward(
		std::size_t nBatchSize,
		const std::vector<float> *pForwardInput,
		const std::vector<float> *pBackwardInput,
		const std::vector<std::vector<float>> *pForwardOutput,
		std::vector<std::vector<float>> *pBackwardOutput,
		std::vector<float> *pBiasDelta,
		std::vector<float> *pWeightDelta) const
	{
		for (std::size_t nIndex{this->sLayerList.size() - 1}; ; --nIndex)
		{
			const auto &pLayer{this->sLayerList[nIndex]};
			const auto pLayerForwardInput{nIndex == 0 ? pForwardInput : pForwardOutput[nIndex - 1].data()};
			const auto pLayerBackwardInput{nIndex + 1 == this->depth() ? pBackwardInput : pBackwardOutput[nIndex + 1].data()};
			auto pLayerBackwardOutput{pBackwardOutput[nIndex].data()};

			for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
				for (std::size_t nOut{0}, nOutSize{pBiasDelta[nIndex].size()}; nOut < nOutSize; ++nOut)
					pBiasDelta[nIndex][nOut] += pLayerBackwardInput[nBatch][nOut];

			pLayer->backward(
				nBatchSize,
				pLayerForwardInput,
				pLayerBackwardInput,
				pLayerBackwardOutput,
				pWeightDelta[nIndex].data());

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
		std::vector<std::vector<std::vector<float>>> sOutput(this->depth());

		for (auto &sLayerBuffer : sOutput)
		{
			sLayerBuffer.resize(nBatchSize);

			for (auto &sOutputBuffer : sLayerBuffer)
				sOutputBuffer.resize(this->sLayerList[nIndex]->fanOut());

			++nIndex;
		}

		this->forward(nBatchSize, pInput, sOutput.data());

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
		{
			std::size_t nMaxIndex{0};
			auto nMaxValue{sOutput.back()[nBatch].front()};

			for (std::size_t nOut{1}, nOutSize{sOutput.back()[nBatch].size()}; nOut < nOutSize; ++nOut)
				if (nMaxValue < sOutput.back()[nBatch][nOut])
					nMaxValue = sOutput.back()[nBatch][nMaxIndex = nOut];

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
		IO::Serializable::write(sOutput, this->sLayerList.size());
		
		for (auto &pLayer : this->sLayerList)
			Layer::LayerIO::serializeLayer(sOutput, pLayer);
	}

	void NN::deserialize(std::ifstream &sInput)
	{
		this->sLayerList.clear();
		this->sOutput.clear();

		auto nSize{IO::Serializable::read<std::remove_reference_t<decltype(this->sLayerList.size())>>(sInput)};
		
		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex)
		{
			this->sLayerList.push_back(Layer::LayerIO::deserializeLayer(sInput));
			this->sOutput.emplace_back(this->sLayerList.back()->fanOut(), .0f);
		}
	}
}