
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_OMOC_H

#define _CLASS_OMOC_H

#include <algorithm>
#include <cstdint>
#include <memory>

class OmocAgent
{
public:
	virtual ~OmocAgent() = default;

public:
	virtual int place(const float *pPlace) = 0;
	virtual void handleStart(float nIdentifier) = 0;
	virtual void handlePlaceOK(int nPlace) = 0;
	virtual void handlePlaceOtherOK(int nPlace) = 0;
	virtual void handleWin() = 0;
	virtual void handleLose() = 0;
	virtual void handleDraw() = 0;
};

class OmocObserver
{
public:
	virtual ~OmocObserver() = default;

public:
	virtual void handleGameStart() = 0;
	virtual void handleGameEnd(const float *pPlace, int nWinner, int nFinalPlace) = 0;
};

class Omoc
{
private:
	float *pPlace;
	int nPlaceCount;
	int nPlaceWidth;
	int nPlaceHeight;
	OmocAgent *pBlack;
	OmocAgent *pWhite;
	OmocObserver *pObserver;
	
public:
	Omoc(int nWidth, int nHeight);
	Omoc(const Omoc &sSrc) = delete;
	Omoc(Omoc &&sSrc) = delete;
	~Omoc();
	
public:
	Omoc &operator=(const Omoc &sSrc) = delete;
	Omoc &operator=(Omoc &&sSrc) = delete;
	
public:
	inline void registerAgent(OmocAgent *pNewBlack, OmocAgent *pNewWhite);
	inline void registerObserver(OmocObserver *pNewObserver);

	void playNewGame();

private:
	bool nextStep(int *pWinner, int *nFinalPlace);
	bool checkGameWinner(int nPlace, float nIdentifier);
};

inline void Omoc::registerAgent(OmocAgent *pNewBlack, OmocAgent *pNewWhite)
{
	this->pBlack = pNewBlack;
	this->pWhite = pNewWhite;
}

inline void Omoc::registerObserver(OmocObserver *pNewObserver)
{
	this->pObserver = pNewObserver;
}

#endif