
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#include "LearningAIOmocAgent.h"

namespace TinNet_Example
{
	LearningAIOmocAgent::LearningAIOmocAgent(TinNet::NN *pNetwork, TinNet::Optimizer::PGBaseline &sUpdater) :
		AIOmocAgent(pNetwork),
		sUpdater{sUpdater}
	{
		//Empty.
	}

	uint32_t LearningAIOmocAgent::place(const OmocBoard *pOmocBoard)
	{
		std::vector<float> sInput(pOmocBoard->nWidth * pOmocBoard->nHeight);

		for (std::size_t nIndex{0}, nSize{sInput.size()}; nIndex < nSize; ++nIndex)
			sInput[nIndex] = static_cast<float>(pOmocBoard->sBoard[nIndex]);

		this->pNetwork->forward(sInput.data());

		for (int i = 0; i < 80; ++i)
			this->pNetwork->output().back()[i + 1] += this->pNetwork->output().back()[i];

		std::uniform_real_distribution<float> sDist{.0f, this->pNetwork->output().back().back()};
		auto nValue{sDist(this->sEngine)};

		for (int i = 0; i < 81; ++i)
			if (this->pNetwork->output().back()[i] >= nValue)
				return i;

		return 80;
	}

	void LearningAIOmocAgent::onGameBegin(const OmocBoard *pOmocBoard)
	{
		//Empty.
	}

	void LearningAIOmocAgent::onPlaced(uint32_t nPlacement, const OmocBoard *pOmocBoard)
	{
		this->sEpList.sState.emplace_back(pOmocBoard->sBoard.begin(), pOmocBoard->sBoard.end());
		this->sEpList.sAction.emplace_back(pOmocBoard->nWidth * pOmocBoard->nHeight, .0f);
		this->sEpList.sReward.emplace_back(.05f);

		this->sEpList.sAction.back()[nPlacement] = 1.f;
	}

	void LearningAIOmocAgent::onPlaceRejected(uint32_t nPlacement, const OmocBoard *pOmocBoard)
	{
		this->sEpList.sState.emplace_back(pOmocBoard->sBoard.begin(), pOmocBoard->sBoard.end());
		this->sEpList.sAction.emplace_back(pOmocBoard->nWidth * pOmocBoard->nHeight, .0f);
		this->sEpList.sReward.emplace_back(-100.f);

		this->sEpList.sAction.back()[nPlacement] = 1.f;
	}

	void LearningAIOmocAgent::onGameEnd(const OmocGameResult *pOmocGameResult)
	{
		if (pOmocGameResult->pWinner == this)
			this->sEpList.sReward.back() = 1.f;
		else if (pOmocGameResult->pLoser == this)
			this->sEpList.sReward.back() = -1.f;

		this->update();
	}

	void LearningAIOmocAgent::update()
	{
		constexpr float nLambda = .9f;
		auto nReward{.0f};

		//리워드 업데이트
		for (std::size_t nTime{this->sEpList.sState.size() - 1}; ; --nTime)
		{
			nReward = nLambda * nReward + this->sEpList.sReward[nTime];
			this->sEpList.sReward[nTime] = nReward;

			if (!nTime)
				break;
		}

		//auto nLength{static_cast<float>(this->sEpList.sState.size())};
		//auto nMean{std::accumulate(this->sEpList.sReward.cbegin(), this->sEpList.sReward.cend(), .0f) / nLength};
		//auto nStd{std::sqrtf(std::inner_product(this->sEpList.sReward.cbegin(), this->sEpList.sReward.cend(), this->sEpList.sReward.cbegin(), .0f) / nLength - nMean * nMean)};
		//
		//std::transform(this->sEpList.sReward.begin(), this->sEpList.sReward.end(), this->sEpList.sReward.begin(), [nMean, nStd](auto nElement)
		//{
		//	return nElement / (nStd + 1e-4f);
		//});

		this->sUpdater.update(this->sEpList.sState.size(), this->sEpList.sState.data(), this->sEpList.sAction.data(), this->sEpList.sReward.data());

		//리플레이 메모리 초기화
		this->sEpList.sState.clear();
		this->sEpList.sAction.clear();
		this->sEpList.sReward.clear();
	}
}