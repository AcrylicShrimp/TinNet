
/*
	2018.03.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_DOT_WINDOW_H

#define _CLASS_TINNET_DOT_WINDOW_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "WindowMessageHandler.h"

#include <unordered_map>
#include <cstdint>
#include <string>
#include <utility>
#include <Windows.h>

namespace TinNet::Dot
{
	enum class ClassStyle : UINT
	{
		ByteAlignClient = CS_BYTEALIGNCLIENT,
		ByteAlignWindow = CS_BYTEALIGNWINDOW,
		ClassDeviceContext = CS_CLASSDC,
		DoubleClick = CS_DBLCLKS,
		DropShadow = CS_DROPSHADOW,
		GlobalClass = CS_GLOBALCLASS,
		HorizontalRedraw = CS_HREDRAW,
		VerticalRedraw = CS_VREDRAW,
		NoClose = CS_NOCLOSE,
		OwnDeviceContext = CS_OWNDC,
		ParentDeviceContext = CS_PARENTDC,
		SaveBit = CS_SAVEBITS
	};

	enum class WindowStyle : DWORD
	{
		Border = WS_BORDER,
		Caption = WS_CAPTION,
		Child = WS_CHILD,
		ClipChild = WS_CLIPCHILDREN,
		ClipSibling = WS_CLIPSIBLINGS,
		Disabled = WS_DISABLED,
		DialogFrame = WS_DLGFRAME,
		Group = WS_GROUP,
		HorizontalScrollBar = WS_HSCROLL,
		VerticalScrollBar = WS_VSCROLL,
		Maximized = WS_MAXIMIZE,
		Minimized = WS_MINIMIZE,
		MaximizeBox = WS_MAXIMIZEBOX,
		MinimizeBox = WS_MINIMIZEBOX,
		Titled = WS_TILED,
		TitledWindow = WS_TILEDWINDOW,
		Popup = WS_POPUP,
		PopupWindow = WS_POPUPWINDOW,
		ResizingFrame = WS_SIZEBOX,
		SystemMenu = WS_SYSMENU,
		TabStop = WS_TABSTOP,
		Visible = WS_VISIBLE
	};

	enum class ExtendedWindowStyle : DWORD
	{
		AcceptFile = WS_EX_ACCEPTFILES,
		AppWindow = WS_EX_APPWINDOW,
		Topmost = WS_EX_TOPMOST,
		ClientEdge = WS_EX_CLIENTEDGE,
		Composited = WS_EX_COMPOSITED,
		HelpMenu = WS_EX_CONTEXTHELP,
		TakeParentFlow = WS_EX_CONTROLPARENT,
		DoubleBorder = WS_EX_DLGMODALFRAME,
		Layered = WS_EX_LAYERED,
		RTLLayout = WS_EX_LAYOUTRTL,
		LeftAligned = WS_EX_LEFT,
		RightAligned = WS_EX_RIGHT,
		LeftScrollBar = WS_EX_LEFTSCROLLBAR,
		RightScrollBar = WS_EX_RIGHTSCROLLBAR,
		LTRReading = WS_EX_LTRREADING,
		RTLReading = WS_EX_RTLREADING,
		MDIChiled = WS_EX_MDICHILD,
		NoActivate = WS_EX_NOACTIVATE,
		NoInheritLayout = WS_EX_NOINHERITLAYOUT,
		NoParentNotify = WS_EX_NOPARENTNOTIFY,
		NoBitmapBuffer = WS_EX_NOREDIRECTIONBITMAP,
		OverlappedWindow = WS_EX_OVERLAPPEDWINDOW,
		PaletteWindow = WS_EX_PALETTEWINDOW,
		StaticEdge = WS_EX_STATICEDGE,
		ToolWindow = WS_EX_TOOLWINDOW,
		Transparent = WS_EX_TRANSPARENT,
		WindowEdge = WS_EX_WINDOWEDGE
	};

	enum class SizingMode : bool
	{
		ClientAreaOnly = true,
		EntireArea = false
	};

	struct WindowAttribute
	{
	public:
		int32_t nX;
		int32_t nY;
		uint32_t nWidth;
		uint32_t nHeight;
		SizingMode eSizingMode;
		HMENU hMenu;
		HICON hIcon;
		HCURSOR hCursor;
		HBRUSH hBackgroundBrush;
		HWND hParentWindow;
		LPCWSTR sMenuName;
		std::wstring sClassName;
		std::wstring sTitleText;
		ClassStyle eClassStyle;
		WindowStyle eWindowStyle;
		ExtendedWindowStyle eExtendedWindowStyle;
		LPVOID pExtraPointer;
	};

	enum class PixelBufferProperties : DWORD
	{
		DrawToBitmap = PFD_DRAW_TO_BITMAP,
		DrawToWindow = PFD_DRAW_TO_WINDOW,
		SupportGDI = PFD_SUPPORT_GDI,
		SupportOpenGL = PFD_SUPPORT_OPENGL,
		GenericFormat = PFD_GENERIC_FORMAT,
		GenericAccelerated = PFD_GENERIC_ACCELERATED,
		NeedPalette = PFD_NEED_PALETTE,
		NeedSystemPalette = PFD_NEED_SYSTEM_PALETTE,
		DoubleBuffer = PFD_DOUBLEBUFFER,
		Stereoscopic = PFD_STEREO,
		SwapLayerBuffer = PFD_SWAP_LAYER_BUFFERS,
		DepthNotCare = PFD_DEPTH_DONTCARE,
		DoubleBufferNotCare = PFD_DOUBLEBUFFER_DONTCARE,
		StereoscopicNotCare = PFD_STEREO_DONTCARE,
		CopySwap = PFD_SWAP_COPY,
		ExchangeSwap = PFD_SWAP_EXCHANGE
	};

	enum class PixelBufferPixelType : BYTE
	{
		RGBA = PFD_TYPE_RGBA,
		ColorIndex = PFD_TYPE_COLORINDEX
	};

	enum class WindowVisibility : int
	{
		ForceMinimize = SW_FORCEMINIMIZE,
		Hide = SW_HIDE,
		Maximize = SW_MAXIMIZE,
		Minimize = SW_MINIMIZE,
		Restore = SW_RESTORE,
		Show = SW_SHOW,
		ShowDefault = SW_SHOWDEFAULT,
		ShowMaximized = SW_SHOWMAXIMIZED,
		ShowMinimized = SW_SHOWMINIMIZED,
		ShowMinimizedNoActive = SW_SHOWMINNOACTIVE,
		ShowNoActive = SW_SHOWNA,
		ShowNormal = SW_SHOWNORMAL,
		ShowNormalNoActive = SW_SHOWNOACTIVATE
	};

	struct WindowInfo
	{
		HDC hDeviceContext;
		HGLRC hRenderingContext;
		int32_t nEntireX;
		int32_t nEntireY;
		uint32_t nEntireWidth;
		uint32_t nEntireHeight;
		uint32_t nClientWidth;
		uint32_t nClientHeight;
	};

	class TINNET_DLL Window final
	{
	public:
		static const auto NoHandler{static_cast<LRESULT>(-1)};

	private:
		static std::unordered_map<HWND, Window *> sWindowMap;
		static std::unordered_map<UINT, std::vector<WindowMessageHandler *>> sGlobalHandlerListMap;

		std::unordered_map<UINT, std::vector<WindowMessageHandler *>> sHandlerListMap;
		WindowInfo sWindowInfo;
		HWND hWindow{nullptr};
		HINSTANCE hInstance{nullptr};
		std::wstring sClassName;
		
	public:
		Window() = default;
		Window(const Window &sSrc) = delete;
		Window(Window &&sSrc) = delete;
		~Window();

	public:
		Window &operator=(const Window &sSrc) = delete;
		Window &operator=(Window &&sSrc) = delete;
		
	public:
		inline WindowInfo &windowInfo();
		inline const WindowInfo &windowInfo() const;
		inline HWND windowHandle() const;
		inline HINSTANCE instanceHandle() const;
		inline bool isCreated() const;

		void destroyWindow();
		bool createWindow(const WindowAttribute &sWindowAttribute);
		bool createOpenGLContext(BYTE nColorBit, BYTE nDepthBit, PixelBufferProperties eNewPixelBufferProperties, PixelBufferPixelType eNewPixelBufferPixelType);
		void destroyOpenGLContext();
		bool linkCurrentThread() const;
		void unlinkCurrentThread() const;
		bool setVisible(WindowVisibility eNewWindowVisibility);
		void setFileDraggable(bool bNewDraggable);
		bool setTitle(const std::wstring &sNewTitle);
		bool moveWindow(int nNewX, int nNewY, int nNewWidth, int nNewHeight, bool bRepaint = true);
		void registerHandler(WindowMessageHandler *pNewWindowMessageHandler);
		void unregisterHandler(WindowMessageHandler *pNewWindowMessageHandler);
		void unregisterHandlerAll();
		LRESULT handleMessage(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);

		static Window *findWindow(HWND hWindow);
		static void registerGlobalHandler(WindowMessageHandler *pNewWindowMessageHandler);
		static void unregisterGlobalHandler(WindowMessageHandler *pNewWindowMessageHandler);
		static void unregisterGlobalHandlerAll();
		static LRESULT CALLBACK windowMessageProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
	};

	inline WindowInfo &Window::windowInfo()
	{
		return this->sWindowInfo;
	}

	inline const WindowInfo &Window::windowInfo() const
	{
		return this->sWindowInfo;
	}

	inline HWND Window::windowHandle() const
	{
		return this->hWindow;
	}

	inline HINSTANCE Window::instanceHandle() const
	{
		return this->hInstance;
	}

	inline bool Window::isCreated() const
	{
		return this->hWindow;
	}

	template<class EnumType> inline constexpr EnumType combineEnum(EnumType tFirst)
	{
		return tFirst;
	}

	template<class EnumType, class ...OtherEnumType> inline constexpr EnumType combineEnum(EnumType tFirst, OtherEnumType ...tSecond)
	{
		return static_cast<EnumType>(static_cast<std::underlying_type_t<EnumType>>(tFirst) | static_cast<std::underlying_type_t<EnumType>>(combineEnum(static_cast<EnumType>(tSecond)...)));
	}
}

#endif