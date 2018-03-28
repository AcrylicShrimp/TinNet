
/*
	2018.03.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_OMOCAGENT_H

#define _CLASS_TINNET_EXAMPLE_OMOCAGENT_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace TinNet_Example
{
	class OmocAgent
	{
	private:

		
	public:
		OmocAgent();
		OmocAgent(const OmocAgent &sSrc);
		OmocAgent(OmocAgent &&sSrc);
		~OmocAgent();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		OmocAgent &operator=(const OmocAgent &sSrc);
		OmocAgent &operator=(OmocAgent &&sSrc);
		/*
			TODO : Place other operator overloadings here.
		*/
		
		
	public:
		/*
			TODO : Place the member function declarations here.
		*/
		
	};
}

#endif