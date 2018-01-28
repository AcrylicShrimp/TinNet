
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
		Layer(nNewWidth * nNewHeight * nNewChannel, nNewOutputWidth * nNewOutputHeight * nNewFilter),
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
		sWeight(nNewFilter),
		sFuture(nNewFilter)
	{
		if ((this->nZeroPaddingHorizontalNegative = this->nZeroPaddingHorizontalPositive = ((this->nOutputWidth - 1u) * this->nStrideHorizontal + this->nFilterWidth - this->nWidth) / 2u) & 1u)
			++this->nZeroPaddingHorizontalPositive;

		if ((this->nZeroPaddingVerticalNegative = this->nZeroPaddingVerticalPositive = ((this->nOutputHeight - 1u) * this->nStrideVertical + this->nFilterHeight - this->nHeight) / 2u) & 1u)
			++this->nZeroPaddingVerticalPositive;

		for (auto &sWeight : this->sWeight)
		{
			sWeight.resize(this->nChannel);

			for (auto &sWeight : sWeight)
				sWeight.resize(this->nFilterWidth * this->nFilterHeight, .0f);
		}
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
		sWeight{std::move(sSrc.sWeight)},
		sFuture{std::move(sSrc.sFuture)}
	{
		//Empty.
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
		this->sFuture = std::move(sSrc.sFuture);

		return *this;
	}

	const char *ConvLayer::name() const
	{
		return "ConvLayer";
	}

	std::unique_ptr<Layer> ConvLayer::duplicate() const
	{
		//return std::unique_ptr<ConvLayer>(new ConvLayer(*this));
		return std::unique_ptr<ConvLayer>(nullptr);
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
		auto fFilterBehaviour = [&](std::size_t nFilterIndex)
		{
			auto pFilterOutput{pOutput + nFilterIndex * this->nOutputWidth * this->nOutputHeight};

			for (std::size_t nChannelIndex{0}; nChannelIndex < this->nChannel; ++nChannelIndex)
			{
				const auto pChannelInput{pInput + nChannelIndex * this->nWidth * this->nHeight};

				for (std::size_t nOutputIndex{0}, nOutputSize{this->nOutputWidth * this->nOutputHeight}; nOutputIndex < nOutputSize; ++nOutputIndex)
					pFilterOutput[nOutputIndex] = this->sBias[nFilterIndex];

				for (std::size_t nOutputY{0}; nOutputY < this->nOutputHeight; ++nOutputY)
				{
					const auto nStrideOffsetY{nOutputY * this->nStrideVertical};

					for (std::size_t nOutputX{0}; nOutputX < this->nOutputWidth; ++nOutputX)
					{
						const auto nStrideOffsetX{nOutputX * this->nStrideHorizontal};

						for (std::size_t nFilterY{0}; nFilterY < this->nFilterHeight; ++nFilterY)
						{
							const auto nY{nStrideOffsetY + nFilterY};

							if (nY < this->nZeroPaddingVerticalNegative)
								continue;

							if (nY >= this->nZeroPaddingVerticalNegative + this->nHeight)
								continue;

							const auto nInputY{nY - this->nZeroPaddingVerticalNegative};

							for (std::size_t nFilterX{0}; nFilterX < this->nFilterWidth; ++nFilterX)
							{
								const auto nX{nStrideOffsetX + nFilterX};

								if (nX < this->nZeroPaddingHorizontalNegative)
									continue;

								if (nX >= this->nZeroPaddingHorizontalNegative + this->nWidth)
									continue;

								const auto nInputX{nX - this->nZeroPaddingHorizontalNegative};

								pFilterOutput[nOutputY * this->nOutputWidth + nOutputX] +=
									pChannelInput[nInputY * this->nWidth + nInputX] *
									this->sWeight[nFilterIndex][nChannelIndex][nFilterY * this->nFilterWidth + nFilterX];
							}
						}
					}
				}
			}
		};

		for (std::size_t nFilterIndex{1}; nFilterIndex < this->nFilter; ++nFilterIndex)
			this->sFuture[nFilterIndex] = std::async(fFilterBehaviour, nFilterIndex);

		fFilterBehaviour(0);

		for (std::size_t nFilterIndex{1}; nFilterIndex < this->nFilter; ++nFilterIndex)
			this->sFuture[nFilterIndex].wait();
	}

	void ConvLayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase) const
	{
		auto fFilterBehaviour = [&](std::size_t nBatch, std::size_t nFilterIndex)
		{
			auto pFilterOutput{pOutput[nBatch].data() + nFilterIndex * this->nOutputWidth * this->nOutputHeight};

			for (std::size_t nChannelIndex{0}; nChannelIndex < this->nChannel; ++nChannelIndex)
			{
				const auto pChannelInput{pInput[nBatch].data() + nChannelIndex * this->nWidth * this->nHeight};

				for (std::size_t nOutputIndex{0}, nOutputSize{this->nOutputWidth * this->nOutputHeight}; nOutputIndex < nOutputSize; ++nOutputIndex)
					pFilterOutput[nOutputIndex] = this->sBias[nFilterIndex];

				for (std::size_t nOutputY{0}; nOutputY < this->nOutputHeight; ++nOutputY)
				{
					const auto nStrideOffsetY{nOutputY * this->nStrideVertical};

					for (std::size_t nFilterY{0}; nFilterY < this->nFilterHeight; ++nFilterY)
					{
						const auto nY{nStrideOffsetY + nFilterY};

						if (nY < this->nZeroPaddingVerticalNegative)
							continue;

						if (nY >= this->nZeroPaddingVerticalNegative + this->nHeight)
							continue;

						const auto nInputY{nY - this->nZeroPaddingVerticalNegative};

						for (std::size_t nOutputX{0}; nOutputX < this->nOutputWidth; ++nOutputX)
						{
							const auto nStrideOffsetX{nOutputX * this->nStrideHorizontal};

							for (std::size_t nFilterX{0}; nFilterX < this->nFilterWidth; ++nFilterX)
							{
								const auto nX{nStrideOffsetX + nFilterX};

								if (nX < this->nZeroPaddingHorizontalNegative)
									continue;

								if (nX >= this->nZeroPaddingHorizontalNegative + this->nWidth)
									continue;

								const auto nInputX{nX - this->nZeroPaddingHorizontalNegative};

								pFilterOutput[nOutputY * this->nOutputWidth + nOutputX] +=
									pChannelInput[nInputY * this->nWidth + nInputX] *
									this->sWeight[nFilterIndex][nChannelIndex][nFilterY * this->nFilterWidth + nFilterX];
							}
						}
					}
				}
			}
		};

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
		{
			for (std::size_t nFilterIndex{1}; nFilterIndex < this->nFilter; ++nFilterIndex)
				this->sFuture[nFilterIndex] = std::async(fFilterBehaviour, nBatch, nFilterIndex);

			fFilterBehaviour(nBatch, 0);

			for (std::size_t nFilterIndex{1}; nFilterIndex < this->nFilter; ++nFilterIndex)
				this->sFuture[nFilterIndex].wait();
		}
	}

	void ConvLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta) const
	{
		auto fFilterBehaviour = [&](std::size_t nBatch, std::size_t nFilterIndex)
		{
			const auto pFilterBackwardInput{pBackwardInput[nBatch].data() + nFilterIndex * this->nOutputWidth * this->nOutputHeight};
			auto pFilterWeightDelta{pWeightDelta + nFilterIndex * this->nChannel * this->nFilterWidth * this->nFilterHeight};

			for (std::size_t nOutputIndex{0}, nOutputSize{this->nOutputWidth * this->nOutputHeight}; nOutputIndex < nOutputSize; ++nOutputIndex)
				pBiasDelta[nFilterIndex] += pFilterBackwardInput[nOutputIndex];

			for (std::size_t nChannelIndex{0}; nChannelIndex < this->nChannel; ++nChannelIndex)
			{
				const auto pChannelForwardInput{pForwardInput[nBatch].data() + nChannelIndex * this->nWidth * this->nHeight};
				auto pChannelBackwardOutput{pBackwardOutput[nBatch].data() + nChannelIndex * this->nWidth * this->nHeight};
				auto pChannelWeightDelta{pFilterWeightDelta + nChannelIndex * this->nFilterWidth * this->nFilterHeight};

				for (std::size_t nOutputY{0}; nOutputY < this->nOutputHeight; ++nOutputY)
				{
					const auto nStrideOffsetY{nOutputY * this->nStrideVertical};

					for (std::size_t nOutputX{0}; nOutputX < this->nOutputWidth; ++nOutputX)
					{
						const auto nStrideOffsetX{nOutputX * this->nStrideHorizontal};

						for (std::size_t nFilterY{0}; nFilterY < this->nFilterHeight; ++nFilterY)
						{
							const auto nY{nStrideOffsetY + nFilterY};

							if (nY < this->nZeroPaddingVerticalNegative)
								continue;

							if (nY >= this->nZeroPaddingVerticalNegative + this->nHeight)
								continue;

							const auto nInputY{nY - this->nZeroPaddingVerticalNegative};

							for (std::size_t nFilterX{0}; nFilterX < this->nFilterWidth; ++nFilterX)
							{
								const auto nX{nStrideOffsetX + nFilterX};

								if (nX < this->nZeroPaddingHorizontalNegative)
									continue;

								if (nX >= this->nZeroPaddingHorizontalNegative + this->nWidth)
									continue;

								const auto nInputX{nX - this->nZeroPaddingHorizontalNegative};

								pChannelWeightDelta[nFilterY * this->nFilterWidth + nFilterX] +=
									pFilterBackwardInput[nOutputY * this->nOutputWidth + nOutputX] *
									pChannelForwardInput[nInputY * this->nWidth + nInputX];

								pChannelBackwardOutput[nInputY * this->nWidth + nInputX] +=
									pFilterBackwardInput[nOutputY * this->nOutputWidth + nOutputX] *
									this->sWeight[nFilterIndex][nChannelIndex][(this->nFilterHeight - nFilterY) * this->nFilterWidth + (this->nFilterWidth - nFilterX)];
							}
						}
					}
				}
			}
		};

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
		{
			for (std::size_t nFilterIndex{1}; nFilterIndex < this->nFilter; ++nFilterIndex)
				this->sFuture[nFilterIndex] = std::async(fFilterBehaviour, nBatch, nFilterIndex);

			fFilterBehaviour(nBatch, 0);

			for (std::size_t nFilterIndex{1}; nFilterIndex < this->nFilter; ++nFilterIndex)
				this->sFuture[nFilterIndex].wait();
		}
	}

	void ConvLayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{
		for (std::size_t nFilterIndex{0}; nFilterIndex < this->nFilter; ++nFilterIndex)
			this->sBias[nFilterIndex] += pBiasDelta[nFilterIndex];

		for (std::size_t nFilterIndex{0}; nFilterIndex < this->nFilter; ++nFilterIndex)
		{
			auto pFilterWeightDelta{pWeightDelta + nFilterIndex * this->nChannel * this->nFilterWidth * this->nFilterHeight};

			for (std::size_t nChannelIndex{0}; nChannelIndex < this->nChannel; ++nChannelIndex)
			{
				auto pChannelWeightDelta{pFilterWeightDelta + nChannelIndex * this->nFilterWidth * this->nFilterHeight};

				for (std::size_t nFilterY{0}; nFilterY < this->nFilterHeight; ++nFilterY)
					for (std::size_t nFilterX{0}; nFilterX < this->nFilterWidth; ++nFilterX)
						this->sWeight[nFilterIndex][nChannelIndex][nFilterY * this->nFilterWidth + nFilterX] += pChannelWeightDelta[nFilterY * this->nFilterWidth + nFilterX];
			}
		}
	}

	void ConvLayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{
		for (std::size_t nFilterIndex{0}; nFilterIndex < this->nFilter; ++nFilterIndex)
			this->sBias[nFilterIndex] += nFactor * pBiasDelta[nFilterIndex];

		for (std::size_t nFilterIndex{0}; nFilterIndex < this->nFilter; ++nFilterIndex)
		{
			auto pFilterWeightDelta{pWeightDelta + nFilterIndex * this->nChannel * this->nFilterWidth * this->nFilterHeight};

			for (std::size_t nChannelIndex{0}; nChannelIndex < this->nChannel; ++nChannelIndex)
			{
				auto pChannelWeightDelta{pFilterWeightDelta + nChannelIndex * this->nFilterWidth * this->nFilterHeight};

				for (std::size_t nFilterY{0}; nFilterY < this->nFilterHeight; ++nFilterY)
					for (std::size_t nFilterX{0}; nFilterX < this->nFilterWidth; ++nFilterX)
						this->sWeight[nFilterIndex][nChannelIndex][nFilterY * this->nFilterWidth + nFilterX] += nFactor * pChannelWeightDelta[nFilterY * this->nFilterWidth + nFilterX];
			}
		}
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