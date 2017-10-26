
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CONSOLE_OMOC_OBSERVER_H

#define _CLASS_CONSOLE_OMOC_OBSERVER_H

#include "Omoc.h"

#include <cstdint>
#include <cstdio>

class ConsoleOmocObserver : public OmocObserver
{
private:
	uint64_t nGameCount;
	uint64_t nNondrawGameCount;
	uint64_t nBlackWinCount;
	uint64_t nWhiteWinCount;
	
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
	virtual void handleGameEnd(const float *pPlace, int nWinner, int nFinalPlace) override;
};

#endif