
/*
	2018.04.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_OMOCOBSERVER_H

#define _CLASS_TINNET_EXAMPLE_OMOCOBSERVER_H

#include "OmocAgent.h"

#include <cstdint>

namespace TinNet_Example
{
	struct OmocBoard;
	struct OmocGameResult;

	class OmocObserver
	{
	public:
		OmocObserver() = default;
		OmocObserver(const OmocObserver &sSrc) = default;
		virtual ~OmocObserver() = default;
		
	public:
		OmocObserver &operator=(const OmocObserver &sSrc) = default;
		
	public:
		virtual void onGameBegin(const OmocBoard *pOmocBoard) = 0;
		virtual void onPlaced(uint32_t nPlacement, const OmocAgent *pOmocAgent, const OmocBoard *pOmocBoard) = 0;
		virtual void onPlaceRejected(uint32_t nPlacement, const OmocAgent *pOmocAgent, const OmocBoard *pOmocBoard) = 0;
		virtual void onGameEnd(const OmocGameResult *pOmocGameResult) = 0;
	};
}

#endif