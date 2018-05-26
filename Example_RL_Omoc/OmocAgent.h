
/*
	2018.03.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_OMOCAGENT_H

#define _CLASS_TINNET_EXAMPLE_OMOCAGENT_H

#include <cstdint>

namespace TinNet_Example
{
	struct OmocBoard;
	struct OmocGameResult;

	class OmocAgent
	{
	protected:
		int32_t nIdentifier;
		
	public:
		OmocAgent();
		OmocAgent(const OmocAgent &sSrc);
		virtual ~OmocAgent() = default;
		
	public:
		OmocAgent &operator=(const OmocAgent &sSrc);

	public:
		inline int32_t &identifier();
		inline int32_t identifier() const;
		virtual uint32_t place(const OmocBoard *pOmocBoard) = 0;
		virtual void onGameBegin(const OmocBoard *pOmocBoard) = 0;
		virtual void onPlaced(uint32_t nPlacement, const OmocBoard *pOmocBoard) = 0;
		virtual void onPlaceRejected(uint32_t nPlacement, const OmocBoard *pOmocBoard) = 0;
		virtual void onGameEnd(const OmocGameResult *pOmocGameResult) = 0;
	};

	inline int32_t &OmocAgent::identifier()
	{
		return this->nIdentifier;
	}

	inline int32_t OmocAgent::identifier() const
	{
		return this->nIdentifier;
	}
}

#endif