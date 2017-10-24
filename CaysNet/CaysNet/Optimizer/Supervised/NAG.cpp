
/*
	2017.10.24
	Created by AcrylicShrimp.
*/

#include "NAG.h"

namespace CaysNet::Optimizer::Supervised
{
	NAG::NAG(NN &sNN, float nNewMomentumTerm, float nNewLearningRate) :
		nMomentumTerm{nNewMomentumTerm},
		nLearningRate{nNewLearningRate},
		sNN{sNN},
		sOutput{sNN.depth()},
		sBiasDelta{sNN.depth()},
		sBiasMomentum{sNN.depth()},
		sWeightDelta{sNN.depth()},
		sWeightMomentum{sNN.depth()},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			auto &sLayer{this->sNN[nIndex]};

			this->sOutput[nIndex].resize(sLayer.fanIn(), .0f);
			this->sBiasDelta[nIndex].resize(sLayer.fanOut(), .0f);
			this->sBiasMomentum[nIndex].resize(sLayer.fanOut(), .0f);
			this->sWeightDelta[nIndex].resize(sLayer.fanOut());
			this->sWeightMomentum[nIndex].resize(sLayer.fanOut());

			for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}, nInSize{sLayer.fanIn()}; nOut < nOutSize; ++nOut)
			{
				this->sWeightDelta[nIndex][nOut].resize(nInSize, .0f);
				this->sWeightMomentum[nIndex][nOut].resize(nInSize, .0f);
			}
		}
	}
	
	NAG::NAG(NAG &&sSrc) :
		nMomentumTerm{sSrc.nMomentumTerm},
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sOutput{std::move(sSrc.sOutput)},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sBiasMomentum{std::move(sSrc.sBiasMomentum)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sWeightMomentum{std::move(sSrc.sWeightMomentum)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}
}