
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_NN_H

#define _CLASS_CAYSNET_NN_H

#include "Layer.h"
#include "Activation/Activations.h"
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
	class NN final : public IO::Serializable
	{
	private:
		std::vector<Layer> sLayerList;
		std::vector<std::vector<float>> sOutputBuffer;

	public:
		NN() = default;
		NN(std::initializer_list<Layer> sLayerList);
		NN(const NN &sSrc);
		NN(NN &&sSrc);
		~NN() = default;

	public:
		NN &operator=(const NN &sSrc);
		NN &operator=(NN &&sSrc);
		inline Layer &operator[](std::size_t nIndex);
		inline const Layer &operator[](std::size_t nIndex) const;

	public:
		inline std::vector<Layer> &layer();
		inline const std::vector<Layer> &layer() const;
		inline std::size_t depth() const;
		inline std::vector<std::vector<float>> &output();
		inline const std::vector<std::vector<float>> &output() const;
		inline void addLayer(const Layer &sLayer);
		inline void addLayer(Layer &&sLayer);
		template<class Initializer, class ...InitializerParam> void initWeight(InitializerParam && ...sParam);
		template<class Initializer, class ...InitializerParam> void initBias(InitializerParam && ...sParam);
		void calc(const float *pInput);
		void calc(const float *pInput, float *pOutput);
		void calcForTrain(const float *pInput);
		void calcForTrain(const float *pInput, float *pOutput);
		std::size_t classification(const float *pInput);
		template<class LossFunc> float loss(const float *pInput, const float *pOutput);
		template<class LossFunc> float loss(const float **pInput, const float **pOutput, std::size_t nBatchCount);
		template<class LossFunc> float loss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList);
		template<class LossFunc> float loss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList);
		float classificationLoss(const float **pInput, const float **pOutput, std::size_t nBatchCount);
		float classificationLoss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList);
		float classificationLoss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList);
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};

	inline Layer &NN::operator[](std::size_t nIndex)
	{
		return this->sLayerList[nIndex];
	}

	inline const Layer &NN::operator[](std::size_t nIndex) const
	{
		return this->sLayerList[nIndex];
	}

	inline std::vector<Layer> &NN::layer()
	{
		return this->sLayerList;
	}

	inline const std::vector<Layer> &NN::layer() const
	{
		return this->sLayerList;
	}

	inline std::size_t NN::depth() const
	{
		return this->sLayerList.size();
	}

	inline std::vector<std::vector<float>> &NN::output()
	{
		return this->sOutputBuffer;
	}

	inline const std::vector<std::vector<float>> &NN::output() const
	{
		return this->sOutputBuffer;
	}

	void NN::addLayer(const Layer &sLayer)
	{
		this->sLayerList.emplace_back(sLayer);
		this->sOutputBuffer.emplace_back(this->sLayerList.back().fanOut(), .0f);
	}

	void NN::addLayer(Layer &&sLayer)
	{
		this->sLayerList.emplace_back(std::move(sLayer));
		this->sOutputBuffer.emplace_back(this->sLayerList.back().fanOut(), .0f);
	}
}

#include "NN.hpp"

#endif