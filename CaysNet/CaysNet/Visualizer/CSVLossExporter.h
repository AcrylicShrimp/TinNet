
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_VISUALIZER_CSV_LOSS_EXPORTER_H

#define _CLASS_CAYSNET_VISUALIZER_CSV_LOSS_EXPORTER_H

#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace CaysNet::Visualizer
{
	class CSVLossExporter final
	{
	private:
		std::vector<float> sLoss;
		
	public:
		CSVLossExporter() = default;
		CSVLossExporter(const CSVLossExporter &sSrc) = delete;
		CSVLossExporter(CSVLossExporter &&sSrc);
		~CSVLossExporter() = default;
		
	public:
		CSVLossExporter &operator=(const CSVLossExporter &sSrc) = delete;
		CSVLossExporter &operator=(CSVLossExporter &&sSrc) = delete;
		
	public:
		inline void accrueLoss(float nLoss);
		void exportCSV(std::ofstream &sOutput) const;
	};

	inline void CSVLossExporter::accrueLoss(float nLoss)
	{
		return this->sLoss.emplace_back(nLoss);
	}
}

#endif