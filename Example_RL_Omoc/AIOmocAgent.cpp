
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#include "AIOmocAgent.h"

namespace TinNet_Example
{
	AIOmocAgent::AIOmocAgent(TinNet::NN *pNetwork) :
		pNetwork{pNetwork},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	uint32_t AIOmocAgent::place(const OmocBoard *pOmocBoard)
	{
		std::vector<float> sInput(pOmocBoard->nWidth * pOmocBoard->nHeight);

		for (std::size_t nIndex{0}, nSize{sInput.size()}; nIndex < nSize; ++nIndex)
			sInput[nIndex] = static_cast<float>(pOmocBoard->sBoard[nIndex]);

		this->pNetwork->forward(sInput.data());

		std::size_t nActionSize{0};

		for (auto nPlacement : pOmocBoard->sBoard)
			if (!nPlacement)
				++nActionSize;

		if (!nActionSize)
			return 0;

		std::vector<std::uint32_t> sIndex;
		std::vector<float> sProb;

		sIndex.reserve(nActionSize);
		sProb.reserve(nActionSize);

		for (std::size_t nIndex{0}, nSize{sInput.size()}; nIndex < nSize; ++nIndex)
			if (sInput[nIndex] == .0f)
			{
				sIndex.emplace_back(nIndex);
				sProb.emplace_back(this->pNetwork->output().back()[nIndex]);
			}

		for (std::size_t nIndex{0}, nSize{nActionSize - 1}; nIndex < nSize; ++nIndex)
			sProb[nIndex + 1] += sProb[nIndex];

		std::uniform_real_distribution<float> sDist{0.f, sProb[nActionSize - 1]};
		auto nValue{sDist(this->sEngine)};

		for (std::size_t nIndex{0}, nSize{nActionSize}; nIndex < nSize; ++nIndex)
			if (sProb[nIndex] >= nValue)
				return sIndex[nIndex];

		return sIndex.back();
	}

	void AIOmocAgent::onGameBegin(const OmocBoard *pOmocBoard)
	{
		//Empty.
	}

	void AIOmocAgent::onPlaced(uint32_t nPlacement, const OmocBoard *pOmocBoard)
	{
		//Empty.
	}

	void AIOmocAgent::onPlaceRejected(uint32_t nPlacement, const OmocBoard *pOmocBoard)
	{
		//Empty.
	}

	void AIOmocAgent::onGameEnd(const OmocGameResult *pOmocGameResult)
	{
		//Empty.
	}
}