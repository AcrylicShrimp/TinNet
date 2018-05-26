
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_CONSOLEOMOCOBSERVER_H

#define _CLASS_TINNET_EXAMPLE_CONSOLEOMOCOBSERVER_H

#include "../TinNet_Dot/TinNet/TinNet_Dot.h"

#include "OmocObserver.h"
#include "Omoc.h"

#include <cstdint>
#include <cstdio>

namespace TinNet_Example
{
	class ConsoleOmocObserver : public OmocObserver
	{
	protected:
		uint64_t nGameCount;
		uint64_t nNondrawGameCount;
		uint64_t nBlackWinCount;
		uint64_t nWhiteWinCount;
		uint64_t nBlackErrorCount;
		uint64_t nWhiteErrorCount;

	public:
		ConsoleOmocObserver();
		ConsoleOmocObserver(const ConsoleOmocObserver &sSrc) = delete;
		~ConsoleOmocObserver() = default;

	public:
		ConsoleOmocObserver &operator=(const ConsoleOmocObserver &sSrc) = delete;

	public:
		virtual void onGameBegin(const OmocBoard *pOmocBoard) override;
		virtual void onPlaced(uint32_t nPlacement, const OmocAgent *pOmocAgent, const OmocBoard *pOmocBoard) override;
		virtual void onPlaceRejected(uint32_t nPlacement, const OmocAgent *pOmocAgent, const OmocBoard *pOmocBoard) override;
		virtual void onGameEnd(const OmocGameResult *pOmocGameResult) override;
		void renderBoard(uint32_t nLastPlacement, const OmocBoard *pOmocBoard) const;
	};
}

#endif