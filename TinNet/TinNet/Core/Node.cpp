
/*
	2018.10.21
	Created by AcrylicShrimp.
*/

#include "Node.h"

namespace TinNet::Core
{
	/*
		TODO : Place the static class member variable definitions here.
	*/
	
	
	Node::Node()
	{
		/*
			TODO : Place the default constructor here.
		*/
		
	}
	
	Node::Node(const Node &sSrc)
	{
		/*
			TODO : Place the implementation of the copy constructor here.
		*/
		
	}
	
	Node::Node(Node &&sSrc)
	{
		/*
			TODO : Place the implementation of the move constructor here.
		*/
		
	}
	
	Node::~Node()
	{
		/*
			TODO : Place the implementation of the destructor here.
		*/
		
	}
	
	/*
		TODO : Place the implementations of other constructors here.
	*/
	
	
	Node &Node::operator=(const Node &sSrc)
	{
		if (&sSrc == this)
			return *this;
		
		/*
			TODO : Place the implementation of the copy assignment operator here.
		*/
		
		
		return *this;
	}
	
	Node &Node::operator=(Node &&sSrc)
	{
		if (&sSrc == this)
			return *this;
		
		/*
			TODO : Place the implementation of the move assignment operator here.
		*/
		
		
		return *this;
	}
	
	/*
		TODO : Implement other operator overloadings here.
	*/
	
	
	/*
		TODO : Place the member function implementations here.
	*/
	
}