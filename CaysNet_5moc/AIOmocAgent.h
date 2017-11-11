
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_AIOMOC_AGENT_H

#define _CLASS_AIOMOC_AGENT_H

#include "../CaysNet/CaysNet/CaysNet.h"

#include "Omoc.h"

#include <chrono>
#include <random>

class AIOmocAgent : public OmocAgent
{
private:
	CaysNet::NN *pNetwork;
	int vIndexBuffer[25];
	float vProbBuffer[25];
	std::mt19937_64 sEngine;
	
public:
	AIOmocAgent(CaysNet::NN *pNewNetwork);
	AIOmocAgent(const AIOmocAgent &sSrc) = delete;
	AIOmocAgent(AIOmocAgent &&sSrc) = delete;
	~AIOmocAgent() = default;
	
public:
	AIOmocAgent &operator=(const AIOmocAgent &sSrc) = delete;
	AIOmocAgent &operator=(AIOmocAgent &&sSrc) = delete;
	
public:
	virtual int place(const float *pPlace) override;
	virtual void handleStart(float nIdentifier) override;
	virtual void handlePlaceRejected(int nPlace) override;
	virtual void handlePlaceOK(int nPlace) override;
	virtual void handlePlaceOtherOK(int nPlace) override;
	virtual void handleWin() override;
	virtual void handleLose() override;
	virtual void handleDraw() override;
};

#endif