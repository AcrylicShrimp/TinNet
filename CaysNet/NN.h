
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_NN_H

#define _CLASS_CAYSNET_NN_H

#include "Layer.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>
#include <vector>

namespace CaysNet
{
	template<class LossFunc> class NN final
	{
	private:
		std::vector<Layer> sLayerList;
		std::vector<std::vector<float>> sOutputBuffer;

	public:
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
}

#include "NN.hpp"

#endif