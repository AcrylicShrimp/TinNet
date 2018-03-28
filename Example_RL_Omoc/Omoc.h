
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_OMOC_H

#define _CLASS_TINNET_EXAMPLE_OMOC_H

#include <algorithm>
#include <cstdint>
#include <memory>

namespace TinNet_Example
{
	class OmocAgent
	{
	public:
		virtual ~OmocAgent() = default;

	public:
		virtual int place(const float *pPlace) = 0;
		virtual void handleStart(float nIdentifier) = 0;
		virtual void handlePlaceRejected(int nPlace) = 0;
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
		virtual void handleGameEnd(const float *pPlace, int nWinner, int nFinalPlace, int nErrorBlack, int nErrorWhite) = 0;
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
		int nErrorBlack;
		int nErrorWhite;

	public:
		Omoc(int nWidth, int nHeight);
		Omoc(const Omoc &sSrc) = delete;
		Omoc(Omoc &&sSrc) = delete;
		~Omoc();

	public:
		Omoc &operator=(const Omoc &sSrc) = delete;
		Omoc &operator=(Omoc &&sSrc) = delete;

	public:
		inline int width() const;
		inline int height() const;
		inline void registerAgent(OmocAgent *pNewBlack, OmocAgent *pNewWhite);
		inline void registerObserver(OmocObserver *pNewObserver);

		void playNewGame();

	private:
		bool nextStep(int *pWinner, int *nFinalPlace);
		bool checkGameWinner(int nPlace, float nIdentifier);
	};

	inline int Omoc::width() const
	{
		return this->nPlaceWidth;
	}

	inline int Omoc::height() const
	{
		return this->nPlaceHeight;
	}

	inline void Omoc::registerAgent(OmocAgent *pNewBlack, OmocAgent *pNewWhite)
	{
		this->pBlack = pNewBlack;
		this->pWhite = pNewWhite;
	}

	inline void Omoc::registerObserver(OmocObserver *pNewObserver)
	{
		this->pObserver = pNewObserver;
	}
}

#endif