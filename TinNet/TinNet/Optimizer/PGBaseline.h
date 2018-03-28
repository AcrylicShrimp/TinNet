
/*
	2018.03.24
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_PGBASELINE_H

#define _CLASS_TINNET_OPTIMIZER_PGBASELINE_H

#include "../TinNetDLL.h"

#include "../Loss/Losses.h"
#include "OptimizerBase.h"

#include <cstddef>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL PGBaseline final
	{
	private:
		OptimizerBase &sValue;
		OptimizerBase &sPolicy;
		
	public:
		PGBaseline(OptimizerBase &sValue, OptimizerBase &sPolicy);
		PGBaseline(const PGBaseline &sSrc) = delete;
		PGBaseline(PGBaseline &&sSrc);
		~PGBaseline() = default;
		
	public:
		PGBaseline &operator=(const PGBaseline &sSrc) = delete;
		PGBaseline &operator=(PGBaseline &&sSrc) = delete;
		
	public:
		inline OptimizerBase &value();
		inline const OptimizerBase &value() const;
		inline OptimizerBase &policy();
		inline const OptimizerBase &policy() const;
		void update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward);
	};

	inline OptimizerBase &PGBaseline::value()
	{
		return this->sValue;
	}

	inline const OptimizerBase &PGBaseline::value() const
	{
		return this->sValue;
	}

	inline OptimizerBase &PGBaseline::policy()
	{
		return this->sPolicy;
	}

	inline const OptimizerBase &PGBaseline::policy() const
	{
		return this->sPolicy;
	}
}

#endif