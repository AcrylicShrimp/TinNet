
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_H

#define _CLASS_CAYSNET_LAYER_H

#include <cassert>
#include <cstddef>
#include <cstdint>
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
		Activation::Activation *pActivation;
		
	public:
		Layer(std::size_t nFanIn, std::size_t nFanOut);
		Layer(const Layer &sSrc);
		Layer(Layer &&sSrc);
		~Layer() = default;
		
	public:
		Layer &operator=(const Layer &sSrc);
		Layer &operator=(Layer &&sSrc);
		
	public:
		inline std::vector<std::vector<float>> &weight();
		inline const std::vector<std::vector<float>> &weight() const;
		inline std::vector<float> &bias();
		inline const std::vector<float> &bias() const;
		inline Activation::Activation * &activation();
		inline Activation::Activation *activation() const;
		inline std::size_t fanIn() const;
		inline std::size_t fanOut() const;
		void calc(const float *pInput, float *pOutput) const;
	};

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

	inline Activation::Activation * &Layer::activation()
	{
		return this->pActivation;
	}

	inline Activation::Activation *Layer::activation() const
	{
		return this->pActivation;
	}

	inline std::size_t Layer::fanIn() const
	{
		return this->sWeight.size();
	}

	inline std::size_t Layer::fanOut() const
	{
		return this->sBias.size();
	}
}

#endif