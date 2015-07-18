/***************************************************************************
 { 
 { Class for Opengl Windowed Application
 {
 {
 { 03.?? / 2003 
 { Sungchul Kim 
 { paranwave@korea.com
 {
 { 수정
 { 04.08 : egl namespace 추가
 {
***************************************************************************/
#ifndef _EGL_WINDOW_H_
#define _EGL_WINDOW_H_

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#include "eglMsgMacro.h"

namespace egl {

class Window
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
	Window();
	~Window();
	virtual BOOL InitGL(void);
	virtual void RenderGLScene(void);
	HWND GetHWND(void);
	HDC  GetHDC(void);
	
	BOOL Create(BOOL bFullScreen=FALSE, const char *title="EDin OpenGL Framework", int width=640, int height=480, int bits=16, LPTSTR menu=NULL);
	int Run(void);
	
	DECLARE_MESSAGE_MAP(Window);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam){}
	virtual void OnSize(WPARAM wParam, LPARAM lParam);
	virtual void OnClose(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnSysCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
	virtual void OnCommand(WPARAM wParam, LPARAM lParam) {}
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam){}
	virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam){}
	virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam){}
	virtual void OnMouseMove(WPARAM wParam, LPARAM lParam){}
	virtual void OnRButtonDown(WPARAM wParam, LPARAM lParam){}
	virtual void OnRButtonUp(WPARAM wParam, LPARAM lParam){}
	virtual void OnChar(WPARAM wParam, LPARAM lParam){}

};

}; //end of namespace
#endif