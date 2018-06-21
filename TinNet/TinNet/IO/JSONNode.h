
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_IO_JSONNODE_H

#define _CLASS_TINNET_IO_JSONNODE_H

#include "../TinNetDLL.h"

namespace TinNet::IO
{
	class TINNET_DLL JSONNode
	{
	public:
		enum class Type
		{
			Null,
			Bool,
			Number,
			String,
			Object,
			Array
		};

	private:
		Type eType;
		
	public:
		JSONNode();
		JSONNode(const JSONNode &sSrc) = default;
		JSONNode(JSONNode &&sSrc) = default;
		virtual ~JSONNode() = default;
		
	public:
		JSONNode &operator=(const JSONNode &sSrc) = default;
		JSONNode &operator=(JSONNode &&sSrc) = default;
		
	public:
		
	};
}

#endif