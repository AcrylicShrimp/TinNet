
/*
	2018.03.23
	Created by AcrylicShrimp.
*/

#include "WindowMessageHandler.h"

namespace TinNet::Dot
{
	WindowMessageHandler::WindowMessageHandler(std::initializer_list<UINT> sNewMessageList) :
		sMessageList(sNewMessageList)
	{
		//Empty.
	}

	WindowMessageHandler::WindowMessageHandler(const WindowMessageHandler &sSrc) :
		sMessageList(sSrc.sMessageList)
	{
		//Empty.
	}

	WindowMessageHandler &WindowMessageHandler::operator=(const WindowMessageHandler &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sMessageList = sSrc.sMessageList;

		return *this;
	}
}