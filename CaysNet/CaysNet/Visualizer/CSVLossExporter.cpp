
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "CSVLossExporter.h"

namespace CaysNet::Visualizer
{
	CSVLossExporter::CSVLossExporter(CSVLossExporter &&sSrc) :
		sLoss{std::move(sSrc.sLoss)}
	{
		//Empty.
	}

	void CSVLossExporter::exportCSV(std::ofstream &sOutput) const
	{
		for (auto nLoss : this->sLoss)
			sOutput << nLoss << std::endl;
	}
}