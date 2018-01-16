
/*
	2018.01.17
	Created by AcrylicShrimp.
*/

#include "ConvLayer.h"

namespace TinNet::Layer
{
	ConvLayer::ConvLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
						 std::size_t nNewFilterWidth,
						 std::size_t nNewFilterHeight) :
		ConvLayer(nNewWidth, nNewHeight, nNewChannel, nNewFilter,
				  nNewFilterWidth,
				  nNewFilterHeight,
				  1u,
				  1u)
	{
		//Empty.
	}

	ConvLayer::ConvLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
						 std::size_t nNewFilterWidth,
						 std::size_t nNewFilterHeight,
						 std::size_t nNewStrideHorizontal,
						 std::size_t nNewStrideVertical) :
		ConvLayer(nNewWidth, nNewHeight, nNewChannel, nNewFilter,
				  nNewFilterWidth,
				  nNewFilterHeight,
				  nNewStrideHorizontal,
				  nNewStrideVertical,
				  nNewWidth,
				  nNewHeight)
	{
		//Empty.
	}

	ConvLayer::ConvLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
						 std::size_t nNewFilterWidth,
						 std::size_t nNewFilterHeight,
						 std::size_t nNewStrideHorizontal,
						 std::size_t nNewStrideVertical,
						 std::size_t nNewOutputWidth,
						 std::size_t nNewOutputHeight) :
		Layer(nNewWidth * nNewHeight * nNewChannel, nNewOutputWidth * nNewOutputHeight * nNewChannel),
		nWidth{nNewWidth},
		nHeight{nNewHeight},
		nChannel{nNewChannel},
		nFilter{nNewFilter},
		nFilterWidth{nNewFilterWidth},
		nFilterHeight{nNewFilterHeight},
		nStrideHorizontal{nNewStrideHorizontal},
		nStrideVertical{nNewStrideVertical},
		nOutputWidth{nNewOutputWidth},
		nOutputHeight{nNewOutputHeight},
		sBias(nNewFilter, .0f),
		sWeight(nNewFilter)
	{
		if ((this->nZeroPaddingHorizontalNegative = this->nZeroPaddingHorizontalPositive = ((this->nOutputWidth - 1u) * this->nStrideHorizontal - this->nWidth + this->nFilterWidth) / 2u) & 1u)
			++this->nZeroPaddingHorizontalPositive;

		if ((this->nZeroPaddingVerticalNegative = this->nZeroPaddingVerticalPositive = ((this->nOutputHeight - 1u) * this->nStrideVertical - this->nHeight + this->nFilterHeight) / 2u) & 1u)
			++this->nZeroPaddingVerticalPositive;

		for (auto &sWeight : this->sWeight)
		{
			sWeight.resize(this->nChannel);

			for (auto &sWeight : sWeight)
				sWeight.resize(this->nFilterWidth * this->nFilterHeight, .0f);
		}
	}

	ConvLayer::ConvLayer(const ConvLayer &sSrc) :
		Layer(sSrc),
		nWidth{sSrc.nWidth},
		nHeight{sSrc.nHeight},
		nChannel{sSrc.nChannel},
		nFilter{sSrc.nFilter},
		nFilterWidth{sSrc.nFilterWidth},
		nFilterHeight{sSrc.nFilterHeight},
		nStrideHorizontal{sSrc.nStrideHorizontal},
		nStrideVertical{sSrc.nStrideVertical},
		nOutputWidth{sSrc.nOutputWidth},
		nOutputHeight{sSrc.nOutputHeight},
		nZeroPaddingHorizontalNegative{sSrc.nZeroPaddingHorizontalNegative},
		nZeroPaddingHorizontalPositive{sSrc.nZeroPaddingHorizontalPositive},
		nZeroPaddingVerticalNegative{sSrc.nZeroPaddingVerticalNegative},
		nZeroPaddingVerticalPositive{sSrc.nZeroPaddingVerticalPositive},
		sBias{sSrc.sBias},
		sWeight{sSrc.sWeight}
	{
		//Empty.
	}

	ConvLayer::ConvLayer(ConvLayer &&sSrc) :
		Layer(sSrc),
		nWidth{sSrc.nWidth},
		nHeight{sSrc.nHeight},
		nChannel{sSrc.nChannel},
		nFilter{sSrc.nFilter},
		nFilterWidth{sSrc.nFilterWidth},
		nFilterHeight{sSrc.nFilterHeight},
		nStrideHorizontal{sSrc.nStrideHorizontal},
		nStrideVertical{sSrc.nStrideVertical},
		nOutputWidth{sSrc.nOutputWidth},
		nOutputHeight{sSrc.nOutputHeight},
		nZeroPaddingHorizontalNegative{sSrc.nZeroPaddingHorizontalNegative},
		nZeroPaddingHorizontalPositive{sSrc.nZeroPaddingHorizontalPositive},
		nZeroPaddingVerticalNegative{sSrc.nZeroPaddingVerticalNegative},
		nZeroPaddingVerticalPositive{sSrc.nZeroPaddingVerticalPositive},
		sBias{std::move(sSrc.sBias)},
		sWeight{std::move(sSrc.sWeight)}
	{
		//Empty.
	}

	ConvLayer &ConvLayer::operator=(const ConvLayer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(sSrc);
		this->nWidth = sSrc.nWidth;
		this->nHeight = sSrc.nHeight;
		this->nChannel = sSrc.nChannel;
		this->nFilter = sSrc.nFilter;
		this->nFilterWidth = sSrc.nFilterWidth;
		this->nFilterHeight = sSrc.nFilterHeight;
		this->nStrideHorizontal = sSrc.nStrideHorizontal;
		this->nStrideVertical = sSrc.nStrideVertical;
		this->nOutputWidth = sSrc.nOutputWidth;
		this->nOutputHeight = sSrc.nOutputHeight;
		this->nZeroPaddingHorizontalNegative = sSrc.nZeroPaddingHorizontalNegative;
		this->nZeroPaddingHorizontalPositive = sSrc.nZeroPaddingHorizontalPositive;
		this->nZeroPaddingVerticalNegative = sSrc.nZeroPaddingVerticalNegative;
		this->nZeroPaddingVerticalPositive = sSrc.nZeroPaddingVerticalPositive;
		this->sBias = sSrc.sBias;
		this->sWeight = sSrc.sWeight;

		return *this;
	}

	ConvLayer &ConvLayer::operator=(ConvLayer &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(sSrc);
		this->nWidth = sSrc.nWidth;
		this->nHeight = sSrc.nHeight;
		this->nChannel = sSrc.nChannel;
		this->nFilter = sSrc.nFilter;
		this->nFilterWidth = sSrc.nFilterWidth;
		this->nFilterHeight = sSrc.nFilterHeight;
		this->nStrideHorizontal = sSrc.nStrideHorizontal;
		this->nStrideVertical = sSrc.nStrideVertical;
		this->nOutputWidth = sSrc.nOutputWidth;
		this->nOutputHeight = sSrc.nOutputHeight;
		this->nZeroPaddingHorizontalNegative = sSrc.nZeroPaddingHorizontalNegative;
		this->nZeroPaddingHorizontalPositive = sSrc.nZeroPaddingHorizontalPositive;
		this->nZeroPaddingVerticalNegative = sSrc.nZeroPaddingVerticalNegative;
		this->nZeroPaddingVerticalPositive = sSrc.nZeroPaddingVerticalPositive;
		this->sBias = std::move(sSrc.sBias);
		this->sWeight = std::move(sSrc.sWeight);

		return *this;
	}

	const char *ConvLayer::name() const
	{
		return "ConvLayer";
	}

	std::unique_ptr<Layer> ConvLayer::duplicate() const
	{
		return std::unique_ptr<ConvLayer>(new ConvLayer(*this));
	}

	void ConvLayer::initBias(std::function<float()> sGenerator)
	{
		for (auto &nBias : this->sBias)
			nBias = sGenerator();
	}

	void ConvLayer::initWeight(std::function<float()> sGenerator)
	{
		for (auto &sWeight : this->sWeight)
			for (auto &sWeight : sWeight)
				for (auto &nWeight : sWeight)
					nWeight = sGenerator();
	}

	void ConvLayer::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nWeightDeltaSize = (nBiasDeltaSize = this->nFilter) * this->nChannel * this->nFilterWidth * this->nFilterHeight;
	}

	void ConvLayer::forward(const float *pInput, float *pOutput) const
	{

	}

	void ConvLayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase) const
	{

	}

	void ConvLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pWeightDelta) const
	{

	}

	void ConvLayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{

	}

	void ConvLayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{

	}

	void ConvLayer::serialize(std::ofstream &sOutput) const
	{
		this->Layer::serialize(sOutput);


	}

	void ConvLayer::deserialize(std::ifstream &sInput)
	{
		this->Layer::deserialize(sInput);


	}
}