
/*
	2019.08.16
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_MOMENTUM_H

#define _CLASS_TINNET_OPTIMIZER_MOMENTUM_H

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
	class TINNET_DLL Momentum
	{
	public:
		const float nMomentum;

	private:
		std::vector<Node::Parameter *> sParameterList;
		std::vector<Core::Memory<float>> sMomentumGradientList;
		
	public:
		Momentum(float nMomentum, std::initializer_list<Node::Parameter *> sParameterList);
		Momentum(float nMomentum, const std::vector<Node::Parameter *> &sParameterList);
		Momentum(const Momentum &sSrc) = default;
		Momentum(Momentum &&sSrc) = default;
		~Momentum() noexcept = default;
		
	public:
		Momentum &operator=(const Momentum &sSrc) = default;
		Momentum &operator=(Momentum &&sSrc) noexcept = default;
		
	public:
		void reduce(float nLearningRate, Node::Node *pTarget);
	};
}

#endif