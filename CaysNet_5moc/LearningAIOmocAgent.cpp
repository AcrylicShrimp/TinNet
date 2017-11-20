
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "LearningAIOmocAgent.h"

LearningAIOmocAgent::LearningAIOmocAgent(CaysNet::NN *pNewNetwork) :
	pNetwork{pNewNetwork},
	sUpdater{*this->pNetwork, .0001f},
	sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
{
	//Empty.
}

int LearningAIOmocAgent::place(const float *pPlace)
{
	this->pNetwork->forward(this->pPlace = pPlace);

	for (int i = 0; i < 99; ++i)
		this->pNetwork->output().back()[i + 1] += this->pNetwork->output().back()[i];

	std::uniform_real_distribution<float> sDist{.0f, this->pNetwork->output().back().back()};
	auto nValue{sDist(this->sEngine)};

	for (int i = 0; i < 100; ++i)
		if (this->pNetwork->output().back()[i] >= nValue)
			return i;

	return 99;
}

void LearningAIOmocAgent::handleStart(float nIdentifier)
{
	//Empty.
}

void LearningAIOmocAgent::handlePlaceRejected(int nPlace)
{
	this->sEpList.sState.emplace_back(this->pPlace, this->pPlace + 100);
	this->sEpList.sAction.emplace_back(100u, .0f);
	this->sEpList.sReward.emplace_back(-.0001f);

	this->sEpList.sAction.back()[nPlace] = 1.f;
}

void LearningAIOmocAgent::handlePlaceOK(int nPlace)
{
	this->sEpList.sState.emplace_back(this->pPlace, this->pPlace + 100);
	this->sEpList.sAction.emplace_back(100u, .0f);
	this->sEpList.sReward.emplace_back(.0f);

	this->sEpList.sAction.back()[nPlace] = 1.f;
}

void LearningAIOmocAgent::handlePlaceOtherOK(int nPlace)
{
	//Empty.
}

void LearningAIOmocAgent::handleWin()
{
	this->sEpList.sReward.back() = .0005f;
	this->update();
}

void LearningAIOmocAgent::handleLose()
{
	this->sEpList.sReward.back() = -.001f;
	this->update();
}

void LearningAIOmocAgent::handleDraw()
{
	this->update();
}

void LearningAIOmocAgent::update()
{
	//리워드 업데이트
	for (std::size_t nTime{this->nEpIndex}, nLength{this->sEpList.sState.size()}; nTime < nLength; ++nTime)
	{
		auto nFactor{1.f};
		auto nRewardSum{.0f};

		for (std::size_t nRewardTime{nTime}; nRewardTime < nLength; ++nRewardTime)
		{
			nRewardSum += this->sEpList.sReward[nRewardTime];
			nFactor *= .8f;
		}

		this->sEpList.sReward[nTime] = nRewardSum;
	}

	if ((this->nEpIndex = this->sEpList.sState.size()) < 10000)
		return;

	////업데이트 실시
	//
	//for (;;)
	//{
	//	for (std::size_t nIndex{0}; nIndex < 1000; ++nIndex)
	//		this->sUpdater.update(this->nEpIndex, this->sEpList.sState.data(), this->sEpList.sAction.data(), this->sEpList.sReward.data());
	//
	//	for (std::size_t nTime{0}; nTime < this->nEpIndex; ++nTime)
	//	{
	//
	//	}
	//}

	this->sUpdater.update(this->nEpIndex, this->sEpList.sState.data(), this->sEpList.sAction.data(), this->sEpList.sReward.data());

	//리플레이 메모리 초기화
	this->nEpIndex = 0;
	this->sEpList.sState.clear();
	this->sEpList.sAction.clear();
	this->sEpList.sReward.clear();
}