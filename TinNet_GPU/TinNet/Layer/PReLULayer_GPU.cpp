
/*
	2018.01.23
	Created by AcrylicShrimp.
*/

#include "PReLULayer_GPU.h"

namespace TinNet::Layer
{
	PReLULayer_GPU::PReLULayer_GPU(std::size_t nFanIn, float nNewParam) :
		Layer_GPU(nFanIn, nFanIn),
		nParam{nNewParam}
	{
		//Empty.
	}
	
	PReLULayer_GPU::PReLULayer_GPU(const PReLULayer_GPU &sSrc) :
		Layer_GPU(sSrc),
		nParam{sSrc.nParam}
	{
		//Empty.
	}

	PReLULayer_GPU &PReLULayer_GPU::operator=(const PReLULayer_GPU &sSrc)
	{
		if (&sSrc == this)
			return *this;
		
		this->Layer_GPU::operator=(sSrc);
		this->nParam = sSrc.nParam;
		
		return *this;
	}

	const char *PReLULayer_GPU::name() const
	{
		return "PReLULayer_GPU";
	}

	void PReLULayer_GPU::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void PReLULayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void PReLULayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void PReLULayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
	{
		::PReLULayer_GPU_forward(this->nFanIn, sInput, sOutput, this->nParam);
	}

	void PReLULayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::PReLULayer_GPU_forwardBatch(nIndex, nBatchSize, this->nFanIn, sInput, sOutput, this->nParam);
	}

	void PReLULayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::PReLULayer_GPU_backwardBatch(nIndex, nBatchSize, this->nFanIn, sForwardInput, sBackwardInput, sBackwardOutput, this->nParam);
	}

	void PReLULayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}

	void PReLULayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}
}