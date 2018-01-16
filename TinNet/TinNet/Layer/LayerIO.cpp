
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#include "LayerIO.h"

namespace TinNet::Layer
{
	void LayerIO::serializeLayer(std::ofstream &sOutput, const std::unique_ptr<Layer> &pLayer)
	{
		IO::Serializable::write(sOutput, std::string{pLayer->name()});
		pLayer->serialize(sOutput);
	}

	std::unique_ptr<Layer> LayerIO::deserializeLayer(std::ifstream &sInput)
	{
		std::unique_ptr<Layer> pLayer;

		auto sName{IO::Serializable::readString(sInput)};

		if (sName == "BatchNormLayer")
			pLayer = std::make_unique<BatchNormLayer>(0u, .0f);
		else if (sName == "FullLayer")
			pLayer = std::make_unique<FullLayer>(0u, 0u);
		else if (sName == "SigmoidLayer")
			pLayer = std::make_unique<SigmoidLayer>(0u);
		else if (sName == "TanhLayer")
			pLayer = std::make_unique<TanhLayer>(0u);
		else if (sName == "SoftmaxLayer")
			pLayer = std::make_unique<SoftmaxLayer>(0u);
		else if (sName == "ReLULayer")
			pLayer = std::make_unique<ReLULayer>(0u);
		else if (sName == "LReLULayer")
			pLayer = std::make_unique<LReLULayer>(0u);
		else if (sName == "PReLULayer")
			pLayer = std::make_unique<PReLULayer>(0u, .0f);
		else
			return nullptr;

		pLayer->deserialize(sInput);

		return pLayer;
	}
}