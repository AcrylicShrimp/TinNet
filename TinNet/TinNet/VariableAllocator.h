
/*
	2018.09.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_VARIABLEALLOCATOR_H

#define _CLASS_TINNET_VARIABLEALLOCATOR_H

#include "TinNetDLL.h"

#include "Shape.h"
#include "Variable.h"

#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

namespace TinNet
{
	class TINNET_DLL VariableAllocator final
	{
	private:
		std::unordered_map<std::string, std::tuple<std::size_t, Shape, std::vector<float>>> sVariableMap;
		
	public:
		VariableAllocator() = default;
		VariableAllocator(const VariableAllocator &sSrc) = delete;
		VariableAllocator(VariableAllocator &&sSrc) = default;
		~VariableAllocator() = default;
		
	public:
		VariableAllocator &operator=(const VariableAllocator &sSrc) = delete;
		VariableAllocator &operator=(VariableAllocator &&sSrc) = default;
		
	public:
		Variable allocate(const std::string &sName, Shape sShape);
		void deallocate(const std::string &sName);
	};
}

#endif