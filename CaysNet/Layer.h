
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_H

#define _CLASS_CAYSNET_LAYER_H

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace CaysNet
{
	namespace Activation
	{
		class Activation;
	}

	class Layer final
	{
	private:
		std::vector<std::vector<float>> sWeight;
		std::vector<float> sBias;
		std::vector<float> sActivationInput;
		std::vector<float> sActivationOutput;
		Activation::Activation *pActivation;

	private:
		Layer(std::size_t nFanIn, std::size_t nFanOut, Activation::Activation *pNewActivation);
		
	public:
		Layer(const Layer &sSrc);
		Layer(Layer &&sSrc);
		~Layer();
		
	public:
		Layer &operator=(const Layer &sSrc);
		Layer &operator=(Layer &&sSrc);
		
	public:
		template<class ActivationFunc, class ...ActivationFuncParam> inline static Layer layer(std::size_t nFanIn, std::size_t nFanOut, ActivationFuncParam && ...sActivationFuncParam);
		inline std::vector<std::vector<float>> &weight();
		inline const std::vector<std::vector<float>> &weight() const;
		inline std::vector<float> &bias();
		inline const std::vector<float> &bias() const;
		inline Activation::Activation *activation() const;
		inline std::size_t fanIn() const;
		inline std::size_t fanOut() const;
		void forward(const float *pInput, float *pOutput) const;
		void forwardForTrain(const float *pInput, float *pOutput);
		void backward(float *pBackInput, float *pBackOutput) const;
	};

	template<class ActivationFunc, class ...ActivationFuncParam> inline Layer Layer::layer(std::size_t nFanIn, std::size_t nFanOut, ActivationFuncParam && ...sActivationFuncParam)
	{
		return Layer{nFanIn, nFanOut, new ActivationFunc(std::forward<ActivationFuncParam>(sActivationFuncParam)...)};
	}

	inline std::vector<std::vector<float>> &Layer::weight()
	{
		return this->sWeight;
	}

	inline const std::vector<std::vector<float>> &Layer::weight() const
	{
		return this->sWeight;
	}

	inline std::vector<float> &Layer::bias()
	{
		return this->sBias;
	}

	inline const std::vector<float> &Layer::bias() const
	{
		return this->sBias;
	}

	inline Activation::Activation *Layer::activation() const
	{
		return this->pActivation;
	}

	inline std::size_t Layer::fanIn() const
	{
		return this->sWeight.front().size();
	}

	inline std::size_t Layer::fanOut() const
	{
		return this->sBias.size();
	}
}

#endif