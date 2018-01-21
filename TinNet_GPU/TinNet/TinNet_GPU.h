
/*
	2018.01.19
	Created by AcrylicShrimp.
*/

#ifndef _TINNET_GPU_H

#define _TINNET_GPU_H

#include "../../TinNet/TinNet/TinNetDLL.h"

#include "Layer/Layers_GPU.h"

#include "Loss/Losses_GPU.h"
#include "Optimizer/Optimizers_GPU.h"

namespace TinNet
{
	TINNET_DLL void initTinNetGPU();
	TINNET_DLL void finTinNetGPU();
}

#endif