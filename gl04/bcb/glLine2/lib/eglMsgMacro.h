#ifndef _EGL_MSGMACRO_SYSTEM_H_
#define _EGL_MSGMACRO_SYSTEM_H_

//*************************************************************************************************************//
// Message Macro System 
#include <string>
#define BEGIN_MESSAGE_MAP(CLASSNAME) \
BOOL CLASSNAME::RegisterWindow(HINSTANCE hInstance)\
{\
	WNDCLASSEX wnd;\
	wnd.cbSize        = sizeof(WNDCLASSEX);\
	wnd.cbWndExtra    = 4;\
	wnd.cbClsExtra    = 0;\
	wnd.hCursor       = LoadCursor(NULL, IDC_ARROW);\
	wnd.hIcon         = LoadIcon(NULL, IDI_WINLOGO);\
	wnd.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);\
	wnd.hInstance     = hInstance;\
	wnd.lpfnWndProc   = CLASSNAME::WndProc;\
	wnd.lpszClassName = "eglWindow";\
	wnd.hbrBackground = NULL;\
	wnd.lpszMenuName  = NULL;\
	wnd.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;\
	if(!::RegisterClassEx(&wnd))\
		return FALSE;\
	return TRUE;\
}\
LRESULT CALLBACK CLASSNAME::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)\
{\
	int i=0;\
	static CLASSNAME *ido = (CLASSNAME *)GetWindowLong(hWnd, GWL_USERDATA);\
	if(ido == NULL && iMessage != WM_CREATE)\
	{\
		return DefWindowProc(hWnd, iMessage, wParam, lParam);\
	}\
	if(iMessage == WM_CREATE)\
	{\
		ido = (CLASSNAME *)(((LPCREATESTRUCT)lParam)->lpCreateParams);\
	}\
	while(MessageMap[i].iMsg != 0)\
	{\
		if(iMessage == MessageMap[i].iMsg)\
		{\
			(ido->*(MessageMap[i].fp))(wParam, lParam);\
		}\
		++i;\
	}\
	return DefWindowProc(hWnd, iMessage, wParam, lParam);\
}\
CLASSNAME::MESSAGEMAP CLASSNAME::MessageMap[] = {
#define ON_MESSAGE(CLASSNAME, MESSAGE, HANDLER) {MESSAGE, CLASSNAME::HANDLER},
#define END_MESSAGE_MAP() {0, NULL} };

#define DECLARE_MESSAGE_MAP(CLASSNAME) \
	typedef void (CLASSNAME::*CLASSNAME##FuncPtr)(WPARAM, LPARAM);\
	typedef struct _MESSAGEMAP\
	{\
		UINT iMsg;\
		CLASSNAME##FuncPtr fp;\
	}MESSAGEMAP;\
	private:	static BOOL RegisterWindow(HINSTANCE hInstance);\
	private:	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);\
	private:	static MESSAGEMAP MessageMap[];\
	public: 

// Message Macro System
//****************************************************************************************************************//

#endif