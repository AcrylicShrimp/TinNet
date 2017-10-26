
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

	int nBufferSize = 0;

	for (int i = 0; i < 100; ++i)
		if (pPlace[i] == .0f)
		{
			this->vIndexBuffer[nBufferSize] = i;
			this->vProbBuffer[nBufferSize] = this->pNetwork->output().back()[i];
			++nBufferSize;
		}

	if (!nBufferSize)
		return 0;

	for (int i = 0; i < nBufferSize - 1; ++i)
		this->vProbBuffer[i + 1] += this->vProbBuffer[i];

	std::uniform_real_distribution<float> sDist{0.f, this->vProbBuffer[nBufferSize - 1]};
	auto nValue{sDist(this->sEngine)};

	for (int i = 0; i < nBufferSize; ++i)
		if (this->vProbBuffer[i] >= nValue)
			return this->vIndexBuffer[i];

	return this->vIndexBuffer[nBufferSize - 1];
}

void LearningAIOmocAgent::handleStart(float nIdentifier)
{
	std::fill(this->vMap, this->vMap + 100, .0f);

	this->vMap[100] = nIdentifier;
	this->sPlaceList.clear();
	this->sRewardList.clear();
}

void LearningAIOmocAgent::handlePlaceOK(int nPlace)
{
	this->vMap[nPlace] = this->vMap[100];
	this->sPlaceList.emplace_back(nPlace);
	this->sRewardList.emplace_back(.0f);
}

void LearningAIOmocAgent::handlePlaceOtherOK(int nPlace)
{
	this->vMap[nPlace] = -this->vMap[100];
	this->sPlaceList.emplace_back(nPlace);
}

void LearningAIOmocAgent::handleWin()
{
	this->sRewardList.back() = 1.f;
	this->update();
}

void LearningAIOmocAgent::handleLose()
{
	this->sRewardList.back() = -10.f;
	this->update();
}

void LearningAIOmocAgent::handleDraw()
{
	this->sRewardList.back() = .0f;
	this->update();
}

void LearningAIOmocAgent::update()
{
	float vTempMap[101]{};
	float vTempAction[100]{};
	constexpr float nFactor{.95f};
	int nLastTempAction = -1;

	vTempMap[100] = this->vMap[100];

	for (std::size_t nTime{0u}, nPlaceTime{0u}, nLength{this->sRewardList.size()}; nTime < nLength; ++nTime)
	{
		auto nRewardSum{.0f};
		auto nRewardFactor{1.f};

		for (auto nRewardTime{nTime}; nRewardTime < nLength; ++nRewardTime)
		{
			nRewardSum += nRewardFactor * this->sRewardList[nRewardTime];
			nRewardFactor *= nFactor;
		}

		if (nLastTempAction != -1)
			vTempAction[nLastTempAction] = .0f;

		if (this->vMap[100] < .0f)
		{
			vTempMap[this->sPlaceList[nPlaceTime]] = -1.f;
			vTempAction[nLastTempAction = this->sPlaceList[nPlaceTime++]] = 1.f;

			this->sUpdater.update(vTempMap, vTempAction, nRewardSum);

			if (nPlaceTime < this->sPlaceList.size())
				vTempMap[this->sPlaceList[nPlaceTime++]] = 1.f;
		}
		else
		{
			vTempMap[this->sPlaceList[nPlaceTime++]] = -1.f;

			if (nPlaceTime < this->sPlaceList.size())
			{
				vTempMap[this->sPlaceList[nPlaceTime]] = 1.f;
				vTempAction[nLastTempAction = this->sPlaceList[nPlaceTime++]] = 1.f;
			}

			this->sUpdater.update(vTempMap, vTempAction, nRewardSum);
		}
	}
}