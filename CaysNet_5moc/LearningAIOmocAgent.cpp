
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
	this->pNetwork->calc(this->pPlace = pPlace);

	for (int i = 0; i < 24; ++i)
		this->pNetwork->output().back()[i + 1] += this->pNetwork->output().back()[i];

	std::uniform_real_distribution<float> sDist{.0f, this->pNetwork->output().back().back()};
	auto nValue{sDist(this->sEngine)};

	for (int i = 0; i < 25; ++i)
		if (this->pNetwork->output().back()[i] >= nValue)
			return i;

	return 24;
}

void LearningAIOmocAgent::handleStart(float nIdentifier)
{
	this->sEpList.clear();
}

void LearningAIOmocAgent::handlePlaceRejected(int nPlace)
{
	this->sEpList.emplace_back(Ep
	{
		std::vector<float>(this->pPlace, this->pPlace + 25),
		nPlace,
		-10.f
	});
}

void LearningAIOmocAgent::handlePlaceOK(int nPlace)
{
	this->sEpList.emplace_back(Ep
	{
		std::vector<float>(this->pPlace, this->pPlace + 25),
		nPlace,
		1.f
	});
}

void LearningAIOmocAgent::handlePlaceOtherOK(int nPlace)
{
	//Empty.
}

void LearningAIOmocAgent::handleWin()
{
	if (this->sEpList.empty())
		return;

	this->sEpList.back().nReward = -1.f;
	this->update();
}

void LearningAIOmocAgent::handleLose()
{
	if (this->sEpList.empty())
		return;

	this->sEpList.back().nReward = 1.f;
	this->update();
}

void LearningAIOmocAgent::handleDraw()
{
	if (this->sEpList.empty())
		return;

	//this->sEpList.back().nReward += 10.f;
	this->update();
}

void LearningAIOmocAgent::update()
{
	if (!this->sEpList.size())
		return;

	int nLastTempAction{0};
	float vTempAction[25]{};
	auto nRewardSum{.0f};
	constexpr float nFactor{.0f};

	//float nRewardAvg{.0f};
	//
	//for (const auto &sEp : this->sEpList)
	//	nRewardAvg += sEp.nReward;
	//
	//nRewardAvg /= this->sEpList.size();

	for (std::size_t nTime{0}, nLength{this->sEpList.size()}; nTime < nLength; ++nTime)
	{
		nRewardSum = this->sEpList[nTime].nReward + nRewardSum * nFactor;

		vTempAction[nLastTempAction] = .0f;
		vTempAction[nLastTempAction = this->sEpList[nTime].nAction] = 1.f;

		//printf("Gradient : %lf", this->sUpdater.checkGradient(this->sEpList[nTime].sState.data(), vTempAction, 0, 0, 0));

		this->sUpdater.update(this->sEpList[nTime].sState.data(), vTempAction, this->sEpList[nTime].nAction, nRewardSum);
	}
}