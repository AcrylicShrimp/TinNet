
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#include "OptimizerBase.h"

namespace TinNet::Optimizer
{
	OptimizerBase::OptimizerBase(Graph &sGraph) :
		sGraph{sGraph},
		sInitializableList{sGraph.initializableList()},
		sGradient{this->generateGradientBuffer()}
	{
		//Empty.
	}

	void OptimizerBase::reduce(Node &sTargetNode, float nLearningRate)
	{
		this->sGraph.computeGradient(sTargetNode);
		this->applyGradient(nLearningRate);
	}

	void OptimizerBase::copyGradient(Gradient &sGradient, float nFactor)
	{
		for (std::size_t nInitializableIndex{0}, nMaxInitializableIndex{this->sInitializableList.size()}; nInitializableIndex < nMaxInitializableIndex; ++nInitializableIndex)
			for (std::size_t nIndex{0}, nMaxIndex{this->sInitializableList[nInitializableIndex]->gradientSizeList().size()}; nIndex < nMaxIndex; ++nIndex)
				Cache{sGradient[nInitializableIndex][nIndex]}.copy(this->sInitializableList[nInitializableIndex]->gradientList()[nIndex]->sCache, nFactor);
	}

	void OptimizerBase::accumulateGradient(Gradient &sGradient, float nFactor)
	{
		for (std::size_t nInitializableIndex{0}, nMaxInitializableIndex{this->sInitializableList.size()}; nInitializableIndex < nMaxInitializableIndex; ++nInitializableIndex)
			for (std::size_t nIndex{0}, nMaxIndex{this->sInitializableList[nInitializableIndex]->gradientSizeList().size()}; nIndex < nMaxIndex; ++nIndex)
				Cache{sGradient[nInitializableIndex][nIndex]}.accumulate(this->sInitializableList[nInitializableIndex]->gradientList()[nIndex]->sCache, nFactor);
	}

	void OptimizerBase::applyGradient(float nLearningRate, Gradient &sGradient)
	{
		for (std::size_t nInitializableIndex{0}, nMaxInitializableIndex{this->sInitializableList.size()}; nInitializableIndex < nMaxInitializableIndex; ++nInitializableIndex)
		{
			for (std::size_t nIndex{0}, nMaxIndex{this->sInitializableList[nInitializableIndex]->gradientSizeList().size()}; nIndex < nMaxIndex; ++nIndex)
				this->sInitializableList[nInitializableIndex]->gradientList()[nIndex]->sCache.copy(sGradient[nInitializableIndex][nIndex]);

			this->sInitializableList[nInitializableIndex]->applyGradient(-nLearningRate);
		}
	}

	Gradient OptimizerBase::generateGradientBuffer()
	{
		Gradient sGradientBuffer(this->sInitializableList.size());

		for (std::size_t nInitializableIndex{0}, nMaxInitializableIndex{this->sInitializableList.size()}; nInitializableIndex < nMaxInitializableIndex; ++nInitializableIndex)
		{
			auto &sGradient{sGradientBuffer[nInitializableIndex]};
			auto &sVariableGradientList{this->sInitializableList[nInitializableIndex]->gradientSizeList()};

			sGradient.resize(sVariableGradientList.size());

			for (std::size_t nIndex{0}, nMaxIndex{sVariableGradientList.size()}; nIndex < nMaxIndex; ++nIndex)
				sGradient[nIndex].resize(sVariableGradientList[nIndex], .0f);
		}

		return sGradientBuffer;
	}
}