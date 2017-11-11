
/*
	2017.11.03
	Created by AcrylicShrimp.
*/

#include "ConvLayer.h"

namespace CaysNet::Layer
{
	ConvLayer::ConvLayer(
		Activation::Activation *pActivation,
		std::size_t nInputWidth, std::size_t nInputHeight, std::size_t nChannelCount,
		std::size_t nFilterWidth, std::size_t nFilterHeight,
		std::size_t nPaddingWidth, std::size_t nPaddingHeight,
		std::size_t nStrideWidth, std::size_t nStrideHeight) :
		Layer{
		pActivation,
		nInputWidth * nInputHeight,
		((nInputWidth + 2 * nPaddingWidth - nFilterWidth) / nStrideWidth + 1) * ((nInputHeight + 2 * nPaddingHeight - nFilterHeight) / nStrideHeight + 1)}
	{
		
	}

	ConvLayer::ConvLayer(const ConvLayer &sSrc) :
		Layer(sSrc)
	{
		//TODO : Place your implementation of copy constructor here.

	}

	ConvLayer::ConvLayer(ConvLayer &&sSrc) :
		Layer(std::move(sSrc))
	{
		//TODO : Place your implementation of move constructor here.

	}

	ConvLayer::~ConvLayer()
	{
		//TODO : Place your implementation of destructor here.

	}

	/*
		TODO : Place your other constructors here.
	*/


	ConvLayer &ConvLayer::operator=(const ConvLayer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		//TODO : Place your implementation of copy assignment operator here.


		return *this;
	}

	ConvLayer &ConvLayer::operator=(ConvLayer &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		//TODO : Place your implementation of move assignment operator here.


		return *this;
	}

	/*
		TODO : Place your other operator overloadings here.
	*/


	/*
		TODO : Place your member function definitions here.
	*/

}