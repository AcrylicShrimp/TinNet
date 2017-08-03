
/*
	2017.08.03
	Created by AcrylicShrimp.
*/

#ifndef _CAYS_NET_NN_H

#define _CAYS_NET_NN_H

#include <cstdint>

namespace CaysNet
{
	class NN final
	{
	private:


	public:
		NN();
		NN(NN &&sSrc);
		NN(const NN &sSrc);
		~NN();

	public:
		NN &operator=(NN &sSrc);
		NN &operator=(const NN &sSrc);

	public:
		template<class Activation> NN &addLayer(uint32_t nNodeCount);
	};
}

#endif