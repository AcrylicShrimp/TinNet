
/*
	2018.03.27
	Created by AcrylicShrimp.
*/

#include "GPUVector.h"

#if _DEBUG

#include <cstdio>

#endif

namespace TinNet
{
	GPUVector::GPUVector() :
		nSize{0},
		pDevicePointer{0}
	{
		//Empty.
	}

	GPUVector::GPUVector(std::size_t nSize) :
		nSize{nSize},
		pDevicePointer{0}
	{
		if (!this->nSize)
			return;

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::GPUVector(std::size_t) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif
	}

	GPUVector::GPUVector(std::size_t nSize, float nValue) :
		nSize{nSize},
		pDevicePointer{0}
	{
		if (!this->nSize)
			return;

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::GPUVector(std::size_t, float) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif

		cuMemsetD32(this->pDevicePointer, *reinterpret_cast<unsigned int *>(&nValue), this->nSize);
	}

	GPUVector::GPUVector(std::size_t nSize, const float *pSrc) :
		nSize{nSize},
		pDevicePointer{0}
	{
		if (!this->nSize)
			return;

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::GPUVector(std::size_t, const float *) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif

		cuMemcpyHtoD(this->pDevicePointer, pSrc, sizeof(float) * this->nSize);
	}

	GPUVector::GPUVector(const std::vector<float> &sSrc) :
		nSize{sSrc.size()},
		pDevicePointer{0}
	{
		if (!this->nSize)
			return;

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::GPUVector(const std::vector<float> &) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif

		cuMemcpyHtoD(this->pDevicePointer, sSrc.data(), sizeof(float) * this->nSize);
	}

	GPUVector::GPUVector(const GPUVector &sSrc) :
		nSize{sSrc.nSize},
		pDevicePointer{0}
	{
		if (!this->nSize)
			return;

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::GPUVector(const GPUVector &) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif

		cuMemcpyDtoD(this->pDevicePointer, sSrc.pDevicePointer, sizeof(float) * this->nSize);
	}

	GPUVector::GPUVector(GPUVector &&sSrc) :
		nSize{sSrc.nSize},
		pDevicePointer{sSrc.pDevicePointer}
	{
		sSrc.nSize = sSrc.pDevicePointer = 0;
	}

	GPUVector::~GPUVector()
	{
		if (this->pDevicePointer)
			cuMemFree(this->pDevicePointer);
	}

	GPUVector &GPUVector::operator=(const float *pSrc)
	{
		if (!this->nSize)
			return *this;

		cuMemcpyHtoD(this->pDevicePointer, pSrc, sizeof(float) * this->nSize);

		return *this;
	}

	GPUVector &GPUVector::operator=(const std::vector<float> &sSrc)
	{
		this->~GPUVector();

		if (!(this->nSize = sSrc.size()))
		{
			this->pDevicePointer = 0;
			return *this;
		}

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::operator=(const std::vector<float> &) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif

		cuMemcpyHtoD(this->pDevicePointer, sSrc.data(), sizeof(float) * this->nSize);

		return *this;
	}

	GPUVector &GPUVector::operator=(const GPUVector &sSrc)
	{
		if (&sSrc == this)
			return *this;

		if (this->nSize != sSrc.nSize)
		{
			this->~GPUVector();
			this->nSize = sSrc.size();
		}

		if (!this->nSize)
		{
			this->pDevicePointer = 0;
			return *this;
		}

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::operator=(const GPUVector &) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif

		cuMemcpyDtoD(this->pDevicePointer, sSrc.pDevicePointer, sizeof(float) * this->nSize);

		return *this;
	}

	GPUVector &GPUVector::operator=(GPUVector &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~GPUVector();
		this->nSize = sSrc.nSize;
		this->pDevicePointer = sSrc.pDevicePointer;

		sSrc.nSize = sSrc.pDevicePointer = 0;

		return *this;
	}

	void GPUVector::resize(std::size_t nSize)
	{
		if (this->nSize == nSize)
			return;

		this->~GPUVector();

		if (!(this->nSize = nSize))
		{
			this->pDevicePointer = 0;
			return;
		}

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::resize(std::size_t) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif
	}

	void GPUVector::resize(std::size_t nSize, float nValue)
	{
		if (this->nSize == nSize)
			return;

		this->~GPUVector();

		if (!(this->nSize = nSize))
		{
			this->pDevicePointer = 0;
			return;
		}

#if _DEBUG
		CUresult nError = cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);

		if (nError != CUresult::CUDA_SUCCESS)
			printf("GPUVector::resize(std::size_t, float) : %d\n", nError);
#else
		cuMemAlloc(&this->pDevicePointer, sizeof(float) * this->nSize);
#endif

		cuMemsetD32(this->pDevicePointer, *reinterpret_cast<unsigned int *>(&nValue), this->nSize);
	}

	float GPUVector::at(std::size_t nIndex) const
	{
		assert(nIndex < this->nSize);

		float nResult;

		cuMemcpyDtoH(&nResult, this->pDevicePointer + sizeof(float) * nIndex, sizeof(float));

		return nResult;
	}

	void GPUVector::insert(std::size_t nIndex, float nValue)
	{
		assert(nIndex < this->nSize);

		cuMemcpyHtoD(this->pDevicePointer + sizeof(float) * nIndex, &nValue, sizeof(float));
	}

	void GPUVector::insert(std::size_t nIndex, std::vector<float> &sValue)
	{
		assert(nIndex < this->nSize);

		cuMemcpyHtoD(this->pDevicePointer + sizeof(float) * nIndex, sValue.data(), sizeof(float) * std::min(sValue.size(), this->nSize - nIndex));
	}

	void GPUVector::zero()
	{
		if (!this->nSize)
			return;

		cuMemsetD32(this->pDevicePointer, 0, this->nSize);
	}

	std::vector<float> GPUVector::to() const
	{
		std::vector<float> sResult(this->nSize);

		if (this->nSize)
			cuMemcpyDtoH(sResult.data(), this->pDevicePointer, sizeof(float) * this->nSize);

		return sResult;
	}

	void GPUVector::to(float *pDest) const
	{
		if (!this->nSize)
			return;

		cuMemcpyDtoH(pDest, this->pDevicePointer, sizeof(float) * this->nSize);
	}

	void GPUVector::to(GPUVector &sDest) const
	{
		if (!sDest.nSize || !this->nSize)
			return;

		cuMemcpyDtoD(sDest.pDevicePointer, this->pDevicePointer, sizeof(float) * std::min(sDest.nSize, this->nSize));
	}

	void GPUVector::to(std::vector<float> &sDest) const
	{
		if (sDest.empty() || !this->nSize)
			return;

		cuMemcpyDtoH(sDest.data(), this->pDevicePointer, sizeof(float) * std::min(sDest.size(), this->nSize));
	}
}