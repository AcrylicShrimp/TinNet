
/*
	2017.08.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_REINFORCEMENT_ACTOR_CRITIC_H

#define _CLASS_CAYSNET_OPTIMIZER_REINFORCEMENT_ACTOR_CRITIC_H

#include "../../CaysNetDLL.h"

#include "../../Layer.h"
#include "../../NN.h"

#include <utility>

namespace CaysNet::Optimizer::Reinforcement
{
	class CAYSNET_DLL ActorCritic
	{
	private:
		NN &sActor;
		NN &sCritic;
		
	public:
		ActorCritic();
		ActorCritic(const ActorCritic &sSrc);
		ActorCritic(ActorCritic &&sSrc);
		~ActorCritic();
		
	public:
		ActorCritic &operator=(const ActorCritic &sSrc);
		ActorCritic &operator=(ActorCritic &&sSrc);
		
	public:

	};
}

#endif