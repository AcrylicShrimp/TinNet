
/*
	2018.03.23
	Created by AcrylicShrimp.
*/

#include "Window.h"

namespace TinNet::Dot
{
	std::unordered_map<HWND, Window *> Window::sWindowMap;
	std::unordered_map<UINT, std::vector<WindowMessageHandler *>> Window::sGlobalHandlerListMap;

	Window::~Window()
	{
		this->destroyWindow();
	}

	void Window::destroyWindow()
	{
		auto hWindowHandle{this->hWindow};

		DestroyWindow(this->hWindow);
		this->hWindow = nullptr;

		UnregisterClassW(this->sClassName.c_str(), this->hInstance);
		this->hInstance = nullptr;

		if (hWindowHandle)
			Window::sWindowMap.erase(hWindowHandle);
	}

	bool Window::createWindow(const WindowAttribute &sWindowAttribute)
	{
		WNDCLASSW sClass
		{
			static_cast<UINT>(sWindowAttribute.eClassStyle),
			Window::windowMessageProcedure,
			0,
			0,
			this->hInstance = GetModuleHandleW(nullptr),
			sWindowAttribute.hIcon,
			sWindowAttribute.hCursor,
			sWindowAttribute.hBackgroundBrush,
			sWindowAttribute.sMenuName,
			(this->sClassName = sWindowAttribute.sClassName).c_str()
		};

		if (!RegisterClassW(&sClass))
		{
			this->destroyWindow();

			return false;
		}

		RECT sClientRect
		{
			0l,
			0l,
			static_cast<LONG>(sWindowAttribute.nWidth),
			static_cast<LONG>(sWindowAttribute.nHeight)
		};

		if (sWindowAttribute.eSizingMode == SizingMode::ClientAreaOnly)
		{
			AdjustWindowRectEx(&sClientRect, static_cast<DWORD>(sWindowAttribute.eWindowStyle), sWindowAttribute.sMenuName != nullptr, static_cast<DWORD>(sWindowAttribute.eExtendedWindowStyle));

			sClientRect.right -= sClientRect.left;
			sClientRect.bottom -= sClientRect.top;
		}

		if (!(this->hWindow = CreateWindowExW(
			static_cast<DWORD>(sWindowAttribute.eExtendedWindowStyle),
			sWindowAttribute.sClassName.c_str(),
			sWindowAttribute.sTitleText.c_str(),
			static_cast<DWORD>(sWindowAttribute.eWindowStyle),
			sWindowAttribute.nX,
			sWindowAttribute.nY,
			sClientRect.right,
			sClientRect.bottom,
			sWindowAttribute.hParentWindow,
			sWindowAttribute.hMenu,
			this->hInstance,
			sWindowAttribute.pExtraPointer)))
		{
			this->destroyWindow();

			return false;
		}

		Window::sWindowMap.emplace(this->hWindow, this);

		return true;
	}

	bool Window::createOpenGLContext(BYTE nColorBit, BYTE nDepthBit, PixelBufferProperties eNewPixelBufferProperties, PixelBufferPixelType eNewPixelBufferPixelType)
	{
		if (!(this->sWindowInfo.hDeviceContext = GetDC(this->hWindow)))
		{
			this->sWindowInfo.hDeviceContext = nullptr;

			return false;
		}

		PIXELFORMATDESCRIPTOR sFormat
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			static_cast<DWORD>(eNewPixelBufferProperties),
			static_cast<BYTE>(eNewPixelBufferPixelType),
			nColorBit,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			nDepthBit,
			0,
			0,
			0,
			0,
			0, 0, 0
		};

		auto nPixelFormat{ChoosePixelFormat(this->sWindowInfo.hDeviceContext, &sFormat)};

		if (!nPixelFormat)
		{
			ReleaseDC(this->hWindow, this->sWindowInfo.hDeviceContext);
			this->sWindowInfo.hDeviceContext = nullptr;
			this->sWindowInfo.hRenderingContext = nullptr;

			return false;
		}

		if (!SetPixelFormat(this->sWindowInfo.hDeviceContext, nPixelFormat, &sFormat))
		{
			ReleaseDC(this->hWindow, this->sWindowInfo.hDeviceContext);
			this->sWindowInfo.hDeviceContext = nullptr;
			this->sWindowInfo.hRenderingContext = nullptr;

			return false;
		}

		if (!(this->sWindowInfo.hRenderingContext = wglCreateContext(this->sWindowInfo.hDeviceContext)))
		{
			ReleaseDC(this->hWindow, this->sWindowInfo.hDeviceContext);
			this->sWindowInfo.hDeviceContext = nullptr;
			this->sWindowInfo.hRenderingContext = nullptr;
		}

		return true;
	}

	void Window::destroyOpenGLContext()
	{
		wglDeleteContext(this->sWindowInfo.hRenderingContext);
		this->sWindowInfo.hRenderingContext = nullptr;

		ReleaseDC(this->hWindow, this->sWindowInfo.hDeviceContext);
		this->sWindowInfo.hDeviceContext = nullptr;
	}

	bool Window::linkCurrentThread() const
	{
		return wglMakeCurrent(this->sWindowInfo.hDeviceContext, this->sWindowInfo.hRenderingContext);
	}

	void Window::unlinkCurrentThread() const
	{
		wglMakeCurrent(nullptr, nullptr);
	}

	bool Window::setVisible(WindowVisibility eNewWindowVisibility)
	{
		return ShowWindow(this->hWindow, static_cast<int>(eNewWindowVisibility));
	}

	void Window::setFileDraggable(bool bNewDraggable)
	{
		DragAcceptFiles(this->hWindow, bNewDraggable);
	}

	bool Window::setTitle(const std::wstring &sNewTitle)
	{
		return SetWindowTextW(this->hWindow, sNewTitle.c_str());
	}

	bool Window::moveWindow(int nNewX, int nNewY, int nNewWidth, int nNewHeight, bool bRepaint)
	{
		return MoveWindow(this->hWindow, nNewX, nNewY, nNewWidth, nNewHeight, bRepaint);
	}

	void Window::registerHandler(WindowMessageHandler *pNewWindowMessageHandler)
	{
		for (auto nMessage : pNewWindowMessageHandler->messageList())
			this->sHandlerListMap[nMessage].emplace_back(pNewWindowMessageHandler);
	}

	void Window::unregisterHandler(WindowMessageHandler *pNewWindowMessageHandler)
	{
		for (auto nMessage : pNewWindowMessageHandler->messageList())
		{
			auto &sHandlerList{this->sHandlerListMap[nMessage]};

			for (auto iIndex{sHandlerList.cbegin()}, iEnd{sHandlerList.cend()}; iIndex != iEnd; ++iIndex)
				if (*iIndex == pNewWindowMessageHandler)
				{
					sHandlerList.erase(iIndex);
					break;
				}
		}
	}

	void Window::unregisterHandlerAll()
	{
		this->sHandlerListMap.clear();
	}

	LRESULT Window::handleMessage(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		LRESULT nResult;

		switch (nMessage)
		{
		case WM_MOVE:
		case WM_MOVING:
		case WM_SIZE:
		case WM_SIZING:
		{
			RECT sWindowRect;
			RECT sClientRect;

			GetWindowRect(hWindow, &sWindowRect);
			GetClientRect(hWindow, &sClientRect);

			this->sWindowInfo.nEntireX = sWindowRect.left;
			this->sWindowInfo.nEntireY = sWindowRect.top;
			this->sWindowInfo.nEntireWidth = sWindowRect.right - sWindowRect.left;
			this->sWindowInfo.nEntireHeight = sWindowRect.bottom - sWindowRect.top;

			this->sWindowInfo.nClientWidth = sClientRect.right - sClientRect.left;
			this->sWindowInfo.nClientHeight = sClientRect.bottom - sClientRect.top;

			nResult = 0;
		}
		break;
		default:
		{
			nResult = NoHandler;
		}
		break;
		}

		auto iIndex{this->sHandlerListMap.find(nMessage)};

		if (iIndex != this->sHandlerListMap.cend())
		{
			nResult = 0;

			for (auto pHandler : iIndex->second)
				nResult += pHandler->handleWindowMessage(this, hWindow, nMessage, wParam, lParam);
		}

		return nResult;
	}

	Window *Window::findWindow(HWND hWindow)
	{
		auto iIndex{Window::sWindowMap.find(hWindow)};

		if (iIndex == Window::sWindowMap.cend())
			return nullptr;

		return iIndex->second;
	}

	void Window::registerGlobalHandler(WindowMessageHandler *pNewWindowMessageHandler)
	{
		for (auto nMessage : pNewWindowMessageHandler->messageList())
			Window::sGlobalHandlerListMap[nMessage].emplace_back(pNewWindowMessageHandler);
	}

	void Window::unregisterGlobalHandler(WindowMessageHandler *pNewWindowMessageHandler)
	{
		for (auto nMessage : pNewWindowMessageHandler->messageList())
		{
			auto &sHandlerList{Window::sGlobalHandlerListMap[nMessage]};

			for (auto iIndex{sHandlerList.cbegin()}, iEnd{sHandlerList.cend()}; iIndex != iEnd; ++iIndex)
				if (*iIndex == pNewWindowMessageHandler)
				{
					sHandlerList.erase(iIndex);
					break;
				}
		}
	}

	void Window::unregisterGlobalHandlerAll()
	{
		Window::sGlobalHandlerListMap.clear();
	}

	LRESULT CALLBACK Window::windowMessageProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		auto iWindowIndex{Window::sWindowMap.find(hWindow)};

		if (iWindowIndex == Window::sWindowMap.cend())
			return DefWindowProcW(hWindow, nMessage, wParam, lParam);

		//Pass the local handler first.
		auto nResult{iWindowIndex->second->handleMessage(hWindow, nMessage, wParam, lParam)};

		//Pass the global handler later.
		auto iHandlerIndex{Window::sGlobalHandlerListMap.find(nMessage)};

		if (iHandlerIndex != Window::sGlobalHandlerListMap.cend())
		{
			nResult = 0;

			for (auto pHandler : iHandlerIndex->second)
				nResult += pHandler->handleWindowMessage(iWindowIndex->second, hWindow, nMessage, wParam, lParam);
		}

		return nResult == Window::NoHandler ? DefWindowProcW(hWindow, nMessage, wParam, lParam) : nResult;
	}
}