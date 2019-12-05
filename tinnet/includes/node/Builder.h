
#include "tinnet/includes/memory/ScopedStorage.h"
#include "tinnet/includes/node/Node.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/includes/node/StandardNode.h"
#include "tinnet/includes/node/Type.h"

#include <memory>

namespace tinnet::node {
	class Builder final {
	public:
		Builder()  = delete;
		~Builder() = delete;

	public:
		// TODO: Support multiple types.
		// static std::unique_ptr<Node> wrap(Type eType, Shape &&sShape, bool bGradientEnabled, std::uint8_t *pOutput);
		static std::unique_ptr<Node> wrap(Shape &&sShape, float *pSource, bool bGradientEnabled = false);
		static std::unique_ptr<StandardNode>
			variable(Shape &&sShape, memory::ScopedStorage &&sInitial, bool bGradientEnabled = true);
	};
}	 // namespace tinnet::node