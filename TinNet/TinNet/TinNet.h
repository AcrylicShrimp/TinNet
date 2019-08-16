
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _TINNET_H

#define _TINNET_H

#include "TinNetDLL.h"

/*
	TinNet::Core
*/
#include "Core/Graph.h"
#include "Core/GraphBuilder.h"
#include "Core/Memory.h"
#include "Core/Shape.h"
#include "Core/Span.h"

/*
	TinNet::Initializer
*/
#include "Initializer/Initializer.h"
#include "Initializer/Constant.h"
#include "Initializer/Xavier.h"

/*
	TinNet::Optimizer
*/
#include "Optimizer/SGD.h"
#include "Optimizer/Momentum.h"

/*
	Basic node elements.
*/
#include "Node/Node.h"
#include "Node/NodeInput.h"
#include "Node/NodeType.h"
#include "Node/NodeTypeManager.h"

/*
	Front nodes.
*/
#include "Node/Input.h"
#include "Node/Parameter.h"

/*
	Basic arithmetic nodes.
*/
#include "Node/Add.h"
#include "Node/Subtract.h"
#include "Node/Multiply.h"
#include "Node/Negative.h"

/*
	Math function nodes.
*/
#include "Node/Log.h"
#include "Node/ReLU.h"
#include "Node/Sigmoid.h"
#include "Node/Softmax.h"

/*
	Reduce nodes.
*/
#include "Node/Sum.h"
#include "Node/Mean.h"

/*
	BLAS nodes.
*/
#include "Node/MM.h"

/*
	Layers.
*/
#include "Node/Dense.h"

/*
	Loss nodes.
*/
#include "Node/MSE.h"
#include "Node/SigmoidCrossEntropy.h"
#include "Node/SoftmaxCrossEntropy.h"

#endif