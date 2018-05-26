
/*
	2018.03.25
	Created by AcrylicShrimp.
*/

#include "OmocAgent.h"

namespace TinNet_Example
{
	OmocAgent::OmocAgent() :
		nIdentifier{0}
	{
		//Empty.
	}

	OmocAgent::OmocAgent(const OmocAgent &sSrc) :
		nIdentifier{sSrc.nIdentifier}
	{
		//Empty.
	}

	OmocAgent &OmocAgent::operator=(const OmocAgent &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nIdentifier = sSrc.nIdentifier;

		return *this;
	}
}