
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#include "Adam.h"

namespace TinNet::Optimizer
{
	Adam::Adam(Graph &sGraph, float nBeta1, float nBeta2) :
		OptimizerBase(sGraph),
		nBeta1{nBeta1},
		nBeta2{nBeta2},
		sGradientBeta1{this->OptimizerBase::generateGradientBuffer()},
		sGradientBeta2{this->OptimizerBase::generateGradientBuffer()}
	{
		//Empty.
	}

	void Adam::applyGradient(float nLearningRate)
	{
		this->OptimizerBase::copyGradient(this->sGradient);

		for (std::size_t nInitializableIndex{0}, nMaxInitializableIndex{this->sInitializableList.size()}; nInitializableIndex < nMaxInitializableIndex; ++nInitializableIndex)
		{
			auto &sGradientSizeList{this->sInitializableList[nInitializableIndex]->gradientSizeList()};

			for (std::size_t nGradientIndex{0}, nMaxGradientIndex{sGradientSizeList.size()}; nGradientIndex < nMaxGradientIndex; ++nGradientIndex)
				for (std::size_t nIndex{0}, nMaxIndex{sGradientSizeList[nGradientIndex]}; nIndex < nMaxIndex; ++nIndex)
				{
					this->sGradientBeta1[nInitializableIndex][nGradientIndex][nIndex] = this->nBeta1 * this->sGradientBeta1[nInitializableIndex][nGradientIndex][nIndex] + (1.f - this->nBeta1) * this->sGradient[nInitializableIndex][nGradientIndex][nIndex];
					this->sGradientBeta2[nInitializableIndex][nGradientIndex][nIndex] = this->nBeta2 * this->sGradientBeta2[nInitializableIndex][nGradientIndex][nIndex] + (1.f - this->nBeta2) * this->sGradient[nInitializableIndex][nGradientIndex][nIndex] * this->sGradient[nInitializableIndex][nGradientIndex][nIndex];
				}
		}

		for (std::size_t nInitializableIndex{0}, nMaxInitializableIndex{this->sInitializableList.size()}; nInitializableIndex < nMaxInitializableIndex; ++nInitializableIndex)
		{
			auto &sGradientSizeList{this->sInitializableList[nInitializableIndex]->gradientSizeList()};

			for (std::size_t nGradientIndex{0}, nMaxGradientIndex{sGradientSizeList.size()}; nGradientIndex < nMaxGradientIndex; ++nGradientIndex)
				for (std::size_t nIndex{0}, nMaxIndex{sGradientSizeList[nGradientIndex]}; nIndex < nMaxIndex; ++nIndex)
					this->sGradient[nInitializableIndex][nGradientIndex][nIndex] =
					nLearningRate * (this->sGradientBeta1[nInitializableIndex][nGradientIndex][nIndex] / (1.f - this->nBeta1)) / (std::sqrt(this->sGradientBeta2[nInitializableIndex][nGradientIndex][nIndex] / (1.f - this->nBeta2)) + .0001f);
		}

		this->OptimizerBase::applyGradient(1.f, this->sGradient);
	}
}