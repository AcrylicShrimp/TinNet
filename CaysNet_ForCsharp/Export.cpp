
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#include "../CaysNet/CaysNet/CaysNet.h"

#include <fstream>

CaysNet::NN sNN;

#if __cplusplus

extern "C"
{

#endif

	__declspec(dllexport) void initNetwork()
	{
		sNN.deserialize(std::ifstream{"network.cn", std::ios::binary | std::ios::in});
	}

	__declspec(dllexport) int classifyImage(float *pFloat)
	{
		return static_cast<int>(sNN.classify(pFloat));
	}

#if __cplusplus

}

#endif