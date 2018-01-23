
/*
	2018.01.24
	Created by AcrylicShrimp.
*/

#include "ConvLayer_GPU.h"

namespace TinNet::Layer
{
	ConvLayer_GPU::ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
								 std::size_t nNewFilterWidth,
								 std::size_t nNewFilterHeight) :
		ConvLayer_GPU(nNewWidth, nNewHeight, nNewChannel, nNewFilter,
				  nNewFilterWidth,
				  nNewFilterHeight,
				  1u,
				  1u)
	{
		//Empty.
	}

	ConvLayer_GPU::ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
								 std::size_t nNewFilterWidth,
								 std::size_t nNewFilterHeight,
								 std::size_t nNewStrideHorizontal,
								 std::size_t nNewStrideVertical) :
		ConvLayer_GPU(nNewWidth, nNewHeight, nNewChannel, nNewFilter,
				  nNewFilterWidth,
				  nNewFilterHeight,
				  nNewStrideHorizontal,
				  nNewStrideVertical,
				  nNewWidth,
				  nNewHeight)
	{
		//Empty.
	}

	ConvLayer_GPU::ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
								 std::size_t nNewFilterWidth,
								 std::size_t nNewFilterHeight,
								 std::size_t nNewStrideHorizontal,
								 std::size_t nNewStrideVertical,
								 std::size_t nNewOutputWidth,
								 std::size_t nNewOutputHeight) :
		Layer_GPU(nNewWidth * nNewHeight * nNewChannel, nNewOutputWidth * nNewOutputHeight * nNewFilter)
	{
		std::size_t vParam[14]
		{
			nNewWidth,
			nNewHeight,
			nNewChannel,
			nNewFilter,
			nNewFilterWidth,
			nNewFilterHeight,
			nNewStrideHorizontal,
			nNewStrideVertical,
			nNewOutputWidth,
			nNewOutputHeight
		};

		if ((vParam[10] = vParam[11] = ((nNewOutputWidth - 1u) * nNewStrideHorizontal + nNewFilterWidth - nNewWidth) / 2u) & 1u)
			++vParam[11];

		if ((vParam[12] = vParam[13] = ((nNewOutputHeight - 1u) * nNewStrideVertical + nNewFilterHeight - nNewHeight) / 2u) & 1u)
			++vParam[13];

		cuMemAlloc(&this->pBias, sizeof(float) * nNewFilter);
		cuMemAlloc(&this->pWeight, sizeof(float) * nNewFilter * nNewChannel * nNewFilterWidth * nNewFilterHeight);
		cuMemAlloc(&this->pParam, sizeof(vParam));

		cuMemcpyHtoD(this->pParam, vParam, sizeof(vParam));
	}
	
	ConvLayer_GPU::~ConvLayer_GPU()
	{
		cuMemFree(this->pBias);
		cuMemFree(this->pWeight);
		cuMemFree(this->pParam);

		this->pBias = 0;
		this->pWeight = 0;
		this->pParam = 0;
	}


}