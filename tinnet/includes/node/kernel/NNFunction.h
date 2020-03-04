
#ifndef _TINNET_NODE_KERNEL_NNFUNCTION_H

#define _TINNET_NODE_KERNEL_NNFUNCTION_H

#include "tinnet/includes/memory/ScopedStorage.h"
#include "tinnet/includes/node/Node.h"

namespace tinnet::node::kernel {
	memory::ScopedStorage __kernel__relu(Node *pNode, float nA);
	void				  __kernel__reluGradient(Node *pNode, Node *pDeps, float nA);
}	 // namespace tinnet::node::kernel

#endif