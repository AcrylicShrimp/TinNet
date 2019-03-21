
/*
	2019.03.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_NODETYPE_H

#define _CLASS_TINNET_NODE_NODETYPE_H

#include "../TinNetDLL.h"

#include <string>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL NodeType final
	{
	public:
		const NodeType *const pBaseType;
		const std::string sTypeName;

	public:
		NodeType(const NodeType *pBaseType, std::string_view sTypeName);
		NodeType(const NodeType &sSrc) = delete;
		~NodeType() noexcept = default;

	public:
		NodeType &operator=(const NodeType &sSrc) = delete;
		bool operator==(const NodeType &sRight) const;

	public:
		bool isBaseOf(const NodeType *pDerivedType) const;
		bool isDerivedFrom(const NodeType *pBaseType) const;
		bool isExactlyBaseOf(const NodeType *pDerivedType) const;
		bool isExactlyDerivedFrom(const NodeType *pBaseType) const;

	private:
		static bool isBaseOf(const NodeType *pBaseType, const NodeType *pDerivedType);
		static bool isExactlyBaseOf(const NodeType *pBaseType, const NodeType *pDerivedType);
	};
}

#endif