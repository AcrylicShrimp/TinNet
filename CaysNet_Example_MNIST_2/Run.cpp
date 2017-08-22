
/*
	2017.08.23
	Created by AcrylicShrimp.
*/

#include "../CaysNet/CaysNet/CaysNet.h"

#include <fstream>

#ifdef __cplusplus

extern "C" {

#endif

	CaysNet::NN sNetwork;

	__declspec(dllexport) void initNetwork();
	__declspec(dllexport) int classifyImage(float *pFloat);

	void initNetwork()
	{
		sNetwork.deserialize(std::ifstream{"network.cn", std::ifstream::binary | std::ifstream::in});
	}

	int classifyImage(float *pFloat)
	{
		return static_cast<int>(sNetwork.classify(pFloat));
	}

#ifdef __cplusplus

}

#endif