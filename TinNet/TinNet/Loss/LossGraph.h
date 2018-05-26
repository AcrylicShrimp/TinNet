
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LOSS_LOSSGRAPH_H

#define _CLASS_TINNET_LOSS_LOSSGRAPH_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

namespace TinNet::Loss
{
	using LossNode = std::shared_ptr<class LossGraph>;

	class LossGraph
	{
	protected:
		LossGraph *pForward;
		
	public:
		LossGraph();
		LossGraph(const LossGraph &sSrc) = default;
		virtual ~LossGraph() = default;
		
	public:
		LossGraph &operator=(const LossGraph &sSrc) = default;
		
	public:
		virtual std::size_t fanOut() const = 0;
		virtual void forward(float *pResult) = 0;
		void backward(float *pResult);
		template<class T, class ...P> inline static LossNode make(P &&...sParam);

	protected:
		virtual void backwardPath(LossGraph *pBackward, float *pResult) = 0;
		void link(LossGraph *pBackward);
	};

	template<class T, class ...P> inline LossNode LossGraph::make(P &&...sParam)
	{
		return std::make_shared<T>(std::forward<P>(sParam)...);
	}
}

#endif