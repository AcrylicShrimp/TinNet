
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Optimizer.h"

namespace CaysNet::Optimizer
{
	Optimizer::Optimizer()
	{
		//TODO : Place your implementation of default constructor here.
		
	}
	
	Optimizer::Optimizer(const Optimizer &sSrc)
	{
		//TODO : Place your implementation of copy constructor here.
		
	}
	
	Optimizer::Optimizer(Optimizer &&sSrc)
	{
		//TODO : Place your implementation of move constructor here.
		
	}
	
	Optimizer::~Optimizer()
	{
		//TODO : Place your implementation of destructor here.
		
	}
	
	/*
		TODO : Place your other constructors here.
	*/
	
	
	Optimizer &Optimizer::operator=(const Optimizer &sSrc)
	{
		if(&sSrc == this)
			return *this;
		
		//TODO : Place your implementation of copy assignment operator here.
		
		
		return *this;
	}
	
	Optimizer &Optimizer::operator=(Optimizer &&sSrc)
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