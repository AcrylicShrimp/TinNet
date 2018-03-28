
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NN_GPU_H

#define _CLASS_TINNET_NN_GPU_H

#include "../../TinNet/TinNet/TinNetDLL.h"

#include "Layer/Layers_GPU.h"

#include "GPUVector.h"

#include <cstddef>
#include <memory>
#include <vector>

namespace TinNet
{
	class TINNET_DLL NN_GPU final
	{
	private:
		std::vector<std::unique_ptr<Layer::Layer_GPU>> sLayerList;
		std::vector<GPUVector> sOutput;
		
	public:
		NN_GPU() = default;
		NN_GPU(const NN_GPU &sSrc) = delete;
		~NN_GPU() = default;
		
	public:
		NN_GPU &operator=(const NN_GPU &sSrc) = delete;
		inline std::unique_ptr<Layer::Layer_GPU> &operator[](std::size_t nIndex);
		inline const std::unique_ptr<Layer::Layer_GPU> &operator[](std::size_t nIndex) const;
		
	public:
		inline std::vector<std::unique_ptr<Layer::Layer_GPU>> &layer();
		inline const std::vector<std::unique_ptr<Layer::Layer_GPU>> &layer() const;
		inline std::size_t depth() const;
		inline std::vector<GPUVector> &output();
		inline const std::vector<GPUVector> &output() const;
		template<class NewLayer, class ...NewLayerInitializerParam> void addLayer(NewLayerInitializerParam && ...sParam);
		template<class Initializer, class ...InitializerParam> void initBias(InitializerParam && ...sParam);
		template<class Initializer, class ...InitializerParam> void initWeight(InitializerParam && ...sParam);
		void forward(const GPUVector &sInput);
		void forward(const GPUVector &sInput, GPUVector &sOutput);
		void forward(
			std::size_t nBatchSize,
			const GPUVector &sInput,
			GPUVector *pOutput,
			bool bTrainingPhase = false) const;
		void forward(
			std::size_t nIndex,
			std::size_t nBatchSize,
			const GPUVector &sInput,
			GPUVector *pOutput,
			bool bTrainingPhase = false) const;
		void backward(
			std::size_t nIndex,
			std::size_t nBatchSize,
			const GPUVector &sForwardInput,
			const GPUVector &sBackwardInput,
			const GPUVector *pForwardOutput,
			GPUVector *pBackwardOutput,
			GPUVector *pBiasDelta,
			GPUVector *pWeightDelta) const;
		std::size_t classify(const GPUVector &sInput);
		void classify(std::size_t nBatchSize, const GPUVector *pInput, std::size_t *pOutput);
		template<class LossFunc> float loss(const GPUVector &sInput, const GPUVector &sOutput);
		template<class LossFunc> float loss(std::size_t nBatchSize, const GPUVector *pInput, const GPUVector *pOutput);
		float classificationLoss(std::size_t nBatchSize, const GPUVector *pInput, const GPUVector *pOutput);
	};

	inline std::unique_ptr<Layer::Layer_GPU> &NN_GPU::operator[](std::size_t nIndex)
	{
		return this->sLayerList[nIndex];
	}

	inline const std::unique_ptr<Layer::Layer_GPU> &NN_GPU::operator[](std::size_t nIndex) const
	{
		return this->sLayerList[nIndex];
	}

	inline std::vector<std::unique_ptr<Layer::Layer_GPU>> &NN_GPU::layer()
	{
		return this->sLayerList;
	}

	inline const std::vector<std::unique_ptr<Layer::Layer_GPU>> &NN_GPU::layer() const
	{
		return this->sLayerList;
	}

	inline std::size_t NN_GPU::depth() const
	{
		return this->sLayerList.size();
	}

	inline std::vector<GPUVector> &NN_GPU::output()
	{
		return this->sOutput;
	}

	inline const std::vector<GPUVector> &NN_GPU::output() const
	{
		return this->sOutput;
	}
}

#include "NN_GPU.hpp"

#endif