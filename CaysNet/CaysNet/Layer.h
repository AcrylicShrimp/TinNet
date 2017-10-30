
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_H

#define _CLASS_CAYSNET_LAYER_H

#include "CaysNetDLL.h"

#include "IO/Serializable.h"

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace CaysNet
{
	namespace Activation
	{
		class CAYSNET_DLL Activation;
	}

	class CAYSNET_DLL Layer final : public IO::Serializable
	{
	private:
		std::vector<std::vector<float>> sWeight;
		std::vector<float> sBias;
		std::vector<float> sActivationInput;
		std::vector<float> sActivationOutput;
		Activation::Activation *pActivation;

	public:
		Layer(std::size_t nFanIn, std::size_t nFanOut, Activation::Activation *pNewActivation);
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
		inline std::vector<float> &activationInput();
		inline const std::vector<float> &activationInput() const;
		inline std::vector<float> &activationOutput();
		inline const std::vector<float> &activationOutput() const;
		inline Activation::Activation *activation() const;
		inline std::size_t fanIn() const;
		inline std::size_t fanOut() const;
		void forward(const float *pInput, float *pOutput) const;
		void forwardForTrain(const float *pInput, float *pOutput);
		void backward(float *pBackInput, float *pBackOutput) const;
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
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

	inline std::vector<float> &Layer::activationInput()
	{
		return this->sActivationInput;
	}

	inline const std::vector<float> &Layer::activationInput() const
	{
		return this->sActivationInput;
	}

	inline std::vector<float> &Layer::activationOutput()
	{
		return this->sActivationOutput;
	}

	inline const std::vector<float> &Layer::activationOutput() const
	{
		return this->sActivationOutput;
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