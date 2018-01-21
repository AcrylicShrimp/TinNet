
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_SUPERVISED_SUPERVISEDOPTIMIZERBASE_GPU_H

#define _CLASS_TINNET_OPTIMIZER_SUPERVISED_SUPERVISEDOPTIMIZERBASE_GPU_H

#include "../../../../TinNet/TinNet/TinNetDLL.h"

#include "../../Layer/Layer_GPU.h"
#include "../../NN_GPU.h"
#include "../../TinNet_GPU_Backend.h"

#include "cuda.h"

#include <vector>

namespace TinNet::Optimizer::Supervised
{
	class TINNET_DLL SupervisedOptimizerBase_GPU
	{
	protected:
		NN_GPU &sNN;
		std::size_t nBatchSize;
		std::size_t nTrainingSize;
		std::vector<CUdeviceptr> sBiasDelta;
		std::vector<CUdeviceptr> sWeightDelta;
		std::vector<CUdeviceptr> sForwardOutput;
		std::vector<CUdeviceptr> sBackwardOutput;
		CUdeviceptr pBackwardInput;
		CUdeviceptr pTrainingInput;
		CUdeviceptr pTrainingOutput;
		
	public:
		SupervisedOptimizerBase_GPU(NN_GPU &sNN, std::size_t nNewBatchSize);
		SupervisedOptimizerBase_GPU(const SupervisedOptimizerBase_GPU &sSrc) = delete;
		virtual ~SupervisedOptimizerBase_GPU();
		
	public:
		SupervisedOptimizerBase_GPU &operator=(const SupervisedOptimizerBase_GPU &sSrc) = delete;

	public:
		void addTrainingSet(std::size_t nSetSize, const std::vector<float> *pInput, const std::vector<float> *pOutput);
		template<class LossFunc> void train(std::size_t nEpoch);
		
	public:
		virtual void applyGradient(std::size_t nActualBatchSize) = 0;
	};
}

#include "SupervisedOptimizerBase_GPU.hpp"

#endif