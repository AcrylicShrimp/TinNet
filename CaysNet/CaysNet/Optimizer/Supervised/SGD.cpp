
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "SGD.h"

namespace CaysNet::Optimizer::Supervised
{
	SGD::SGD(NN &sNN, float nNewLearningRate) :
		nLearningRate{nNewLearningRate},
		sNN{sNN},
		sOutput(sNN.depth()),
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			auto &sLayer{this->sNN[nIndex]};

			this->sOutput[nIndex].resize(sLayer.fanIn(), .0f);
			this->sBiasDelta[nIndex].resize(sLayer.fanOut(), .0f);
			this->sWeightDelta[nIndex].resize(sLayer.fanOut());

			for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}, nInSize{sLayer.fanIn()}; nOut < nOutSize; ++nOut)
				this->sWeightDelta[nIndex][nOut].resize(nInSize, .0f);
		}
	}

	SGD::SGD(SGD &&sSrc) :
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sOutput{std::move(sSrc.sOutput)},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}
}