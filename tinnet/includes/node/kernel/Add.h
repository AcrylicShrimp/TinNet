
#include "tinnet/includes/memory/ScopedStorage.h"

#ifndef _TINNET_NODE_KERNEL_ADD_H

#	define _TINNET_NODE_KERNEL_ADD_H

#	include "tinnet/includes/node/Node.h"

namespace tinnet::node::kernel {
	memory::ScopedStorage __kernel__add(Node *pLeft, Node *pRight);
	void				  __kernel__addGradient(Node *pNode, Node *pDeps);
}	 // namespace tinnet::node::kernel

#endif