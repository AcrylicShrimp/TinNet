
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_CONSOLEOMOCOBSERVER_H

#define _CLASS_TINNET_EXAMPLE_CONSOLEOMOCOBSERVER_H

#include "../TinNet_Dot/TinNet/TinNet_Dot.h"

#include "Omoc.h"

#include <cstdint>
#include <cstdio>

namespace TinNet_Example
{
	class ConsoleOmocObserver : public OmocObserver
	{
	private:
		uint64_t nGameCount;
		uint64_t nNondrawGameCount;
		uint64_t nBlackWinCount;
		uint64_t nWhiteWinCount;
		uint64_t nBlackErrorCount;
		uint64_t nWhiteErrorCount;

	public:
		ConsoleOmocObserver();
		ConsoleOmocObserver(const ConsoleOmocObserver &sSrc) = delete;
		ConsoleOmocObserver(ConsoleOmocObserver &&sSrc) = delete;
		~ConsoleOmocObserver() = default;

	public:
		ConsoleOmocObserver &operator=(const ConsoleOmocObserver &sSrc) = delete;
		ConsoleOmocObserver &operator=(ConsoleOmocObserver &&sSrc) = delete;

	public:
		virtual void handleGameStart() override;
		virtual void handleGameEnd(const float *pPlace, int nWinner, int nFinalPlace, int nErrorBlack, int nErrorWhite) override;
	};
}

#endif