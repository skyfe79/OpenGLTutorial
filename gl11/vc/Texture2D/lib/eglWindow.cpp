#include "eglWindow.h"

namespace egl {

// { email : paranwave@korea.com }
BEGIN_MESSAGE_MAP(Window)
	ON_MESSAGE(Window, WM_CREATE,    OnCreate)
	ON_MESSAGE(Window, WM_SIZE,		OnSize)
	ON_MESSAGE(Window, WM_CLOSE,		OnClose)
	ON_MESSAGE(Window, WM_KEYDOWN,	OnKeyDown)
	ON_MESSAGE(Window, WM_KEYUP,		OnKeyUp)
	ON_MESSAGE(Window, WM_MOUSEMOVE, OnMouseMove)
	ON_MESSAGE(Window, WM_LBUTTONDOWN, OnLButtonDown)
	ON_MESSAGE(Window, WM_LBUTTONUP,   OnLButtonUp)
	ON_MESSAGE(Window, WM_RBUTTONDOWN, OnRButtonDown)
	ON_MESSAGE(Window, WM_RBUTTONUP,   OnRButtonUp)
	ON_MESSAGE(Window, WM_CHAR,		  OnChar)
	ON_MESSAGE(Window, WM_COMMAND,	OnCommand)
	ON_MESSAGE(Window, WM_SYSCOMMAND,OnSysCommand)
	ON_MESSAGE(Window, WM_ERASEBKGND,OnEraseBkgnd)
END_MESSAGE_MAP();

void Window::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if(wParam == VK_ESCAPE)
	{
		SendMessage(mHWnd, WM_CLOSE, 0, 0);
	}
}
void Window::OnSize(WPARAM wParam, LPARAM lParam)
{
	GLsizei width  = LOWORD(lParam);
	GLsizei height = HIWORD(lParam);

	if (height == 0)
		height = 1;                     // Making Height Equal One

	glViewport( 0, 0, width, height ); // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);       // Select The Projection Matrix
	glLoadIdentity();                  // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, GLfloat(width)/GLfloat(height), 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity();           // Reset The Modelview Matrix
}
void Window::OnClose(WPARAM wParam, LPARAM lParam)
{
	DestroyGLWindow();
	PostQuitMessage(0);
}
void Window::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)				// Check System Calls
	{
		case SC_SCREENSAVE:		// Screensaver Trying To Start?
		case SC_MONITORPOWER:	// Monitor Trying To Enter Powersave?
		return ;				// Prevent From Happening
	}
}
void Window::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return ;
}



Window::Window(void) : mDC(NULL), mHWnd(NULL), mFullscreen(FALSE)
{
	 mHInstance = GetModuleHandle(NULL); //현재 프로그램의 인스턴스 핸들을 가져온다.
}

Window::~Window()
{
}

BOOL Window::InitGL(void)
{
	glShadeModel(GL_SMOOTH);                           // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);              // Black Background
    glClearDepth(1.0f);                                // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                           // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                            // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

	return TRUE;
}

void Window::RenderGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity();                                   // Reset The Current Modelview Matrix
}

void Window::DestroyGLWindow(void)
{
	if(mFullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}
	if(mRC)
	{
		if(!wglMakeCurrent(NULL, NULL))
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		mRC = NULL;
	}
	if( mDC && !ReleaseDC(mHWnd, mDC))
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		mDC = NULL; // Set DC To NULL
	}
	if(mHWnd && !DestroyWindow(mHWnd))
	{
		MessageBox(NULL, "Could Not Release mHWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		mHWnd = NULL; // Set hWnd To NULL
	}
	if (!UnregisterClass("eglWindow", mHInstance))
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		mHInstance = NULL; 
	}
}
HWND Window::GetHWND(void)
{
	return mHWnd;
}
HDC Window::GetHDC(void)
{
	return mDC;
}

BOOL Window::Create(BOOL fullscreen, const char *title, int width, int height, int bits,LPTSTR menu)
{
	if(!Window::RegisterWindow(mHInstance))
		return FALSE;

	GLuint   PixelFormat; // Holds The Results After Searching For A Match
	DWORD    dwExStyle;   // Window Extended Style
	DWORD    dwStyle;     // Window Style
	RECT     ClientRect;
	ClientRect.left   = (long)0;
	ClientRect.right  = (long)width;
	ClientRect.top    = (long)0;
	ClientRect.bottom = (long)height;
	
	mFullscreen = fullscreen;
	if(mFullscreen)
	{
		DEVMODE dm;						// Device Mode
		memset(&dm, 0, sizeof(dm));		// Makes Sure Memory's Cleared
		dm.dmSize = sizeof(dm);			// Size Of The Devmode Structure
		dm.dmPelsHeight = height;		// Selected Screen Height
		dm.dmPelsWidth  = width;		// Selected Screen Width
		dm.dmBitsPerPel = bits;			// Selected Bits Per Pixel
		dm.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if(ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if(MessageBox(NULL, TEXT("현재의 비디오카드에서 풀스크린을 지원하지 않습니다. 보통화면으로 보시겠습니까?"), TEXT("오류"),
				MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				mFullscreen = FALSE;
			}
			else
			{
				MessageBox(NULL, TEXT("프로그램을 종료합니다"), TEXT("알림"), MB_OK | MB_ICONSTOP);
				PostQuitMessage(0);
				return FALSE; //exit
			}
		}
	}

	if(mFullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle   = WS_POPUP;
		//ShowCursor(false);
	}
	else
	{
      dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
      dwStyle   = WS_OVERLAPPEDWINDOW;               
	}
	
	AdjustWindowRectEx(&ClientRect, dwStyle, false, dwExStyle); // Adjust Window To true Requested Size
	
	mHWnd = CreateWindowEx(
			dwExStyle,
			"eglWindow",
			title,
			dwStyle|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
			0, 0,
			ClientRect.right-ClientRect.left,
			ClientRect.bottom-ClientRect.top,
			(HWND)NULL,
			(HMENU)((!fullscreen) ? LoadMenu(mHInstance, menu) : NULL),
			mHInstance,
			(LPVOID)this); //메세지맵을 위하여 this 포인터를 넘긴다.

	if(!mHWnd) 
	{
		MessageBox(NULL, TEXT("윈도우를 생성하는데 실패했습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

    static PIXELFORMATDESCRIPTOR pfd = {
      sizeof(pfd), // Size Of This Pixel Format Descriptor
      1,                             // Version Number
      PFD_DRAW_TO_WINDOW |           // Format Must Support Window
      PFD_SUPPORT_OPENGL |           // Format Must Support OpenGL
      PFD_DOUBLEBUFFER,              // Must Support Double Buffering
      PFD_TYPE_RGBA,                 // Request An RGBA Format
      bits,                          // Select Our Color Depth
      0, 0, 0, 0, 0, 0,              // Color Bits Ignored
      0,                             // No Alpha Buffer
      0,                             // Shift Bit Ignored
      0,                             // No Accumulation Buffer
      0, 0, 0, 0,                    // Accumulation Bits Ignored
      16,                            // 16Bit Z-Buffer (Depth Buffer)
      0,                             // No Stencil Buffer
      0,                             // No Auxiliary Buffer
      PFD_MAIN_PLANE,                // Main Drawing Layer
      0,                             // Reserved
      0, 0, 0                        // Layer Masks Ignored
    };
	
	// Did We Get A Device Context?
	if(!(mDC = GetDC(mHWnd)))
	{ 
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL Device Context 를 생성할 수 없습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	 // Did Windows Find A Matching Pixel Format?
	if (!(PixelFormat = ChoosePixelFormat(mDC, &pfd)))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("장치에 맞는 픽셀형식을 찾지 못했습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Are We Able To Set The Pixel Format?
	if(!SetPixelFormat(mDC, PixelFormat, &pfd))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("픽셀형식을 설정할 수 없습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Are We Able To Get A Rendering Context?
	if (!(mRC=wglCreateContext(mDC)))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL Rendering Context 를 생성할 수 없습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return false
	}

	// Try To Activate The Rendering Context
	if(!wglMakeCurrent(mDC, mRC))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL Rendering Context 를 사용할 수 없습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return false
	}

	ShowWindow(mHWnd, SW_SHOW);    // Show The Window
	SetForegroundWindow(mHWnd);    // Slightly Higher Priority
	SetFocus(mHWnd);               // Sets Keyboard Focus To The Window
	
	OnSize(0, MAKELPARAM(width, height)); //이함수를 호출하지 않으면 FULLSCREEN 에서 그림이 그려지지 않는다.

	// Initialize Our Newly Created GL Window
	if (!InitGL())
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("초기화에 실패했습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

int Window::Run(void)
{
	while(1)
	{
		if(PeekMessage(&mMsg, NULL, 0, 0, PM_REMOVE))
		{
			if(mMsg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&mMsg);
				DispatchMessage(&mMsg);
			}
		}
		else
		{
			RenderGLScene();
			SwapBuffers(mDC);	
		}
	}
	return mMsg.message;
}

}; //end of namespace