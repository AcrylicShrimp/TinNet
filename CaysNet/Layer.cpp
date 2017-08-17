
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Layer.h"

#include "Activation.h"

namespace CaysNet
{
	Layer::Layer(std::size_t nFanIn, std::size_t nFanOut, Activation::Activation *pNewActivation) :
		sWeight(nFanOut, std::vector<float>(nFanIn, .0f)),
		sBias(nFanOut),
		sActivationInput(nFanOut, .0f),
		sActivationOutput(nFanOut, .0f),
		pActivation{pNewActivation}
	{
		//Empty.
	}

	Layer::Layer(const Layer &sSrc) :
		sWeight{sSrc.sWeight},
		sBias{sSrc.sBias},
		sActivationInput{sSrc.sActivationInput},
		sActivationOutput{sSrc.sActivationOutput},
		pActivation{sSrc.pActivation->duplicate()}
	{
		//Empty.
	}

	Layer::Layer(Layer &&sSrc) :
		sWeight{std::move(sSrc.sWeight)},
		sBias{std::move(sSrc.sBias)},
		sActivationInput{std::move(sSrc.sActivationInput)},
		sActivationOutput{std::move(sSrc.sActivationOutput)},
		pActivation{sSrc.pActivation}
	{
		sSrc.pActivation = nullptr;
	}

	Layer::~Layer()
	{
		if (this->pActivation)
			delete this->pActivation;

		this->pActivation = nullptr;
	}

	Layer &Layer::operator=(const Layer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Layer();

		this->sWeight = sSrc.sWeight;
		this->sBias = sSrc.sBias;
		this->sActivationInput = sSrc.sActivationInput;
		this->sActivationOutput = sSrc.sActivationOutput;
		this->pActivation = sSrc.pActivation->duplicate();

		return *this;
	}

	Layer &Layer::operator=(Layer &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Layer();

		this->sWeight = std::move(sSrc.sWeight);
		this->sBias = std::move(sSrc.sBias);
		this->sActivationInput = std::move(sSrc.sActivationInput);
		this->sActivationOutput = std::move(sSrc.sActivationOutput);
		this->pActivation = sSrc.pActivation;

		sSrc.pActivation = nullptr;

		return *this;
	}

	void Layer::forward(const float *pInput, float *pOutput) const
	{
		assert(this->pActivation);

		//z = X * W + b
		for (std::size_t nOut{0}, nOutSize{this->fanOut()}; nOut < nOutSize; ++nOut)
		{
			auto &nDestination{pOutput[nOut] = this->sBias[nOut]};

			for (std::size_t nIn{0}, nInSize{this->fanIn()}; nIn < nInSize; ++nIn)
				nDestination += pInput[nIn] * this->sWeight[nOut][nIn];
		}

		//a = f(z)
		this->pActivation->activate(this, pOutput);
	}

	void Layer::forwardForTrain(const float *pInput, float *pOutput)
	{
		assert(this->pActivation);

		//z = X * W + b
		for (std::size_t nOut{0}, nOutSize{this->fanOut()}; nOut < nOutSize; ++nOut)
		{
			auto &nDestination{this->sActivationOutput[nOut] = this->sBias[nOut]};

			for (std::size_t nIn{0}, nInSize{this->fanIn()}; nIn < nInSize; ++nIn)
				nDestination += pInput[nIn] * this->sWeight[nOut][nIn];

			//Save the network outputs.
			this->sActivationInput[nOut] = nDestination;
		}

		//a = f(z)
		this->pActivation->activate(this, this->sActivationOutput.data());

		//Save the network outputs w/ activation.
		for (std::size_t nOut{0}, nOutSize{this->fanOut()}; nOut < nOutSize; ++nOut)
			pOutput[nOut] = this->sActivationOutput[nOut];
	}

	void Layer::backward(float *pBackInput, float *pBackOutput) const
	{
		assert(this->pActivation);

		//Multiply the derivations of the activation function.
		std::vector<float> sBackInputBuffer(this->fanOut(), .0f);
		this->pActivation->derivative(this->fanOut(), this->sActivationInput.data(), this->sActivationOutput.data(), pBackInput, sBackInputBuffer.data());

		for (std::size_t nOut{0}, nOutSize{this->fanOut()}; nOut < nOutSize; ++nOut)
			pBackInput[nOut] = sBackInputBuffer[nOut];

		if (!pBackOutput)
			return;

		for (std::size_t nIn{0}, nInSize{this->fanIn()}; nIn < nInSize; ++nIn)
			pBackOutput[nIn] = .0f;

		//Backprop the sum of the differentials.
		for (std::size_t nOut{0}, nOutSize{this->fanOut()}; nOut < nOutSize; ++nOut)
			for (std::size_t nIn{0}, nInSize{this->fanIn()}; nIn < nInSize; ++nIn)
				pBackOutput[nIn] += this->sWeight[nOut][nIn] * pBackInput[nOut];	//SUM (W * derivation * derivation_before)
	}

	void Layer::serialize(std::ofstream &sOutput) const
	{
		for (auto &sWeight : this->sWeight)
			for (auto nWeight : sWeight)
				IO::Serializable::write(sOutput, nWeight);

		for (auto nBias : this->sBias)
			IO::Serializable::write(sOutput, nBias);
	}

	void Layer::deserialize(std::ifstream &sInput)
	{
		for (auto &sWeight : this->sWeight)
			for (auto &nWeight : sWeight)
				nWeight = IO::Serializable::read<float>(sInput);

		for (auto &nBias : this->sBias)
			nBias = IO::Serializable::read<float>(sInput);
	}
}