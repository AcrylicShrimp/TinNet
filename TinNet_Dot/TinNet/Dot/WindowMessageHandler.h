
/*
	2018.03.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_DOT_WINDOWMESSAGEHANDLER_H

#define _CLASS_TINNET_DOT_WINDOWMESSAGEHANDLER_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include <initializer_list>
#include <vector>
#include <Windows.h>
#include <windowsx.h>

namespace TinNet::Dot
{
	class Window;

	class TINNET_DLL WindowMessageHandler
	{
	protected:
		std::vector<UINT> sMessageList;

	public:
		WindowMessageHandler(std::initializer_list<UINT> sNewMessageList);
		WindowMessageHandler(const WindowMessageHandler &sSrc);
		WindowMessageHandler(WindowMessageHandler &&sSrc) = delete;
		virtual ~WindowMessageHandler() = default;

	public:
		WindowMessageHandler &operator=(const WindowMessageHandler &sSrc);
		WindowMessageHandler &operator=(WindowMessageHandler &&sSrc) = delete;

	public:
		inline const std::vector<UINT> &messageList() const;

		virtual LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam) = 0;
	};

	inline const std::vector<UINT> &WindowMessageHandler::messageList() const
	{
		return this->sMessageList;
	}
}

#endif