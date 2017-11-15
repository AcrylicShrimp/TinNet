
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
			std::size_t nBatchSize,
			const std::vector<float> *pInput,
			std::vector<std::vector<float>> *pOutputBuffer);
		void forward(
			std::size_t nBatchSize,
			const std::vector<float> *pInput,
			std::vector<std::vector<float>> *pOutputBuffer,
			std::vector<std::vector<float>> *pActivationInputBuffer,
			std::vector<std::vector<float>> *pActivationOutputBuffer);
		void backward(
			std::size_t nBatchSize,
			const std::vector<float> *pForwardInput,
			const std::vector<float> *pBackwardInput,
			const std::vector<std::vector<float>> *pForwardOutputBuffer,
			const std::vector<std::vector<float>> *pActivationInputBuffer,
			const std::vector<std::vector<float>> *pActivationOutputBuffer,
			std::vector<float> *pBiasDelta,
			std::vector<float> *pWeightDelta,
			std::vector<float> *pBiasDeltaBuffer,
			std::vector<float> *pWeightDeltaBuffer,
			std::vector<std::vector<float>> *pBackwardOutputBuffer) const;
		std::size_t classify(const float *pInput);
		void classify(std::size_t nBatchSize, const std::vector<float> *pInput, std::size_t *pOutput);
		template<class LossFunc> float loss(const float *pInput, const float *pOutput);
		template<class LossFunc> float loss(std::size_t nBatchSize, const std::vector<float> *pInput, const std::vector<float> *pOutput);
		float classificationLoss(std::size_t nBatchSize, const std::vector<float> *pInput, const std::vector<float> *pOutput);
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