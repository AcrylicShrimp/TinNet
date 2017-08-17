
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_NN_H

#define _CLASS_CAYSNET_NN_H

#include "Activations.h"
#include "Layer.h"
#include "Serializable.h"

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
	template<class LossFunc> class NN final : public IO::Serializable
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
		float loss(const float *pInput, const float *pOutput);
		float loss(const float **pInput, const float **pOutput, std::size_t nBatchCount);
		float loss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList);
		float loss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList);
		float classificationLoss(const float **pInput, const float **pOutput, std::size_t nBatchCount);
		float classificationLoss(const std::vector<float *> &sInputList, const std::vector<float *> &sOutputList);
		float classificationLoss(const std::vector<std::vector<float>> &sInputList, const std::vector<std::vector<float>> &sOutputList);
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};

	template<class LossFunc> inline Layer &NN<LossFunc>::operator[](std::size_t nIndex)
	{
		return this->sLayerList[nIndex];
	}

	template<class LossFunc> inline const Layer &NN<LossFunc>::operator[](std::size_t nIndex) const
	{
		return this->sLayerList[nIndex];
	}

	template<class LossFunc> inline std::vector<Layer> &NN<LossFunc>::layer()
	{
		return this->sLayerList;
	}

	template<class LossFunc> inline const std::vector<Layer> &NN<LossFunc>::layer() const
	{
		return this->sLayerList;
	}

	template<class LossFunc> inline std::size_t NN<LossFunc>::depth() const
	{
		return this->sLayerList.size();
	}

	template<class LossFunc> inline std::vector<std::vector<float>> &NN<LossFunc>::output()
	{
		return this->sOutputBuffer;
	}

	template<class LossFunc> inline const std::vector<std::vector<float>> &NN<LossFunc>::output() const
	{
		return this->sOutputBuffer;
	}

	template<class LossFunc> void NN<LossFunc>::addLayer(const Layer &sLayer)
	{
		this->sLayerList.emplace_back(sLayer);
		this->sOutputBuffer.emplace_back(this->sLayerList.back().fanOut(), .0f);
	}

	template<class LossFunc> void NN<LossFunc>::addLayer(Layer &&sLayer)
	{
		this->sLayerList.emplace_back(std::move(sLayer));
		this->sOutputBuffer.emplace_back(this->sLayerList.back().fanOut(), .0f);
	}
}

#include "NN.hpp"

#endif