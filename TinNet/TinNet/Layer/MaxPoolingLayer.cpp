
/*
	2018.01.17
	Created by AcrylicShrimp.
*/

#include "MaxPoolingLayer.h"

namespace TinNet::Layer
{
	MaxPoolingLayer::MaxPoolingLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel,
									 std::size_t nNewPoolingWidth,
									 std::size_t nNewPoolingHeight) :
		MaxPoolingLayer(nNewWidth, nNewHeight, nNewChannel,
						nNewPoolingWidth,
						nNewPoolingHeight,
						nNewPoolingWidth,
						nNewPoolingHeight)
	{
		//Empty.
	}

	MaxPoolingLayer::MaxPoolingLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel,
									 std::size_t nNewPoolingWidth,
									 std::size_t nNewPoolingHeight,
									 std::size_t nStrideHorizontal,
									 std::size_t nStrideVertical) :
		Layer(nNewWidth * nNewHeight * nNewChannel, ((nNewWidth - nNewPoolingWidth) / nStrideHorizontal + 1) * ((nNewHeight - nNewPoolingHeight) / nStrideVertical + 1) * nNewChannel),
		nWidth{nNewWidth},
		nHeight{nNewHeight},
		nChannel{nNewChannel},
		nPoolingWidth{nNewPoolingWidth},
		nPoolingHeight{nNewPoolingHeight},
		nStrideHorizontal{nStrideHorizontal},
		nStrideVertical{nStrideVertical},
		nOutputWidth{(nNewWidth - nNewPoolingWidth) / nStrideHorizontal + 1},
		nOutputHeight{(nNewHeight - nNewPoolingHeight) / nStrideVertical + 1},
		sMax(nNewPoolingWidth * nNewPoolingHeight, .0f),
		sMaxPosition(nNewPoolingWidth * nNewPoolingHeight)
	{
		//Empty.
	}

	MaxPoolingLayer::MaxPoolingLayer(const MaxPoolingLayer &sSrc) :
		Layer(sSrc)
	{

	}

	MaxPoolingLayer::MaxPoolingLayer(MaxPoolingLayer &&sSrc) :
		Layer(sSrc)
	{

	}

	MaxPoolingLayer &MaxPoolingLayer::operator=(const MaxPoolingLayer &sSrc)
	{
		if (&sSrc == this)
			return *this;



		return *this;
	}

	MaxPoolingLayer &MaxPoolingLayer::operator=(MaxPoolingLayer &&sSrc)
	{
		if (&sSrc == this)
			return *this;



		return *this;
	}

	const char *MaxPoolingLayer::name() const
	{
		return "MaxPoolingLayer";
	}

	std::unique_ptr<Layer> MaxPoolingLayer::duplicate() const
	{
		return std::unique_ptr<MaxPoolingLayer>(new MaxPoolingLayer(*this));
	}

	void MaxPoolingLayer::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void MaxPoolingLayer::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void MaxPoolingLayer::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0u;
	}

	void MaxPoolingLayer::forward(const float *pInput, float *pOutput) const
	{
		for (std::size_t nChannelIndex{0}; nChannelIndex < this->nChannel; ++nChannelIndex)
		{
			const auto pChannelInput{pInput + nChannelIndex * this->nWidth * this->nHeight};
			auto pChannelOutput{pOutput + nChannelIndex * this->nOutputWidth * this->nOutputHeight};

			for (std::size_t nOutputY{0}; nOutputY < this->nOutputHeight; ++nOutputY)
			{
				const auto nStrideOffsetY{nOutputY * this->nStrideVertical};

				for (std::size_t nOutputX{0}; nOutputX < this->nOutputWidth; ++nOutputX)
				{
					const auto nStrideOffsetX{nOutputX * this->nStrideHorizontal};

					for (std::size_t nPoolingY{0}; nPoolingY < this->nPoolingHeight; ++nPoolingY)
					{
						const auto nY{nStrideOffsetY + nPoolingY};

						for (std::size_t nPoolingX{0}; nPoolingX < this->nPoolingWidth; ++nPoolingX)
						{
							const auto nX{nStrideOffsetX + nPoolingX};

							this->sMax[nPoolingY * this->nPoolingWidth + nPoolingX] = pChannelInput[nY * this->nWidth + nX];
						}
					}

					pChannelOutput[nOutputY * this->nOutputWidth + nOutputX] = *std::max_element(this->sMax.cbegin(), this->sMax.cend());
				}
			}
		}
	}

	void MaxPoolingLayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nChannelIndex{0}; nChannelIndex < this->nChannel; ++nChannelIndex)
			{
				const auto pChannelInput{pInput[nBatch].data() + nChannelIndex * this->nWidth * this->nHeight};
				auto pChannelOutput{pOutput[nBatch].data() + nChannelIndex * this->nOutputWidth * this->nOutputHeight};

				for (std::size_t nOutputY{0}; nOutputY < this->nOutputHeight; ++nOutputY)
				{
					const auto nStrideOffsetY{nOutputY * this->nStrideVertical};

					for (std::size_t nOutputX{0}; nOutputX < this->nOutputWidth; ++nOutputX)
					{
						const auto nStrideOffsetX{nOutputX * this->nStrideHorizontal};

						for (std::size_t nPoolingY{0}; nPoolingY < this->nPoolingHeight; ++nPoolingY)
						{
							const auto nY{nStrideOffsetY + nPoolingY};

							for (std::size_t nPoolingX{0}; nPoolingX < this->nPoolingWidth; ++nPoolingX)
							{
								const auto nX{nStrideOffsetX + nPoolingX};

								this->sMax[nPoolingY * this->nPoolingWidth + nPoolingX] = pChannelInput[nY * this->nWidth + nX];
							}
						}

						pChannelOutput[nOutputY * this->nOutputWidth + nOutputX] = *std::max_element(this->sMax.cbegin(), this->sMax.cend());
					}
				}
			}
	}

	void MaxPoolingLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nChannelIndex{0}; nChannelIndex < this->nChannel; ++nChannelIndex)
			{
				const auto pChannelForwardInput{pForwardInput[nBatch].data() + nChannelIndex * this->nWidth * this->nHeight};
				const auto pChannelBackwardInput{pBackwardInput[nBatch].data() + nChannelIndex * this->nOutputWidth * this->nOutputHeight};
				auto pChannelBackwardOutput{pBackwardOutput[nBatch].data() + nChannelIndex * this->nWidth * this->nHeight};

				for (std::size_t nOutputY{0}; nOutputY < this->nOutputHeight; ++nOutputY)
				{
					const auto nStrideOffsetY{nOutputY * this->nStrideVertical};

					for (std::size_t nOutputX{0}; nOutputX < this->nOutputWidth; ++nOutputX)
					{
						const auto nStrideOffsetX{nOutputX * this->nStrideHorizontal};

						for (std::size_t nPoolingY{0}; nPoolingY < this->nPoolingHeight; ++nPoolingY)
						{
							const auto nY{nStrideOffsetY + nPoolingY};

							for (std::size_t nPoolingX{0}; nPoolingX < this->nPoolingWidth; ++nPoolingX)
							{
								const auto nX{nStrideOffsetX + nPoolingX};

								this->sMax[nPoolingY * this->nPoolingWidth + nPoolingX] = pChannelForwardInput[nY * this->nWidth + nX];
								this->sMaxPosition[nPoolingY * this->nPoolingWidth + nPoolingX] = std::make_tuple(nPoolingX, nPoolingY);
							}
						}

						auto sPosition{this->sMaxPosition[std::distance(this->sMax.cbegin(), std::max_element(this->sMax.cbegin(), this->sMax.cend()))]};
						pChannelBackwardOutput[(nStrideOffsetY + std::get<1>(sPosition)) * this->nWidth + (nStrideOffsetX + std::get<0>(sPosition))] = pChannelBackwardInput[nOutputY * this->nOutputWidth + nOutputX];
					}
				}
			}
	}

	void MaxPoolingLayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void MaxPoolingLayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void MaxPoolingLayer::serialize(std::ofstream &sOutput) const
	{
		this->Layer::serialize(sOutput);


	}

	void MaxPoolingLayer::deserialize(std::ifstream &sInput)
	{
		this->Layer::deserialize(sInput);


	}
}