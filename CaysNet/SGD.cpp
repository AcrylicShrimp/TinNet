
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "SGD.h"

namespace CaysNet::Optimizer
{
	SGD::SGD()
	{
		//TODO : Place your implementation of default constructor here.
		
	}
	
	SGD::SGD(const SGD &sSrc)
	{
		//TODO : Place your implementation of copy constructor here.
		
	}
	
	SGD::SGD(SGD &&sSrc)
	{
		//TODO : Place your implementation of move constructor here.
		
	}
	
	SGD::~SGD()
	{
		//TODO : Place your implementation of destructor here.
		
	}
	
	/*
		TODO : Place your other constructors here.
	*/
	
	
	SGD &SGD::operator=(const SGD &sSrc)
	{
		if(&sSrc == this)
			return *this;
		
		//TODO : Place your implementation of copy assignment operator here.
		
		
		return *this;
	}
	
	SGD &SGD::operator=(SGD &&sSrc)
	{
		if(&sSrc == this)
			return *this;
		
		//TODO : Place your implementation of move assignment operator here.
		
		
		return *this;
	}
	
	/*
		TODO : Place your other operator overloadings here.
	*/
	
	
	/*
		TODO : Place your member function definitions here.
	*/

}