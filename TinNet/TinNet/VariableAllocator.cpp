
/*
	2018.09.02
	Created by AcrylicShrimp.
*/

#include "VariableAllocator.h"

namespace TinNet
{
	Variable VariableAllocator::allocate(const std::string &sName, Shape sShape)
	{
		auto iIndex{this->sVariableMap.find(sName)};

		if (iIndex == this->sVariableMap.cend())
		{
			auto &sVector = std::get<2>(this->sVariableMap.emplace(sName, std::make_tuple(1, sShape, std::vector<float>(sShape.element()))).first->second);

			return
			{
				sShape,
				sVector.data(),
				sVector.size()
			};
		}

		if (std::get<1>(iIndex->second) != sShape)
			throw std::invalid_argument("shape mismatch");

		++std::get<0>(iIndex->second);

		return
		{
			sShape,
			std::get<2>(iIndex->second).data(),
			std::get<2>(iIndex->second).size()
		};
	}

	void VariableAllocator::deallocate(const std::string &sName)
	{
		auto iIndex{this->sVariableMap.find(sName)};

		if (iIndex == this->sVariableMap.cend())
			return;

		if (!--std::get<0>(iIndex->second))
			this->sVariableMap.erase(iIndex);
	}
}