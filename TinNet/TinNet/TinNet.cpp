
/*
	2019.03.20
	Created by AcrylicShrimp.
*/

#include "TinNet.h"

namespace TinNet
{
	void registerStandardNodeType(Node::NodeTypeManager &sNodeTypeManager)
	{
		/*
			Front nodes.
		*/
		sNodeTypeManager.registerNode<Node::Input>();
		sNodeTypeManager.registerNode<Node::Parameter>();

		/*
			Basic arithmetic nodes.
		*/
		sNodeTypeManager.registerNode<Node::Add>();

		/*
			BLAS nodes.
		*/
		sNodeTypeManager.registerNode<Node::MM>();

		/*
			Math function nodes.
		*/
		sNodeTypeManager.registerNode<Node::Sigmoid>();

		/*
			Loss nodes.
		*/
		sNodeTypeManager.registerNode<Node::MSE>();
		sNodeTypeManager.registerNode<Node::SigmoidCrossEntropy>();
	}
}