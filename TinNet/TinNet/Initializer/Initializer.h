
/*
	2018.09.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_INITIALIZER_H

#define _CLASS_TINNET_INITIALIZER_INITIALIZER_H

#include "../TinNetDLL.h"

#include "../Variable.h"

namespace TinNet::Initializer
{
	class TINNET_DLL Initializer
	{
	public:
		Initializer() = default;
		Initializer(const Initializer &sSrc) = default;
		virtual ~Initializer() = default;
		
	public:
		Initializer &operator=(const Initializer &sSrc) = default;
		
	public:
		virtual void initialize(Variable &sVariable) = 0;
	};
}

#endif