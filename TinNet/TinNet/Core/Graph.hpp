
namespace TinNet::Core
{
	template<class T> std::size_t Graph::nodeCount() const
	{
		return this->nodeCount(this->sNodeTypeManager.type<T>());
	}

	template<class T> inline T *Graph::node(const std::string &sNodeName)
	{
		static_assert(std::is_base_of<Node::Node, T>());

		auto *pNode{this->node(sNodeName)};

		if (!pNode)
			return nullptr;

		const auto *pNodeType{this->sNodeTypeManager.type<T>()};

		if (!pNodeType || !pNodeType->isBaseOf(pNode->type()))
			return nullptr;

		return static_cast<T *>(pNode);
	}

	template<class T> inline const T *Graph::node(const std::string &sNodeName) const
	{
		static_assert(std::is_base_of<Node::Node, T>());

		const auto *pNode{this->node(sNodeName)};

		if (!pNode)
			return nullptr;

		const auto *pNodeType{this->sNodeTypeManager.type<T>()};

		if (!pNodeType || !pNodeType->isBaseOf(pNode->type()))
			return nullptr;

		return static_cast<const T *>(pNode);
	}

	template<class T> std::vector<T *> Graph::nodes()
	{
		static_assert(std::is_base_of<Node::Node, T>());

		return this->nodes(this->sNodeTypeManager.type<T>());
	}

	template<class T> std::vector<const T *> Graph::nodes() const
	{
		static_assert(std::is_base_of<Node::Node, T>());

		return this->nodes(this->sNodeTypeManager.type<T>());
	}

	template<class T, class ...P> T *Graph::createIntializer(P &&...tParam)
	{
		static_assert(std::is_base_of<Initializer::Initializer, T>());

		return static_cast<T *>(this->sInitializerSet.emplace(new T(std::forward<P>(tParam)...)).first->get());
	}

	template<class T, class ...P> inline T *Graph::createNode(const std::string &sNodeName, P &&...tParam)
	{
		static_assert(std::is_base_of<Node::Node, T>());
		
		const auto *pNodeType{this->sNodeTypeManager.type<T>()};
		
		if (!pNodeType)
			throw std::exception{"not registered or unknown node type."};
		
		auto *pNode{this->node(sNodeName)};
		
		if (!pNode)
			pNode = this->sNodeMap.emplace(std::piecewise_construct, std::forward_as_tuple(sNodeName), std::forward_as_tuple(new T(this, sNodeName, std::forward<P>(tParam)...))).first->second.get();
		
		for (const auto *pNodeType{this->sNodeTypeManager.type<T>()}; pNodeType; pNodeType = pNodeType->pBaseType)
			this->sNodeTypeMap.emplace(pNodeType, pNode);
		
		return static_cast<T *>(pNode);
	}
}