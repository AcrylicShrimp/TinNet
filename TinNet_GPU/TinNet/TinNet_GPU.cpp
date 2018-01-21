
/*
	2018.01.19
	Created by AcrylicShrimp.
*/

#include "TinNet_GPU.h"

#include "cuda_runtime.h"

namespace TinNet
{
	void initTinNetGPU()
	{
		::cudaSetDevice(0);
		::cudaFree(0);
	}

	void finTinNetGPU()
	{
		::cudaDeviceReset();
	}
}