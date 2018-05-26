
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_LEARNINGAIOMOCAGENT_H

#define _CLASS_TINNET_EXAMPLE_LEARNINGAIOMOCAGENT_H

#include "../TinNet/TinNet/TinNet.h"

#include "AIOmocAgent.h"

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

	class LearningAIOmocAgent : public AIOmocAgent
	{
	protected:
		EpList sEpList;
		TinNet::Optimizer::PGBaseline &sUpdater;

	public:
		LearningAIOmocAgent(TinNet::NN *pNetwork, TinNet::Optimizer::PGBaseline &sUpdater);
		LearningAIOmocAgent(const LearningAIOmocAgent &sSrc) = delete;
		~LearningAIOmocAgent() = default;

	public:
		LearningAIOmocAgent &operator=(const LearningAIOmocAgent &sSrc) = delete;

	public:
		virtual uint32_t place(const OmocBoard *pOmocBoard) override;
		virtual void onGameBegin(const OmocBoard *pOmocBoard) override;
		virtual void onPlaced(uint32_t nPlacement, const OmocBoard *pOmocBoard) override;
		virtual void onPlaceRejected(uint32_t nPlacement, const OmocBoard *pOmocBoard) override;
		virtual void onGameEnd(const OmocGameResult *pOmocGameResult) override;

	protected:
		void update();
	};
}

#endif