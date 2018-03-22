
/*
	2018.03.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_DOT_DOT_H

#define _CLASS_TINNET_DOT_DOT_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "Display.h"
#include "Window.h"
#include "WindowMessageHandler.h"

#include <cstddef>
#include <thread>
#include <tuple>
#include <Windows.h>
#include <gl\GL.h>

namespace TinNet::Dot
{
	class TINNET_DLL Dot final : public WindowMessageHandler
	{
	private:
		static bool bCreated;
		static Window sWindow;
		static Display sDisplay;
		static Dot sMessageHandler;
		static std::thread sMessageLoopThread;

	private:
		Dot();
		Dot(const Dot &sSrc) = delete;
		Dot(Dot &&sSrc) = delete;
		~Dot() = default;
		
	public:
		Dot &operator=(const Dot &sSrc) = delete;
		Dot &operator=(Dot &&sSrc) = delete;
		
	public:
		inline static Display &display();
		static void createWindow();
		static void destroyWindow();
		static void repaintWindow();
		virtual LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam) override;

	private:
		static void render();
		static void setupOpenGL();
		static void messageLoop();
		static BOOL WINAPI handleConsoleEvent(DWORD CEvent);
	};

	inline Display &Dot::display()
	{
		return Dot::sDisplay;
	}
}

#endif