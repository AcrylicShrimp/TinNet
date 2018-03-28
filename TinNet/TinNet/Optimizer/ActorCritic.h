
/*
	2018.03.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_ACTORCRITIC_H

#define _CLASS_TINNET_OPTIMIZER_ACTORCRITIC_H

#include "../TinNetDLL.h"

#include "../Loss/Losses.h"
#include "OptimizerBase.h"

#include <cstddef>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL ActorCritic final
	{
	private:
		OptimizerBase &sValue;
		OptimizerBase &sPolicy;
		
	public:
		ActorCritic(OptimizerBase &sValue, OptimizerBase &sPolicy);
		ActorCritic(const ActorCritic &sSrc) = delete;
		ActorCritic(ActorCritic &&sSrc);
		~ActorCritic() = default;
		
	public:
		ActorCritic &operator=(const ActorCritic &sSrc) = delete;
		ActorCritic &operator=(ActorCritic &&sSrc) = delete;
		
	public:
		inline OptimizerBase &value();
		inline const OptimizerBase &value() const;
		inline OptimizerBase &policy();
		inline const OptimizerBase &policy() const;
		void update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward, float nDiscountFactor);
	};

	inline OptimizerBase &ActorCritic::value()
	{
		return this->sValue;
	}

	inline const OptimizerBase &ActorCritic::value() const
	{
		return this->sValue;
	}

	inline OptimizerBase &ActorCritic::policy()
	{
		return this->sPolicy;
	}

	inline const OptimizerBase &ActorCritic::policy() const
	{
		return this->sPolicy;
	}
}

#endif