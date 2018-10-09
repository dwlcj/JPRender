#include "Window.h"
#include "Application.h"

namespace EDX
{

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Window::Create(const String& strTitle,
		const uint iWidth,
		const uint iHeight)
	{
		mstrTitle = strTitle;
		mWidth = iWidth;
		mHeight = iHeight;

		if (!RegisterWindowClass())
			return false;

		DWORD winStyle = WS_OVERLAPPEDWINDOW;
		DWORD winStyleEX = WS_EX_CLIENTEDGE;

		RECT rect = { 0, 0, LONG(mWidth), LONG(mHeight) };
		AdjustWindowRectEx(&rect, winStyle, NULL, winStyleEX);

		mhWnd = ::CreateWindowEx(
			winStyleEX,
			Application::WinClassName,
			StringCast<WIDECHAR>(*mstrTitle).Get(),
			winStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			GetDesktopWindow(),
			NULL,
			Application::GetInstanceHandle(),
			NULL);

		if (!mhWnd)
			return false;

		return true;
	}

	void Window::Destroy()
	{
		::UnregisterClass(Application::WinClassName, Application::GetInstanceHandle());
	}

	bool Window::RegisterWindowClass()
	{
		WNDCLASSEX winClass;
		winClass.cbSize = sizeof(WNDCLASSEX);
		winClass.style = CS_OWNDC | CS_DBLCLKS;
		winClass.lpfnWndProc = WndProc;
		winClass.cbClsExtra = 0;
		winClass.cbWndExtra = 0;
		winClass.hInstance = Application::GetInstanceHandle();
		winClass.hIcon = LoadIcon(0, IDI_APPLICATION);
		winClass.hCursor = LoadCursor(0, IDC_ARROW);
		winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		winClass.lpszMenuName = 0;
		winClass.lpszClassName = Application::WinClassName;
		winClass.hIconSm = LoadIcon(0, IDI_APPLICATION);

		if (!::RegisterClassEx(&winClass))
			return false;

		return true;
	}

	bool Window::ProcessMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		auto InvokeMouseEvent = [&]
		{
			MouseEventArgs mouseArgs;
			mouseArgs.Action = MouseAction(msg);
			mMousePt = MAKEPOINTS(lParam);
			mouseArgs.x = mMousePt.x;
			mouseArgs.y = mMousePt.y;
			mouseArgs.motionX = mMousePt.x - mMousePrevPt.x;
			mouseArgs.motionY = mMousePt.y - mMousePrevPt.y;
			mouseArgs.lDown = mLBtnDown;
			mouseArgs.rDown = mRBtnDown;
			mMouseEvent.Invoke(Application::GetMainWindow(), mouseArgs);

			mMousePrevPt = mMousePt;
		};

		switch (msg)
		{
		case WM_ACTIVATE:
			if (!HIWORD(wParam))
				SetActive(true);
			else
				SetActive(false);
			return true;
		case WM_SIZE:
			mResizeEvent.Invoke(Application::GetMainWindow(), ResizeEventArgs(LOWORD(lParam), HIWORD(lParam)));
			return true;
		case WM_MOUSEMOVE:
			InvokeMouseEvent();
			return true;
		case WM_LBUTTONDOWN:
			mLBtnDown = true;
			InvokeMouseEvent();
			return true;
		case WM_LBUTTONUP:
			mLBtnDown = false;
			InvokeMouseEvent();
			return true;
		case WM_LBUTTONDBLCLK:
			InvokeMouseEvent();
			return true;
		case WM_RBUTTONDOWN:
			mRBtnDown = true;
			InvokeMouseEvent();
			return true;
		case WM_RBUTTONUP:
			mRBtnDown = false;
			InvokeMouseEvent();
			return true;
		case WM_RBUTTONDBLCLK:
			InvokeMouseEvent();
			return true;
		case WM_MBUTTONDOWN:
			InvokeMouseEvent();
			return true;
		case WM_MBUTTONUP:
			InvokeMouseEvent();
			return true;
		case WM_MBUTTONDBLCLK:
			InvokeMouseEvent();
			return true;
		case WM_MOUSEWHEEL:
			InvokeMouseEvent();
			return true;
		case WM_KEYDOWN:
		case WM_CHAR:
		{
			KeyboardEventArgs kbArgs;
			kbArgs.ctrlDown = GetKeyState(VK_CONTROL) & 0x80;
			kbArgs.key = wParam;
			mKeyboardEvent.Invoke(Application::GetMainWindow(), kbArgs);

			return true;
		}
		case WM_DESTROY:
			Destroy();
			PostQuitMessage(0);
			return true;
		}

		return false;
	}

	bool Window::OpenFileDialog(const char* initDir, const char* ext, const char* filter, char outPath[MAX_PATH]) const
	{
		OPENFILENAMEA ofn;
		ZeroMemory(&ofn, sizeof(ofn));

		char filePath[MAX_PATH];

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = GetHandle();
		ofn.lpstrFile = filePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(filePath);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = initDir;
		ofn.lpstrDefExt = ext;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		if (GetOpenFileNameA(&ofn) == 0)
			return false;

		strcpy_s(outPath, MAX_PATH, filePath);
		return true;
	}

	void Window::CopyToClipBoard(const char* str, int strLength) const
	{
		OpenClipboard(mhWnd);
		EmptyClipboard();
		HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strLength);
		if (!hg)
		{
			CloseClipboard();
			return;
		}
		Memory::Memcpy(GlobalLock(hg), str, strLength);
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT, hg);
		CloseClipboard();
		//GlobalFree(hg);
	}

	bool Window::PasteFromClipBoard(String& str) const
	{
		if (!IsClipboardFormatAvailable(CF_TEXT))
			return false;
		if (!OpenClipboard(mhWnd))
			return false;

		HGLOBAL hglb = GetClipboardData(CF_TEXT);
		if (hglb == NULL)
		{
			CloseClipboard();
			return false;
		}
		else
		{
			char* pStr = (char*)GlobalLock(hglb);
			if (pStr != nullptr)
			{
				str = pStr;
				GlobalUnlock(hglb);
			}
			else
			{
				CloseClipboard();
				return false;
			}
		}

		CloseClipboard();
		return true;
	}

	bool GLWindow::Create(const String& strTitle,
		const uint iWidth,
		const uint iHeight)
	{
		if (!Window::Create(strTitle, iWidth, iHeight))
			return false;

		PIXELFORMATDESCRIPTOR pf =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			24,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			32,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
		mhDC = ::GetDC(GetHandle());
		int idx = ::ChoosePixelFormat(mhDC, &pf);
		::SetPixelFormat(mhDC, idx, &pf);

		mhRC = ::wglCreateContext(mhDC);
		::wglMakeCurrent(mhDC, mhRC);

		return true;
	}

	void GLWindow::Destroy()
	{
		::wglMakeCurrent(0, 0);
		::wglDeleteContext(mhRC);
		::ReleaseDC(mhWnd, mhDC);

		mhDC = 0;
		mhRC = 0;

		Window::Destroy();
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		bool bProcessed = false;
		Window* pWnd;
		if (pWnd = Application::GetMainWindow())
		{
			bProcessed = pWnd->ProcessMessage(hwnd, msg, wParam, lParam);
		}
		if (!bProcessed)
			return DefWindowProc(hwnd, msg, wParam, lParam);

		return 0;
	}
}