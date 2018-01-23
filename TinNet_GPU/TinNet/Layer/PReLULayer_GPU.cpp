
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

	void PReLULayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::PReLULayer_GPU_forward(this->nFanIn, pInput, pOutput, this->nParam);
	}

	void PReLULayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::PReLULayer_GPU_forwardBatch(nBatchSize, this->nFanIn, pInput, pOutput, this->nParam);
	}

	void PReLULayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::PReLULayer_GPU_backwardBatch(nBatchSize, this->nFanIn, pForwardInput, pBackwardInput, pBackwardOutput, this->nParam);
	}

	void PReLULayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}

	void PReLULayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}
}