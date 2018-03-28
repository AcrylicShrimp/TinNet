
/*
	2018.03.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GPUVECTOR_H

#define _CLASS_TINNET_GPUVECTOR_H

#include "../../TinNet/TinNet/TinNetDLL.h"

#include "cuda.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

namespace TinNet
{
	class TINNET_DLL GPUVector final
	{
	private:
		std::size_t nSize;
		CUdeviceptr pDevicePointer;
		
	public:
		GPUVector();
		GPUVector(std::size_t nSize);
		GPUVector(std::size_t nSize, float nValue);
		GPUVector(std::size_t nSize, const float *pSrc);
		GPUVector(const std::vector<float> &sSrc);
		GPUVector(const GPUVector &sSrc);
		GPUVector(GPUVector &&sSrc);
		~GPUVector();
		
	public:
		GPUVector &operator=(const float *pSrc);
		GPUVector &operator=(const std::vector<float> &sSrc);
		GPUVector &operator=(const GPUVector &sSrc);
		GPUVector &operator=(GPUVector &&sSrc);
		inline float operator[](std::size_t nIndex) const;
		
	public:
		inline std::size_t size() const;
		inline CUdeviceptr pointer() const;
		inline float *address();
		inline const float *address() const;
		inline float *address(std::size_t nIndex);
		inline const float *address(std::size_t nIndex) const;
		void resize(std::size_t nSize);
		void resize(std::size_t nSize, float nValue);
		float at(std::size_t nIndex) const;
		void insert(std::size_t nIndex, float nValue);
		void insert(std::size_t nIndex, std::vector<float> &sValue);
		void zero();
		std::vector<float> to() const;
		void to(float *pDest) const;
		void to(GPUVector &sDest) const;
		void to(std::vector<float> &sDest) const;
	};

	inline float GPUVector::operator[](std::size_t nIndex) const
	{
		return this->at(nIndex);
	}

	inline std::size_t GPUVector::size() const
	{
		return this->nSize;
	}

	inline CUdeviceptr GPUVector::pointer() const
	{
		return this->pDevicePointer;
	}

	inline float *GPUVector::address()
	{
		return reinterpret_cast<float *>(this->pDevicePointer);
	}

	inline const float *GPUVector::address() const
	{
		return reinterpret_cast<const float *>(this->pDevicePointer);
	}

	inline float *GPUVector::address(std::size_t nIndex)
	{
		return reinterpret_cast<float *>(this->pDevicePointer) + nIndex;
	}

	inline const float *GPUVector::address(std::size_t nIndex) const
	{
		return reinterpret_cast<const float *>(this->pDevicePointer) + nIndex;
	}
}

#endif