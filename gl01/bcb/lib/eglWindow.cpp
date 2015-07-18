#include "eglWindow.h"

// { EDin OpenGL Framework 0.4 } 
// { email : paranwave@korea.com }

BEGIN_MESSAGE_MAP(eglWindow)
	ON_MESSAGE(eglWindow, WM_LBUTTONDOWN, OnLButtonDown)
	ON_MESSAGE(eglWindow, WM_DESTROY,   OnDestroy)
END_MESSAGE_MAP();

BEGIN_MESSAGE_MAP(eglWindow2)
	ON_MESSAGE(eglWindow2, WM_LBUTTONDOWN, OnLButtonDown)
	ON_MESSAGE(eglWindow2, WM_DESTROY,   OnDestroy)
END_MESSAGE_MAP();

void eglWindow2::OnLButtonDown(WPARAM w, LPARAM l)
{
	MessageBeep(-1);
}

void eglWindow::OnLButtonDown(WPARAM w, LPARAM l)
{
	MessageBox(this->mHWnd, TEXT("EDin's OpenGL Framework 입니다"), TEXT("Hello;)"), MB_OK);
}

void eglWindow::OnDestroy(WPARAM w, LPARAM l)
{
	PostQuitMessage(0);
}

eglWindow::eglWindow() : mDC(NULL), mHWnd(NULL), mHInstance(NULL)
{
}

eglWindow::~eglWindow()
{
}


BOOL eglWindow::Create(HINSTANCE hInstance, std::string WindowTitle, BOOL bFullScreen)
{
	if(!eglWindow::RegisterWindow(hInstance))
		return FALSE;

	mHInstance = hInstance;
	mHWnd = CreateWindowEx(
			0,
			"EdineglWindowClass",
			WindowTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			(HWND)NULL,
			(HMENU)NULL,
			hInstance,
			(LPVOID)this); //메세지맵을 위하여 this 포인터를 넘긴다.

	if(!mHWnd) 
	{
		return FALSE;
	}

	ShowWindow(mHWnd, SW_SHOW);
	UpdateWindow(mHWnd);
	return TRUE;
}

int eglWindow::Run(void)
{
	while(GetMessage(&mMsg, NULL, 0, 0))
	{
		TranslateMessage(&mMsg);
		DispatchMessage(&mMsg);
	}
	return mMsg.message;
}
