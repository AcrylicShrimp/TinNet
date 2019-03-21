
/*
	2019.03.18
	Created by AcrylicShrimp.
*/

#include "NodeType.h"

namespace TinNet::Node
{
	NodeType::NodeType(const NodeType *pBaseType, std::string_view sTypeName) :
		pBaseType{pBaseType},
		sTypeName{sTypeName}
	{
		//Empty.
	}

	bool NodeType::operator==(const NodeType &sRight) const
	{
		return this->sTypeName == sRight.sTypeName;
	}

	bool NodeType::isBaseOf(const NodeType *pDerivedType) const
	{
		return NodeType::isBaseOf(this, pDerivedType);
	}

	bool NodeType::isDerivedFrom(const NodeType *pBaseType) const
	{
		return NodeType::isBaseOf(pBaseType, this);
	}

	bool NodeType::isExactlyBaseOf(const NodeType *pDerivedType) const
	{
		return NodeType::isExactlyBaseOf(this, pDerivedType);
	}

	bool NodeType::isExactlyDerivedFrom(const NodeType *pBaseType) const
	{
		return NodeType::isExactlyBaseOf(pBaseType, this);
	}

	bool NodeType::isBaseOf(const NodeType *pBaseType, const NodeType *pDerivedType)
	{
		if (!pBaseType)
			return false;

		for (const auto *pBase{pDerivedType}; pBase; ++pBase)
			if (*pBase == *pBaseType)
				return true;

		return false;
	}

	bool NodeType::isExactlyBaseOf(const NodeType *pBaseType, const NodeType *pDerivedType)
	{
		if (!pBaseType)
			return false;

		if (!pDerivedType)
			return false;

		for (const auto *pBase{pDerivedType->pBaseType}; pBase; ++pBase)
			if (*pBase == *pBaseType)
				return true;

		return false;
	}
}