
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_LAYER_GPU_H

#define _CLASS_TINNET_LAYER_LAYER_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "../../../TinNet/TinNet/Layer/LayerBase.h"

#include "cuda.h"

#include <cstddef>
#include <functional>

namespace TinNet::Layer
{
	class TINNET_DLL Layer_GPU : public LayerBase
	{
	protected:
		std::size_t nFanIn;
		std::size_t nFanOut;

	public:
		Layer_GPU(std::size_t nFanIn, std::size_t nFanOut);
		Layer_GPU(const Layer_GPU &sSrc);
		~Layer_GPU() = default;
		
	public:
		Layer_GPU &operator=(const Layer_GPU &sSrc);
		
	public:
		virtual std::size_t fanIn() const override;
		virtual std::size_t fanOut() const override;
		virtual const char *name() const = 0;
		virtual void specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const = 0;
		virtual void forward(CUdeviceptr pInput, CUdeviceptr pOutput) const = 0;
		virtual void forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const = 0;
		virtual void backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const = 0;
		virtual void update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) = 0;
		virtual void update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) = 0;
	};
}

#endif