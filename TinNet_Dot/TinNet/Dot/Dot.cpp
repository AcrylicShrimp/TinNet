
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
	std::size_t Dot::nViewportIndex{100};
	std::size_t Dot::nViewportWidth{100};
	float Dot::nViewportSpacing{.8f};
	bool Dot::bScrollLock{true};

	Dot::Dot() :
		WindowMessageHandler{WM_CLOSE, WM_ERASEBKGND, WM_PAINT, WM_SIZING, WM_SIZE, WM_MOUSEWHEEL, WM_KEYDOWN, WM_SYSKEYDOWN, WM_SYSKEYUP, WM_SYSCHAR}
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
		case WM_MOUSEWHEEL:
		{
			auto nDelta{GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA};

			if (GetAsyncKeyState(VK_MENU) & 0x8000)
			{
				if (nDelta > 0)
					for (auto nIndex{0}, nCount{std::abs(nDelta)}; nIndex < nCount; ++nIndex)
					{
						if (Dot::nViewportWidth <= 25)
							break;

						Dot::nViewportWidth /= 2;
					}
				else
					for (auto nIndex{0}, nCount{std::abs(nDelta)}; nIndex < nCount; ++nIndex)
					{
						if (Dot::nViewportWidth >= 10000)
							break;

						Dot::nViewportWidth *= 2;
					}

				if (Dot::nViewportWidth <= 25)
					Dot::nViewportSpacing = .8f;
				else if (Dot::nViewportWidth <= 50)
					Dot::nViewportSpacing = .85f;
				else if (Dot::nViewportWidth <= 100)
					Dot::nViewportSpacing = .875f;
				else
					Dot::nViewportSpacing = .9f;
			}
			else
			{
				Dot::bScrollLock = false;

				auto nIndexDelta{-nDelta * static_cast<std::int64_t>(Dot::nViewportWidth / 25)};

				if (nIndexDelta < 0 && Dot::nViewportIndex < -nIndexDelta)
					Dot::nViewportIndex = 0;
				else
					Dot::nViewportIndex += nIndexDelta;
			}

			Dot::repaintWindow();
		}
		return 0;
		case WM_KEYDOWN:
		{
			if (wParam == VK_SPACE)
			{
				Dot::bScrollLock = true;
				Dot::repaintWindow();
			}
			else if (wParam == VK_DELETE)
			{
				Dot::display().clear();
				Dot::repaintWindow();
			}
		}
		return 0;
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_SYSCHAR:
		return 0;
		default:
		return 0;
		}
	}

	void Dot::render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto sResult{Dot::sDisplay.obtainData(Dot::nViewportWidth, Dot::bScrollLock ? Dot::sDisplay.length() : Dot::nViewportIndex)};
		auto pData{std::get<4>(sResult)};

		if (Dot::nViewportIndex > std::get<1>(sResult))
			Dot::bScrollLock = true;

		if (Dot::bScrollLock)
			Dot::nViewportIndex = std::get<1>(sResult);

		auto nXStep{std::powf(10.f, std::floorf(std::log10f(Dot::nViewportWidth)))};

		while (Dot::nViewportWidth / nXStep < 10.f)
			nXStep *= .5f;

		auto nMinX{std::floorf(Dot::nViewportIndex / nXStep) * nXStep};
		auto nMaxX{std::ceilf((Dot::nViewportIndex + Dot::nViewportWidth) / nXStep) * nXStep};

		glLineWidth(0.5f);
		glColor3f(.5f, .5f, .5f);
		glBegin(GL_LINES);
		{
			for (auto nX{nMinX}; nX <= nMaxX; nX += nXStep)
			{
				glVertex2f(2.f * (nX - Dot::nViewportIndex) / Dot::nViewportWidth - 1.f, 1.f);
				glVertex2f(2.f * (nX - Dot::nViewportIndex) / Dot::nViewportWidth - 1.f, -1.f);
			}
		}
		glEnd();

		auto nMin{std::get<2>(sResult) * .95f + Dot::sDisplay.min() * .05f};
		auto nMax{std::get<3>(sResult) * .95f + Dot::sDisplay.max() * .05f};

		if (nMin == nMax)
		{
			nMin -= 100.f;
			nMax += 100.f;
		}

		auto nDisplayHeight{nMax - nMin};
		auto nYStep{std::powf(10.f, std::floorf(std::log10f(nDisplayHeight)))};
		auto nMinY{std::floorf(nMin / nYStep) * nYStep};
		auto nMaxY{std::ceilf(nMax / nYStep) * nYStep};

		while ((nMaxY - nMinY) / nYStep <= 7.f)
		{
			nYStep *= .5f;
			nMinY = std::floorf(nMin / nYStep) * nYStep;
			nMaxY = std::ceilf(nMax / nYStep) * nYStep;
		}

		auto nYOverStep{nYStep * 5.f};
		auto nOverMinY{std::floorf(nMin / nYOverStep) * nYOverStep};
		auto nOverMaxY{std::ceilf(nMax / nYOverStep) * nYOverStep};

		glLineWidth(0.5f);
		glColor3f(.5f, .5f, .5f);
		glBegin(GL_LINES);
		{
			for (auto nY{nMinY}; nY <= nMaxY; nY += nYStep)
			{
				glVertex2f(-1.f, (2.f * (nY - nMin) / (nMax - nMin) - 1.f) * Dot::nViewportSpacing);
				glVertex2f(1.f, (2.f * (nY - nMin) / (nMax - nMin) - 1.f) * Dot::nViewportSpacing);
			}
		}
		glEnd();

		glLineWidth(2.f);
		glColor3f(1.f, 1.f, 1.f);
		glBegin(GL_LINES);
		{
			for (auto nY{nOverMinY}; nY <= nOverMaxY; nY += nYOverStep)
			{
				glVertex2f(-1.f, (2.f * (nY - nMin) / (nMax - nMin) - 1.f) * Dot::nViewportSpacing);
				glVertex2f(1.f, (2.f * (nY - nMin) / (nMax - nMin) - 1.f) * Dot::nViewportSpacing);
			}
		}
		glEnd();

		auto nStep{2.f / static_cast<float>(Dot::nViewportWidth - 1)};

		glLineWidth(3.f);
		glBegin(GL_LINE_STRIP);
		{
			constexpr float offset = -0x44;
			glColor3f((0xF5 + offset) / 255.f, (0xD9 + offset) / 255.f, (0x9D + offset) / 255.f);

			auto nX{-1.f};

			for (std::size_t nIndex{0}, nSize{std::get<0>(sResult)}; nIndex < nSize; ++nIndex, nX += nStep)
				glVertex2f(nX, (2.f * (pData[nIndex] - nMin) / (nMax - nMin) - 1.f) * Dot::nViewportSpacing);
		}
		glEnd();

		if (Dot::nViewportWidth < 100)
		{
			glBegin(GL_POINTS);
			{
				glColor3f(0xF5 / 255.f, 0xD9 / 255.f, 0x9D / 255.f);

				auto nX{-1.f};

				for (std::size_t nIndex{0}, nSize{std::get<0>(sResult)}; nIndex < nSize; ++nIndex, nX += nStep)
					glVertex2f(nX, (2.f * (pData[nIndex] - nMin) / (nMax - nMin) - 1.f) * Dot::nViewportSpacing);
			}
			glEnd();
		}

		SwapBuffers(Dot::sWindow.windowInfo().hDeviceContext);
	}

	void Dot::setupOpenGL()
	{
		glClearColor(0x42 / 255.f, 0x38 / 255.f, 0x33 / 255.f, .0f);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glPointSize(9.f);

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