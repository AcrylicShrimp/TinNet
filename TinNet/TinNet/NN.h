
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NN_H

#define _CLASS_TINNET_NN_H

#include "TinNetDLL.h"

#include "Layer/Layer.h"
#include "Layer/LayerIO.h"
#include "IO/Serializable.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <limits>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace TinNet
{
	class TINNET_DLL NN final : public IO::Serializable
	{
	private:
		std::vector<std::unique_ptr<Layer::Layer>> sLayerList;
		std::vector<std::vector<float>> sOutput;

	public:
		NN() = default;
		NN(const NN &sSrc);
		NN(NN &&sSrc);
		~NN();

	public:
		NN &operator=(const NN &sSrc);
		NN &operator=(NN &&sSrc);
		inline std::unique_ptr<Layer::Layer> &operator[](std::size_t nIndex);
		inline const std::unique_ptr<Layer::Layer> &operator[](std::size_t nIndex) const;

	public:
		inline std::vector<std::unique_ptr<Layer::Layer>> &layer();
		inline const std::vector<std::unique_ptr<Layer::Layer>> &layer() const;
		inline std::size_t depth() const;
		inline std::vector<std::vector<float>> &output();
		inline const std::vector<std::vector<float>> &output() const;
		template<class NewLayer, class ...NewLayerInitializerParam> void addLayer(NewLayerInitializerParam && ...sParam);
		template<class Initializer, class ...InitializerParam> void initWeight(InitializerParam && ...sParam);
		template<class Initializer, class ...InitializerParam> void initBias(InitializerParam && ...sParam);
		void forward(const float *pInput);
		void forward(const float *pInput, float *pOutput);
		void forward(
			std::size_t nBatchSize,
			const std::vector<float> *pInput,
			std::vector<std::vector<float>> *pOutput,
			bool bTrainingPhase = false) const;
		void backward(
			std::size_t nBatchSize,
			const std::vector<float> *pForwardInput,
			const std::vector<float> *pBackwardInput,
			const std::vector<std::vector<float>> *pForwardOutput,
			std::vector<std::vector<float>> *pBackwardOutput,
			std::vector<float> *pBiasDelta,
			std::vector<float> *pWeightDelta) const;
		std::size_t classify(const float *pInput);
		void classify(std::size_t nBatchSize, const std::vector<float> *pInput, std::size_t *pOutput);
		template<class LossFunc> float loss(const float *pInput, const float *pOutput);
		template<class LossFunc> float loss(std::size_t nBatchSize, const std::vector<float> *pInput, const std::vector<float> *pOutput);
		float classificationLoss(std::size_t nBatchSize, const std::vector<float> *pInput, const std::vector<float> *pOutput);
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};

	inline std::unique_ptr<Layer::Layer> &NN::operator[](std::size_t nIndex)
	{
		return this->sLayerList[nIndex];
	}

	inline const std::unique_ptr<Layer::Layer> &NN::operator[](std::size_t nIndex) const
	{
		return this->sLayerList[nIndex];
	}

	inline std::vector<std::unique_ptr<Layer::Layer>> &NN::layer()
	{
		return this->sLayerList;
	}

	inline const std::vector<std::unique_ptr<Layer::Layer>> &NN::layer() const
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
}

#include "NN.hpp"

#endif