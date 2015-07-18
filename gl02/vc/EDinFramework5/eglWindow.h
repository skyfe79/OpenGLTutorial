#ifndef _EGL_WINDOW_H_
#define _EGL_WINDOW_H_

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#include "eglMsgMacro.h"


class eglWindow
{
protected:
	BOOL				mFullscreen;
	HWND				mHWnd;
	MSG					mMsg;
	HDC					mDC;
	HGLRC				mRC;
	HINSTANCE			mHInstance;
	void				DestroyGLWindow(void);
public:
	eglWindow();
	~eglWindow();
	virtual BOOL InitGL(void);
	virtual void RenderGLScene(void);
	HWND GetHWND(void);
	HDC  GetHDC(void);
	
	BOOL Create(BOOL bFullScreen=FALSE, const char *title="EDin OpenGL Framework", int width=640, int height=480, int bits=16);
	int Run(void);
	
	DECLARE_MESSAGE_MAP(eglWindow);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam){}
	virtual void OnSize(WPARAM wParam, LPARAM lParam);
	virtual void OnClose(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnSysCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnCommand(WPARAM wParam, LPARAM lParam) {}
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam){}
	virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam){}
	virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam){}
	virtual void OnMouseMove(WPARAM wParam, LPARAM lParam){}
	virtual void OnRButtonDown(WPARAM wParam, LPARAM lParam){}
	virtual void OnRButtonUp(WPARAM wParam, LPARAM lParam){}
	virtual void OnChar(WPARAM wParam, LPARAM lParam){}
};
#endif