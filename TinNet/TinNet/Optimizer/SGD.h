
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_SGD_H

#define _CLASS_TINNET_OPTIMIZER_SGD_H

#include "../TinNetDLL.h"

#include "../Core/Memory.h"
#include "../Core/Span.h"

#include "../Node/Node.h"
#include "../Node/Parameter.h"

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL SGD
	{
	private:
		std::vector<Node::Parameter *> sParameterList;
		
	public:
		SGD(std::initializer_list<Node::Parameter *> sParameterList);
		SGD(const std::vector<Node::Parameter *> &sParameterList);
		SGD(const SGD &sSrc) = default;
		SGD(SGD &&sSrc) = default;
		~SGD() = default;
		
	public:
		SGD &operator=(const SGD &sSrc) = default;
		SGD &operator=(SGD &&sSrc) = default;
		
	public:
		void reduce(float nLearningRate, Node::Node *pTarget);
	};
}

#endif