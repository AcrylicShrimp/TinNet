
#ifndef _TINNET_NODE_KERNEL_MATHFUNCTION_H

#define _TINNET_NODE_KERNEL_MATHFUNCTION_H

#include "tinnet/includes/memory/ScopedStorage.h"
#include "tinnet/includes/node/Node.h"

namespace tinnet::node::kernel {
	memory::ScopedStorage __kernel__log(Node *pNode);
	void				  __kernel__logGradient(Node *pNode, Node *pDeps);
}	 // namespace tinnet::node::kernel

#endif