
/*
	2019.03.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_NODEWRAPPER_H

#define _CLASS_TINNET_CORE_NODEWRAPPER_H

#include "../TinNetDLL.h"

#include "Shape.h"
#include "Span.h"

#include "../Node/Node.h"
#include "../Node/NodeInput.h"

#include <cassert>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace TinNet::Core
{
	class TINNET_DLL NodeWrapper final
	{
	public:
		Node::Node *const pNode;

	public:
		NodeWrapper(Node::Node *pNode);
		NodeWrapper(const NodeWrapper &sSrc) = default;
		~NodeWrapper() noexcept = default;

	public:
		NodeWrapper &operator=(const NodeWrapper &sSrc) = delete;
		inline Node::NodeInput *operator[](const std::string &sInputName);
		inline const Node::NodeInput *operator[](const std::string &sInputName) const;
		inline operator Node::Node *() noexcept;
		inline operator const Node::Node *() const noexcept;

	public:
		inline const Core::Shape &shape() const noexcept;
		inline Core::Span<float> output() const noexcept;
		inline Core::Span<float> gradient() const noexcept;
		inline bool hasDeps(NodeWrapper sDep) const;
		inline bool hasRevDeps(NodeWrapper sRevDep) const;
		inline NodeWrapper &markDirty(bool bDirtyShape = true);
		inline NodeWrapper &evalShape();
		inline NodeWrapper &evalOutput();
		inline NodeWrapper &evalGradient(NodeWrapper sDy);
	};

	inline Node::NodeInput *NodeWrapper::operator[](const std::string &sInputName)
	{
		return this->pNode->operator[](sInputName);
	}

	inline const Node::NodeInput *NodeWrapper::operator[](const std::string &sInputName) const
	{
		return this->pNode->operator[](sInputName);
	}

	inline NodeWrapper::operator Node::Node *() noexcept
	{
		return this->pNode;
	}

	inline NodeWrapper::operator const Node::Node *() const noexcept
	{
		return this->pNode;
	}

	inline const Core::Shape &NodeWrapper::shape() const noexcept
	{
		return this->pNode->shape();
	}

	inline Core::Span<float> NodeWrapper::output() const noexcept
	{
		return this->pNode->output();
	}

	inline Core::Span<float> NodeWrapper::gradient() const noexcept
	{
		return this->pNode->gradient();
	}

	inline bool NodeWrapper::hasDeps(NodeWrapper sDep) const
	{
		return this->pNode->hasDeps(sDep);
	}

	inline bool NodeWrapper::hasRevDeps(NodeWrapper sRevDep) const
	{
		return this->pNode->hasRevDeps(sRevDep);
	}

	inline NodeWrapper &NodeWrapper::markDirty(bool bDirtyShape)
	{
		this->pNode->markDirty(bDirtyShape);

		return *this;
	}

	inline NodeWrapper &NodeWrapper::evalShape()
	{
		this->pNode->evalShape();

		return *this;
	}

	inline NodeWrapper &NodeWrapper::evalOutput()
	{
		this->pNode->evalOutput();

		return *this;
	}

	inline NodeWrapper &NodeWrapper::evalGradient(NodeWrapper sDy)
	{
		this->pNode->evalGradient(sDy);

		return *this;
	}
}

#endif