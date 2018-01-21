
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NN_GPU_H

#define _CLASS_TINNET_NN_GPU_H

#include "../../TinNet/TinNet/TinNetDLL.h"

#include "Layer/Layers_GPU.h"

#include "cuda.h"

#include <cstddef>

namespace TinNet
{
	class TINNET_DLL NN_GPU final
	{
	private:
		std::vector<std::unique_ptr<Layer::Layer_GPU>> sLayerList;
		std::vector<CUdeviceptr> sOutput;
		
	public:
		NN_GPU() = default;
		NN_GPU(const NN_GPU &sSrc) = delete;
		~NN_GPU();
		
	public:
		NN_GPU &operator=(const NN_GPU &sSrc) = delete;
		inline std::unique_ptr<Layer::Layer_GPU> &operator[](std::size_t nIndex);
		inline const std::unique_ptr<Layer::Layer_GPU> &operator[](std::size_t nIndex) const;
		
	public:
		inline std::size_t depth() const;
		inline std::vector<CUdeviceptr> &output();
		inline const std::vector<CUdeviceptr> &output() const;
		inline std::vector<std::unique_ptr<Layer::Layer_GPU>> &layer();
		inline const std::vector<std::unique_ptr<Layer::Layer_GPU>> &layer() const;

		template<class NewLayer, class ...NewLayerInitializerParam> void addLayer(NewLayerInitializerParam && ...sParam);
		template<class Initializer, class ...InitializerParam> void initBias(InitializerParam && ...sParam);
		template<class Initializer, class ...InitializerParam> void initWeight(InitializerParam && ...sParam);

		void forward(const float *pInput, float *pOutput);
		void forward(CUdeviceptr pInput);
		void forward(
			std::size_t nBatchSize,
			CUdeviceptr pInput,
			const CUdeviceptr *pOutput,
			bool bTrainingPhase = false) const;
		void backward(
			std::size_t nBatchSize,
			CUdeviceptr pForwardInput,
			CUdeviceptr pBackwardInput,
			const CUdeviceptr *pForwardOutput,
			const CUdeviceptr *pBackwardOutput,
			const CUdeviceptr *pBiasDelta,
			const CUdeviceptr *pWeightDelta);
		std::size_t classify(const float *pInput);
		std::size_t classify(CUdeviceptr *pInput);

	};

	inline std::unique_ptr<Layer::Layer_GPU> &NN_GPU::operator[](std::size_t nIndex)
	{
		return this->sLayerList[nIndex];
	}

	inline const std::unique_ptr<Layer::Layer_GPU> &NN_GPU::operator[](std::size_t nIndex) const
	{
		return this->sLayerList[nIndex];
	}

	inline std::size_t NN_GPU::depth() const
	{
		return this->sLayerList.size();
	}

	inline std::vector<CUdeviceptr> &NN_GPU::output()
	{
		return this->sOutput;
	}

	inline const std::vector<CUdeviceptr> &NN_GPU::output() const
	{
		return this->sOutput;
	}

	inline std::vector<std::unique_ptr<Layer::Layer_GPU>> &NN_GPU::layer()
	{
		return this->sLayerList;
	}

	inline const std::vector<std::unique_ptr<Layer::Layer_GPU>> &NN_GPU::layer() const
	{
		return this->sLayerList;
	}
}

#include "NN_GPU.hpp"

#endif