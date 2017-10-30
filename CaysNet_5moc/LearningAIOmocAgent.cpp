
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "LearningAIOmocAgent.h"

LearningAIOmocAgent::LearningAIOmocAgent(CaysNet::NN *pNewNetwork) :
	pNetwork{pNewNetwork},
	sUpdater{*this->pNetwork, .001f},
	sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
{
	//Empty.
}

int LearningAIOmocAgent::place(const float *pPlace)
{
	this->pNetwork->calc(this->vMap);

	std::uniform_real_distribution<float> sDist{.0f, 1.f};
	auto nValue{sDist(this->sEngine)};

	for (int i = 0; i < 99; ++i)
		this->pNetwork->output().back()[i + 1] += this->pNetwork->output().back()[i];

	for (int i = 0; i < 100; ++i)
		if (this->pNetwork->output().back()[i] >= nValue)
			return i;

	return 99;
}

void LearningAIOmocAgent::handleStart(float nIdentifier)
{
	std::fill(this->vMap, this->vMap + 100, .0f);

	this->vMap[100] = nIdentifier;
	this->sEpList.clear();
}

void LearningAIOmocAgent::handlePlaceRejected(int nPlace)
{
	this->sEpList.emplace_back(Ep
	{
		std::vector<float>(this->vMap, this->vMap + 101),
		nPlace,
		-100.f
	});
}

void LearningAIOmocAgent::handlePlaceOK(int nPlace)
{
	this->sEpList.emplace_back(Ep
	{
		std::vector<float>(this->vMap, this->vMap + 101),
		nPlace,
		1.f
	});

	this->vMap[nPlace] = this->vMap[100];
}

void LearningAIOmocAgent::handlePlaceOtherOK(int nPlace)
{
	this->vMap[nPlace] = -this->vMap[100];
}

void LearningAIOmocAgent::handleWin()
{
	this->sEpList.back().nReward = 25.f;
	this->update();
}

void LearningAIOmocAgent::handleLose()
{
	this->sEpList.back().nReward = -10.f;
	this->update();
}

void LearningAIOmocAgent::handleDraw()
{
	//this->sEpList.back().nReward += 10.f;
	this->update();
}

void LearningAIOmocAgent::update()
{
	int nLastTempAction{0};
	float vTempAction[100]{};
	auto nRewardSum{.0f};
	constexpr float nFactor{.8f};

	for (std::size_t nTime{0}, nLength{this->sEpList.size()}; nTime < nLength; ++nTime)
	{
		nRewardSum = this->sEpList[nTime].nReward + nRewardSum * nFactor;

		vTempAction[nLastTempAction] = .0f;
		vTempAction[nLastTempAction = this->sEpList[nTime].nAction] = 1.f;

		this->sUpdater.update(this->sEpList[nTime].sState.data(), vTempAction, nRewardSum);
	}
}