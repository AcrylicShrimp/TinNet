
/*
	2018.01.24
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_CONVLAYER_GPU_H

#define _CLASS_TINNET_LAYER_CONVLAYER_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "Layer_GPU.h"
#include "../TinNet_GPU_Backend.h"

#include "cuda.h"

namespace TinNet::Layer
{
	class TINNET_DLL ConvLayer_GPU : public Layer_GPU
	{
	protected:
		CUdeviceptr pBias;
		CUdeviceptr pWeight;
		CUdeviceptr pParam;
		std::size_t nWidth;
		std::size_t nHeight;
		std::size_t nChannel;
		std::size_t nFilter;
		std::size_t nFilterWidth;
		std::size_t nFilterHeight;
		std::size_t nStrideHorizontal;
		std::size_t nStrideVertical;
		std::size_t nOutputWidth;
		std::size_t nOutputHeight;
		std::size_t nZeroPaddingHorizontalNegative;
		std::size_t nZeroPaddingHorizontalPositive;
		std::size_t nZeroPaddingVerticalNegative;
		std::size_t nZeroPaddingVerticalPositive;
		
	public:
		ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
					  std::size_t nNewFilterWidth,
					  std::size_t nNewFilterHeight);
		ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
					  std::size_t nNewFilterWidth,
					  std::size_t nNewFilterHeight,
					  std::size_t nNewStrideHorizontal,
					  std::size_t nNewStrideVertical);
		ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
					  std::size_t nNewFilterWidth,
					  std::size_t nNewFilterHeight,
					  std::size_t nNewStrideHorizontal,
					  std::size_t nNewStrideVertical,
					  std::size_t nNewOutputWidth,
					  std::size_t nNewOutputHeight);
		ConvLayer_GPU(const ConvLayer_GPU &sSrc) = delete;
		~ConvLayer_GPU();
		
	public:
		ConvLayer_GPU &operator=(const ConvLayer_GPU &sSrc) = delete;
		
	public:
		virtual const char *name() const override;
		virtual void initBias(std::function<float()> sGenerator) override;
		virtual void initWeight(std::function<float()> sGenerator) override;
		virtual void specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const override;
		virtual void forward(CUdeviceptr pInput, CUdeviceptr pOutput) const override;
		virtual void forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const override;
		virtual void backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const override;
		virtual void update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) override;
		virtual void update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) override;
	};
}

#endif