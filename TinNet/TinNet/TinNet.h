
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _TINNET_H

#define _TINNET_H

/*
	TinNet::Core
*/
#include "Core/Memory.h"
#include "Core/Shape.h"
#include "Core/Span.h"

/*
	TinNet::Intializer
*/
#include "Initializer/InitializerBase.h"
#include "Initializer/Constant.h"
#include "Initializer/Xavier.h"

/*
	TinNet::Optimizer
*/
#include "Optimizer/SGD.h"

/*
	Basic node elements.
*/
#include "Node/Node.h"
#include "Node/NodeInput.h"

/*
	Front nodes.
*/
#include "Node/Input.h"
#include "Node/Parameter.h"

/*
	Basic arithmetic nodes.
*/
#include "Node/Add.h"

/*
	BLAS arithmetic nodes.
*/
#include "Node/MM.h"

/*
	Math function nodes.
*/
#include "Node/Sigmoid.h"

/*
	Loss nodes.
*/
#include "Node/SigmoidCrossEntropy.h"

#endif