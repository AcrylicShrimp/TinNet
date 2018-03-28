
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_POLICYGRADIENT_H

#define _CLASS_TINNET_OPTIMIZER_POLICYGRADIENT_H

#include "../TinNetDLL.h"

#include "../Loss/Losses.h"
#include "OptimizerBase.h"

#include <cstddef>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL PolicyGradient final
	{
	private:
		OptimizerBase &sPolicy;
		
	public:
		PolicyGradient(OptimizerBase &sPolicy);
		PolicyGradient(const PolicyGradient &sSrc) = delete;
		PolicyGradient(PolicyGradient &&sSrc);
		~PolicyGradient() = default;
		
	public:
		PolicyGradient &operator=(const PolicyGradient &sSrc) = delete;
		PolicyGradient &operator=(PolicyGradient &&sSrc) = delete;
		
	public:
		inline OptimizerBase &policy();
		inline const OptimizerBase &policy() const;
		void update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward);
	};

	inline OptimizerBase &PolicyGradient::policy()
	{
		return this->sPolicy;
	}

	inline const OptimizerBase &PolicyGradient::policy() const
	{
		return this->sPolicy;
	}
}

#endif