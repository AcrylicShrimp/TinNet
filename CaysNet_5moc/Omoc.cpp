
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "Omoc.h"

Omoc::Omoc(int nWidth, int nHeight) :
	pPlace{new float[nWidth * nHeight]},
	nPlaceCount{nWidth * nHeight},
	nPlaceWidth{nWidth},
	nPlaceHeight{nHeight}
{
	//Empty.
}

Omoc::~Omoc()
{
	delete[] this->pPlace;
}

void Omoc::playNewGame()
{
	std::fill(this->pPlace, this->pPlace + this->nPlaceCount, .0f);

	this->pObserver->handleGameStart();
	this->pBlack->handleStart(-1.f);
	this->pWhite->handleStart(1.f);

	int nWinner;
	int nFinalPlace;
	while (!this->nextStep(&nWinner, &nFinalPlace));

	this->pObserver->handleGameEnd(this->pPlace, nWinner, nFinalPlace);

	if (nWinner == -1)
	{
		this->pBlack->handleWin();
		this->pWhite->handleLose();
		return;
	}

	if (nWinner == 1)
	{
		this->pBlack->handleLose();
		this->pWhite->handleWin();
		return;
	}

	this->pBlack->handleDraw();
	this->pWhite->handleDraw();
}

bool Omoc::nextStep(int *pWinner, int *nFinalPlace)
{
	int nPlace;

	nPlace = this->pBlack->place(this->pPlace);

	while (this->pPlace[nPlace] != .0f)
	{
		this->pBlack->handlePlaceRejected(nPlace);
		nPlace = this->pBlack->place(this->pPlace);
	}

	this->pBlack->handlePlaceOK(nPlace);
	this->pWhite->handlePlaceOtherOK(nPlace);
	this->pPlace[nPlace] = -1.f;

	if (this->checkGameWinner(nPlace, -1.f))
	{
		*pWinner = -1;
		*nFinalPlace = nPlace;
		return true;
	}

	for (int i = 0; i < this->nPlaceCount; ++i)
		if (this->pPlace[i] == .0f)
			goto WHITE_PART;

	*pWinner = 0;
	*nFinalPlace = -1;
	return true;

WHITE_PART:
	nPlace = this->pWhite->place(this->pPlace);

	while (this->pPlace[nPlace] != .0f)
	{
		this->pWhite->handlePlaceRejected(nPlace);
		nPlace = this->pWhite->place(this->pPlace);
	}

	this->pBlack->handlePlaceOtherOK(nPlace);
	this->pWhite->handlePlaceOK(nPlace);
	this->pPlace[nPlace] = 1.f;

	if (this->checkGameWinner(nPlace, 1.f))
	{
		*pWinner = 1;
		*nFinalPlace = nPlace;
		return true;
	}

	for (int i = 0; i < this->nPlaceCount; ++i)
		if (this->pPlace[i] == .0f)
			return false;

	*pWinner = 0;
	*nFinalPlace = -1;
	return true;
}

bool Omoc::checkGameWinner(int nPlace, float nIdentifier)
{
	int nSum{1};
	int nX{nPlace % this->nPlaceWidth};
	int nY{nPlace / this->nPlaceWidth};

	for (int x = nX - 1; x >= 0 && this->pPlace[nY * this->nPlaceWidth + x] == nIdentifier; --x)
		++nSum;

	for (int x = nX + 1; x < this->nPlaceWidth && this->pPlace[nY * this->nPlaceWidth + x] == nIdentifier; ++x)
		++nSum;

	if (nSum == 5)
		return true;

	nSum = 1;

	for (int y = nY - 1; y >= 0 && this->pPlace[y * this->nPlaceWidth + nX] == nIdentifier; --y)
		++nSum;

	for (int y = nY + 1; y < this->nPlaceHeight && this->pPlace[y * this->nPlaceWidth + nX] == nIdentifier; ++y)
		++nSum;

	if (nSum == 5)
		return true;

	nSum = 1;

	for (int x = nX - 1, y = nY - 1; x >= 0 && y >= 0 && this->pPlace[y * this->nPlaceWidth + x] == nIdentifier; --x, --y)
		++nSum;

	for (int x = nX + 1, y = nY + 1; x < this->nPlaceWidth && y < this->nPlaceHeight && this->pPlace[y * this->nPlaceWidth + x] == nIdentifier; ++x, ++y)
		++nSum;

	if (nSum == 5)
		return true;

	nSum = 1;

	for (int x = nX - 1, y = nY + 1; x >= 0 && y < this->nPlaceHeight && this->pPlace[y * this->nPlaceWidth + x] == nIdentifier; --x, ++y)
		++nSum;

	for (int x = nX + 1, y = nY - 1; x < this->nPlaceWidth && y >= 0 && this->pPlace[y * this->nPlaceWidth + x] == nIdentifier; ++x, --y)
		++nSum;

	if (nSum == 5)
		return true;

	return false;
}