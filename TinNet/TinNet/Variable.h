
/*
	2018.09.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_VARIABLE_H

#define _CLASS_TINNET_VARIABLE_H

#include "TinNetDLL.h"

#include "Shape.h"

#include <cstddef>

namespace TinNet
{
	class TINNET_DLL Variable final
	{
	private:
		Shape sShape;
		float *pBase;
		std::size_t nSize;
		
	public:
		Variable(Shape sShape, float *pBase, std::size_t nSize);
		Variable(const Variable &sSrc) = default;
		Variable(Variable &&sSrc) = default;
		~Variable() = default;
		
	public:
		Variable &operator=(const Variable &sSrc) = default;
		Variable &operator=(Variable &&sSrc) = default;
		inline operator float *();
		inline operator const float *() const;
		
	public:
		inline const Shape &shape() const;
		inline float *begin();
		inline const float *begin() const;
		inline const float *cbegin() const;
		inline float *end();
		inline const float *end() const;
		inline const float *cend() const;
		inline std::size_t size() const;
	};

	inline Variable::operator float *()
	{
		return this->pBase;
	}

	inline Variable::operator const float *() const
	{
		return this->pBase;
	}

	inline const Shape &Variable::shape() const
	{
		return this->sShape;
	}

	inline float *Variable::begin()
	{
		return this->pBase;
	}

	inline const float *Variable::begin() const
	{
		return this->pBase;
	}

	inline const float *Variable::cbegin() const
	{
		return this->pBase;
	}

	inline float *Variable::end()
	{
		return this->pBase + this->nSize;
	}

	inline const float *Variable::end() const
	{
		return this->pBase + this->nSize;
	}

	inline const float *Variable::cend() const
	{
		return this->pBase + this->nSize;
	}

	inline std::size_t Variable::size() const
	{
		return this->nSize;
	}
}

#endif