
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_OMOC_H

#define _CLASS_TINNET_EXAMPLE_OMOC_H

#include "OmocAgent.h"
#include "OmocObserver.h"

#include <cstdint>
#include <vector>

namespace TinNet_Example
{
	struct OmocBoard
	{
		uint32_t nWidth;
		uint32_t nHeight;
		uint32_t nMaxPlacement;
		std::vector<int32_t> sBoard;
	};

	struct OmocGameResult
	{
		bool bDraw;
		OmocAgent *pWinner;
		OmocAgent *pLoser;
		OmocBoard *pBoard;
		OmocAgent *pLastAgent;
		uint32_t nLastPlacement;
	};

	class Omoc
	{
	private:
		OmocBoard sBoard;
		OmocAgent *pBlack;
		OmocAgent *pWhite;
		OmocObserver *pObserver;

	public:
		Omoc(uint32_t nWidth, uint32_t nHeight, uint32_t nMaxPlacement);
		Omoc(const Omoc &sSrc) = delete;
		~Omoc() = default;

	public:
		Omoc &operator=(const Omoc &sSrc) = delete;

	public:
		inline OmocBoard *board();
		inline const OmocBoard *board() const;
		inline void registerAgent(OmocAgent *pNewBlack, OmocAgent *pNewWhite);
		inline void registerObserver(OmocObserver *pNewObserver);
		OmocGameResult playNewGame();

	private:
		bool nextStep(OmocGameResult *pGameResult);
		bool proceedPhase(OmocAgent *pAgent, OmocGameResult *pGameResult);
		bool checkGameWinner(uint32_t nPlacement, int32_t nIdentifier);
	};

	inline OmocBoard *Omoc::board()
	{
		return &this->sBoard;
	}

	inline const OmocBoard *Omoc::board() const
	{
		return &this->sBoard;
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