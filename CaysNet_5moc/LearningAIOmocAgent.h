
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_LEARNING_AIOMOC_AGENT_H

#define _CLASS_LEARNING_AIOMOC_AGENT_H

#include "../CaysNet/CaysNet/CaysNet.h"

#include "Omoc.h"

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

struct EpList
{
public:
	std::vector<std::vector<float>> sState;
	std::vector<std::vector<float>> sAction;
	std::vector<float> sReward;
};

class LearningAIOmocAgent : public OmocAgent
{
private:
	CaysNet::NN *pNetwork;
	std::mt19937_64 sEngine;
	EpList sEpList;
	const float *pPlace;
	std::size_t nEpIndex{0};
	CaysNet::Optimizer::Reinforcement::MonteCarloPolicyGradient sUpdater;
	
public:
	LearningAIOmocAgent(CaysNet::NN *pNewNetwork);
	LearningAIOmocAgent(const LearningAIOmocAgent &sSrc) = delete;
	LearningAIOmocAgent(LearningAIOmocAgent &&sSrc) = delete;
	~LearningAIOmocAgent() = default;

public:
	LearningAIOmocAgent &operator=(const LearningAIOmocAgent &sSrc) = delete;
	LearningAIOmocAgent &operator=(LearningAIOmocAgent &&sSrc) = delete;
	
public:
	virtual int place(const float *pPlace) override;
	virtual void handleStart(float nIdentifier) override;
	virtual void handlePlaceRejected(int nPlace) override;
	virtual void handlePlaceOK(int nPlace) override;
	virtual void handlePlaceOtherOK(int nPlace) override;
	virtual void handleWin() override;
	virtual void handleLose() override;
	virtual void handleDraw() override;

private:
	void update();
};

#endif