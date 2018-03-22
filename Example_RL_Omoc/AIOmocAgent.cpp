
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#include "AIOmocAgent.h"

namespace TinNet_Example
{
	AIOmocAgent::AIOmocAgent(TinNet::NN *pNewNetwork) :
		pNetwork{pNewNetwork},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	int AIOmocAgent::place(const float *pPlace)
	{
		this->pNetwork->forward(pPlace);

		int nBufferSize = 0;

		for (int i = 0; i < 81; ++i)
			if (pPlace[i] == .0f)
			{
				this->vIndexBuffer[nBufferSize] = i;
				this->vProbBuffer[nBufferSize] = this->pNetwork->output().back()[i];
				++nBufferSize;
			}

		if (!nBufferSize)
			return 0;

		for (int i = 0; i < nBufferSize - 1; ++i)
			this->vProbBuffer[i + 1] += this->vProbBuffer[i];

		std::uniform_real_distribution<float> sDist{0.f, this->vProbBuffer[nBufferSize - 1]};
		auto nValue{sDist(this->sEngine)};

		for (int i = 0; i < nBufferSize; ++i)
			if (this->vProbBuffer[i] >= nValue)
				return this->vIndexBuffer[i];

		return this->vIndexBuffer[nBufferSize - 1];
	}

	void AIOmocAgent::handleStart(float nIdentifier)
	{
		//Empty.
	}

	void AIOmocAgent::handlePlaceRejected(int nPlace)
	{
		//Empty.
	}

	void AIOmocAgent::handlePlaceOK(int nPlace)
	{
		//Empty.
	}

	void AIOmocAgent::handlePlaceOtherOK(int nPlace)
	{
		//Empty.
	}

	void AIOmocAgent::handleWin()
	{
		//Empty.
	}

	void AIOmocAgent::handleLose()
	{
		//Empty.
	}

	void AIOmocAgent::handleDraw()
	{
		//Empty.
	}
}