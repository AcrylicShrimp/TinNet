
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_LAYERIO_H

#define _CLASS_TINNET_LAYER_LAYERIO_H

#include "../TinNetDLL.h"

#include "../IO/Serializable.h"
#include "Layers.h"

#include <fstream>
#include <memory>
#include <string>

namespace TinNet::Layer
{
	class TINNET_DLL LayerIO final
	{
	public:
		LayerIO() = delete;
		LayerIO(const LayerIO &sSrc) = delete;
		~LayerIO() = delete;
		
	public:
		LayerIO &operator=(const LayerIO &sSrc) = delete;
		
	public:
		static void serializeLayer(std::ofstream &sOutput, const std::unique_ptr<Layer> &pLayer);
		static std::unique_ptr<Layer> deserializeLayer(std::ifstream &sInput);
	};
}

#endif