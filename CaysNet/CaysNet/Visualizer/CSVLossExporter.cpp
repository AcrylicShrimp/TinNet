
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
		for (std::size_t nIndex{0}, nSize{this->sLoss.size()}; nIndex < nSize; ++nIndex)
		{
			std::time_t sTime = std::chrono::system_clock::to_time_t(this->sTimepoint[nIndex]);
			std::tm sLocalTime;

			localtime_s(&sLocalTime, &sTime);
			
			auto nDuration{this->sTimepoint[nIndex] - std::chrono::time_point_cast<std::chrono::seconds>(this->sTimepoint[nIndex])};
			sOutput << this->sLoss[nIndex] << ",\"" << sLocalTime.tm_year + 1900 << "." << sLocalTime.tm_mon + 1 << "." << sLocalTime.tm_mday << "-" << sLocalTime.tm_hour << ":" << sLocalTime.tm_min << ":" << sLocalTime.tm_sec << ":" << std::chrono::duration_cast<std::chrono::milliseconds>(nDuration).count() << "\"" << std::endl;
		}
	}
}