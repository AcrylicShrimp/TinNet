
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_LEARNINGAIOMOCAGENT_H

#define _CLASS_TINNET_EXAMPLE_LEARNINGAIOMOCAGENT_H

#include "../TinNet/TinNet/TinNet.h"

#include "Omoc.h"

#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>
#include <vector>

namespace TinNet_Example
{
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
		TinNet::NN *pNetwork;
		EpList sEpList;
		const float *pPlace;
		TinNet::Optimizer::PGBaseline &sUpdater;
		std::mt19937_64 sEngine;

	public:
		LearningAIOmocAgent(TinNet::NN *pNewNetwork, TinNet::Optimizer::PGBaseline &sNewUpdater);
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
}

#endif