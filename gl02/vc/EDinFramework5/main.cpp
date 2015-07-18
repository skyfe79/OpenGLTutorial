#include <windows.h>
#include "egl.h"

class eglSubWindow : public eglWindow
{
private:
	POINT	oldPoint;
	GLfloat xrot, yrot;
public:
	virtual void RenderGLScene(void);

	DECLARE_MESSAGE_MAP(eglSubWindow)

	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual void OnMouseMove(WPARAM wParam, LPARAM lParam);
	
};

BEGIN_MESSAGE_MAP(eglSubWindow)
	ON_MESSAGE(eglSubWindow, WM_SIZE, OnSize)
	ON_MESSAGE(eglSubWindow, WM_CLOSE, OnClose)
	ON_MESSAGE(eglSubWindow, WM_KEYDOWN, OnKeyDown)
	ON_MESSAGE(eglSubWindow, WM_CREATE, OnCreate)
	ON_MESSAGE(eglSubWindow, WM_LBUTTONDOWN, OnLButtonDown)
	ON_MESSAGE(eglSubWindow, WM_LBUTTONUP, OnLButtonUp)
	ON_MESSAGE(eglSubWindow, WM_MOUSEMOVE, OnMouseMove)
END_MESSAGE_MAP();

void eglSubWindow::RenderGLScene(void)
{
	eglWindow::RenderGLScene();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glutWireCube(1.0);
}
void eglSubWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	xrot = yrot = 0.0f;
	memset(&oldPoint, 0, sizeof(oldPoint));
}
void eglSubWindow::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	oldPoint.x = LOWORD(lParam);
	oldPoint.y = HIWORD(lParam);
	SetCapture(GetHWND());
}
void eglSubWindow::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	oldPoint.x = 0;
	oldPoint.y = 0;
	ReleaseCapture();
}
void eglSubWindow::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	if(GetCapture()==GetHWND())
	{
		xrot = LOWORD(lParam) - oldPoint.x/3.6;
		yrot = HIWORD(lParam) - oldPoint.y/3.6;
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	eglSubWindow app;
	app.Create(FALSE);
	return app.Run();
}