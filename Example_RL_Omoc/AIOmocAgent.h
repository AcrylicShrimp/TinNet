
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_AIOMOCAGENT_H

#define _CLASS_TINNET_EXAMPLE_AIOMOCAGENT_H

#include "../TinNet/TinNet/TinNet.h"

#include "Omoc.h"

#include <chrono>
#include <random>

namespace TinNet_Example
{
	class AIOmocAgent : public OmocAgent
	{
	private:
		TinNet::NN *pNetwork;
		int vIndexBuffer[100];
		float vProbBuffer[100];
		std::mt19937_64 sEngine;

	public:
		AIOmocAgent(TinNet::NN *pNewNetwork);
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
}

#endif