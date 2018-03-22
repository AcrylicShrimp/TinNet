
/*
	2018.03.23
	Created by AcrylicShrimp.
*/

#include "Dot.h"

#undef min;
#undef max;

namespace TinNet::Dot
{
	bool Dot::bCreated{false};
	Window Dot::sWindow;
	Display Dot::sDisplay;
	Dot Dot::sMessageHandler;
	std::thread Dot::sMessageLoopThread;

	Dot::Dot() :
		WindowMessageHandler{WM_CLOSE, WM_ERASEBKGND, WM_PAINT, WM_SIZING, WM_SIZE}
	{
		//Empty.
	}

	void Dot::createWindow()
	{
		if (Dot::bCreated)
			return;

		SetConsoleCtrlHandler(&Dot::handleConsoleEvent, TRUE);
		Dot::sWindow.registerHandler(&Dot::sMessageHandler);

		Dot::bCreated = true;
		Dot::sMessageLoopThread = std::thread(&Dot::messageLoop);
	}

	void Dot::destroyWindow()
	{
		Dot::sWindow.destroyWindow();

		if (Dot::sMessageLoopThread.joinable())
			Dot::sMessageLoopThread.join();
	}

	void Dot::repaintWindow()
	{
		RedrawWindow(Dot::sWindow.windowHandle(), nullptr, nullptr, RDW_INVALIDATE);
	}

	LRESULT Dot::handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (nMessage)
		{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
		return 0;
		case WM_ERASEBKGND:
		return TRUE;
		case WM_PAINT:
		{
			Dot::render();

			//Prevent the redraw;
			ValidateRect(hWindow, nullptr);
		}
		return 0;
		case WM_SIZING:
		{
			glViewport(0, 0, Dot::sWindow.windowInfo().nClientWidth, Dot::sWindow.windowInfo().nClientHeight);
		}
		return 0;
		case WM_SIZE:
		{
			glViewport(0, 0, Dot::sWindow.windowInfo().nClientWidth, Dot::sWindow.windowInfo().nClientHeight);
		}
		return 0;
		default:
		return 0;
		}
	}

	void Dot::render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto sResult{Dot::sDisplay.obtainData(250, Dot::sDisplay.length())};
		auto pData{std::get<1>(sResult)};

		glBegin(GL_LINE_STRIP);
		{
			constexpr float offset = -0x44;
			glColor3f((0xF5 + offset) / 255.f, (0xD9 + offset) / 255.f, (0x9D + offset) / 255.f);

			auto nX{-1.f};
			auto nStep{2.f / 249.f};
			auto nMin{Dot::sDisplay.min()};
			auto nMax{Dot::sDisplay.max()};

			if (nMin == nMax)
				for (std::size_t nIndex{0}, nSize{std::get<0>(sResult)}; nIndex < nSize; ++nIndex, nX += nStep)
					glVertex2f(nX, .0f);
			else
				for (std::size_t nIndex{0}, nSize{std::get<0>(sResult)}; nIndex < nSize; ++nIndex, nX += nStep)
					glVertex2f(nX, (2.f * (pData[nIndex] - nMin) / (nMax - nMin) - 1.f) * .9f);
		}
		glEnd();

		glBegin(GL_POINTS);
		{
			glColor3f(0xF5 / 255.f, 0xD9 / 255.f, 0x9D / 255.f);

			auto nX{-1.f};
			auto nStep{2.f / 249.f};
			auto nMin{Dot::sDisplay.min()};
			auto nMax{Dot::sDisplay.max()};

			if (nMin == nMax)
				for (std::size_t nIndex{0}, nSize{std::get<0>(sResult)}; nIndex < nSize; ++nIndex, nX += nStep)
					glVertex2f(nX, .0f);
			else
				for (std::size_t nIndex{0}, nSize{std::get<0>(sResult)}; nIndex < nSize; ++nIndex, nX += nStep)
					glVertex2f(nX, (2.f * (pData[nIndex] - nMin) / (nMax - nMin) - 1.f) * .9f);
		}
		glEnd();

		SwapBuffers(Dot::sWindow.windowInfo().hDeviceContext);
	}

	void Dot::setupOpenGL()
	{
		glClearColor(0x42 / 255.f, 0x38 / 255.f, 0x33 / 255.f, .0f);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glPointSize(9.f);
		glLineWidth(3.f);

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	}

	void Dot::messageLoop()
	{
		RECT sWorkArea;
		SystemParametersInfo(SPI_GETWORKAREA, 0u, &sWorkArea, 0u);

		Dot::sWindow.createWindow(
		{
			(sWorkArea.right - sWorkArea.left) / 4,
			(sWorkArea.bottom - sWorkArea.top) / 4,
			(sWorkArea.right - sWorkArea.left) / 2u,
			(sWorkArea.bottom - sWorkArea.top) / 2u,
			TinNet::Dot::SizingMode::ClientAreaOnly,
			nullptr,
			LoadIconW(nullptr, IDI_APPLICATION),
			LoadCursorW(nullptr, IDC_ARROW),
			nullptr,
			nullptr,
			nullptr,
			L"TinNet Dot",
			L"TinNet Dot",
			TinNet::Dot::combineEnum(TinNet::Dot::ClassStyle::OwnDeviceContext, TinNet::Dot::ClassStyle::HorizontalRedraw, TinNet::Dot::ClassStyle::VerticalRedraw),
			TinNet::Dot::WindowStyle::TitledWindow,
			combineEnum(TinNet::Dot::ExtendedWindowStyle::AppWindow, TinNet::Dot::ExtendedWindowStyle::WindowEdge),
			nullptr
		});

		Dot::sWindow.createOpenGLContext(
			32u,
			32u,
			TinNet::Dot::combineEnum(TinNet::Dot::PixelBufferProperties::DrawToWindow, TinNet::Dot::PixelBufferProperties::SupportOpenGL, TinNet::Dot::PixelBufferProperties::DoubleBuffer),
			TinNet::Dot::PixelBufferPixelType::RGBA);

		Dot::sWindow.linkCurrentThread();
		Dot::setupOpenGL();
		Dot::sWindow.setVisible(TinNet::Dot::WindowVisibility::ShowDefault);

		for (MSG sMsg; GetMessageW(&sMsg, nullptr, 0u, 0u);)
		{
			TranslateMessage(&sMsg);
			DispatchMessageW(&sMsg);
		}

		Dot::sWindow.setVisible(TinNet::Dot::WindowVisibility::Hide);
		Dot::sWindow.unlinkCurrentThread();

		Dot::sWindow.destroyWindow();

		Dot::bCreated = false;
	}

	BOOL WINAPI Dot::handleConsoleEvent(DWORD CEvent)
	{
		switch (CEvent)
		{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_SHUTDOWN_EVENT:
		{
			PostQuitMessage(0);

			if (Dot::sMessageLoopThread.joinable())
				Dot::sMessageLoopThread.join();
		}
		break;
		}

		return TRUE;
	}
}