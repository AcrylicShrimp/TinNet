
#ifndef _TINNET_NODE_KERNEL_BASICARITHMETIC_H

#define _TINNET_NODE_KERNEL_BASICARITHMETIC_H

#include "tinnet/includes/memory/ScopedStorage.h"
#include "tinnet/includes/node/Node.h"

namespace tinnet::node::kernel {
	memory::ScopedStorage __kernel__add(Node *pLeft, Node *pRight);
	memory::ScopedStorage __kernel__sub(Node *pLeft, Node *pRight);
	memory::ScopedStorage __kernel__mul(Node *pLeft, Node *pRight);
	memory::ScopedStorage __kernel__div(Node *pLeft, Node *pRight);
	void				  __kernel__addGradient(Node *pNode, Node *pDeps);
	void				  __kernel__subLGradient(Node *pNode, Node *pDeps);
	void				  __kernel__subRGradient(Node *pNode, Node *pDeps);
	void				  __kernel__mulLGradient(Node *pNode, Node *pDeps);
	void				  __kernel__mulRGradient(Node *pNode, Node *pDeps);
	void				  __kernel__divLGradient(Node *pNode, Node *pDeps);
	void				  __kernel__divRGradient(Node *pNode, Node *pDeps);
}	 // namespace tinnet::node::kernel

#endif