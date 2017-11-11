
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_NN_H

#define _CLASS_CAYSNET_NN_H

#include "CaysNetDLL.h"

#include "Layer/Layer.h"
#include "IO/Serializable.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <limits>
#include <string>
#include <utility>
#include <vector>

namespace CaysNet
{
	class CAYSNET_DLL NN final : public IO::Serializable
	{
	private:
		std::vector<Layer::Layer *> sLayerList;
		std::vector<std::vector<float>> sOutput;

	public:
		NN() = default;
		NN(std::initializer_list<Layer::Layer *> sLayerList);
		NN(const NN &sSrc);
		NN(NN &&sSrc);
		~NN();

	public:
		NN &operator=(const NN &sSrc);
		NN &operator=(NN &&sSrc);
		inline Layer::Layer *operator[](std::size_t nIndex);
		inline const Layer::Layer *operator[](std::size_t nIndex) const;

	public:
		inline std::vector<Layer::Layer *> &layer();
		inline const std::vector<Layer::Layer *> &layer() const;
		inline std::size_t depth() const;
		inline std::vector<std::vector<float>> &output();
		inline const std::vector<std::vector<float>> &output() const;
		inline void addLayer(Layer::Layer *pLayer);
		template<class Initializer, class ...InitializerParam> void initWeight(InitializerParam && ...sParam);
		template<class Initializer, class ...InitializerParam> void initBias(InitializerParam && ...sParam);
		void forward(const float *pInput);
		void forward(const float *pInput, float *pOutput);
		void forward(
			const float *pInput,
			std::vector<std::vector<float>> &sActivationInputBuffer,
			std::vector<std::vector<float>> &sActivationOutputBuffer);
		void backward(
			const std::vector<std::vector<float>> &sActivationInputBuffer,
			const std::vector<std::vector<float>> &sActivationOutputBuffer,
			std::vector<std::vector<float>> &sBiasDeltaBuffer,
			std::vector<std::vector<float>> &sWeightDeltaBuffer,
			std::vector<std::vector<float>> &sBackwardBuffer,
			const float *pForwardInput,
			const float *pBackwardInput) const;
		std::size_t classify(const float *pInput);
		template<class LossFunc> float loss(const float *pInput, const float *pOutput);
		template<class LossFunc> float loss(const float *const *pInput, const float *const *pOutput, std::size_t nBatchCount);
		template<class LossFunc> float loss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList);
		template<class LossFunc> float loss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList);
		float classificationLoss(const float *const *pInput, const float *const *pOutput, std::size_t nBatchCount);
		float classificationLoss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList);
		float classificationLoss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList);
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};

	inline Layer::Layer *NN::operator[](std::size_t nIndex)
	{
		return this->sLayerList[nIndex];
	}

	inline const Layer::Layer *NN::operator[](std::size_t nIndex) const
	{
		return this->sLayerList[nIndex];
	}

	inline std::vector<Layer::Layer *> &NN::layer()
	{
		return this->sLayerList;
	}

	inline const std::vector<Layer::Layer *> &NN::layer() const
	{
		return this->sLayerList;
	}

	inline std::size_t NN::depth() const
	{
		return this->sLayerList.size();
	}

	inline std::vector<std::vector<float>> &NN::output()
	{
		return this->sOutput;
	}

	inline const std::vector<std::vector<float>> &NN::output() const
	{
		return this->sOutput;
	}

	void NN::addLayer(Layer::Layer *pLayer)
	{
		this->sLayerList.emplace_back(pLayer);
		this->sOutput.emplace_back(this->sLayerList.back()->fanOut(), .0f);
	}
}

#include "NN.hpp"

#endif