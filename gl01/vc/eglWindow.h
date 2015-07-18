#ifndef _EGL_WINDOW_H_
#define _EGL_WINDOW_H_

#include <windows.h>
#include <string>
#include "eglMsgMacro.h"

class eglWindow
{
protected:
	HWND				mHWnd;
	MSG					mMsg;
	HDC					mDC;
	HINSTANCE			mHInstance;
public:
	eglWindow();
	~eglWindow();
	BOOL Create(HINSTANCE hInstance, std::string WindowTitle="EDin OpenGL Framework", BOOL bFullScreen=FALSE);
	virtual int Run(void);
	
	DECLARE_MESSAGE_MAP(eglWindow);

	virtual void OnLButtonDown(WPARAM w, LPARAM l);
	virtual void OnDestroy(WPARAM w, LPARAM l);
};

class eglWindow2 : public eglWindow
{
	DECLARE_MESSAGE_MAP(eglWindow2);
public:
	virtual void OnLButtonDown(WPARAM w, LPARAM l);
};


#endif