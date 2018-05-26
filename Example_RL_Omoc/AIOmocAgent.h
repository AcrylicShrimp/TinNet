
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_AIOMOCAGENT_H

#define _CLASS_TINNET_EXAMPLE_AIOMOCAGENT_H

#include "../TinNet/TinNet/TinNet.h"

#include "OmocAgent.h"
#include "Omoc.h"

#include <random>

namespace TinNet_Example
{
	class AIOmocAgent : public OmocAgent
	{
	protected:
		TinNet::NN *pNetwork;
		std::mt19937_64 sEngine;

	public:
		AIOmocAgent(TinNet::NN *pNetwork);
		AIOmocAgent(const AIOmocAgent &sSrc) = delete;
		~AIOmocAgent() = default;

	public:
		AIOmocAgent &operator=(const AIOmocAgent &sSrc) = delete;

	public:
		inline TinNet::NN &network();
		inline const TinNet::NN &network() const;

	public:
		virtual uint32_t place(const OmocBoard *pOmocBoard) override;
		virtual void onGameBegin(const OmocBoard *pOmocBoard) override;
		virtual void onPlaced(uint32_t nPlacement, const OmocBoard *pOmocBoard) override;
		virtual void onPlaceRejected(uint32_t nPlacement, const OmocBoard *pOmocBoard) override;
		virtual void onGameEnd(const OmocGameResult *pOmocGameResult) override;
	};

	inline TinNet::NN &AIOmocAgent::network()
	{
		return *this->pNetwork;
	}

	inline const TinNet::NN &AIOmocAgent::network() const
	{
		return *this->pNetwork;
	}
}

#endif