#include "lib\egl.h"
class eglSubWindow : public eglWindow
{
private:
	GLushort pattern;
	POINT	 oldPoint;
	GLfloat  xrot, yrot;
public:
	virtual void RenderGLScene(void);
	virtual void OnSize(WPARAM wParam, LPARAM lParam);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual void OnMouseMove(WPARAM wParam, LPARAM lParam);
};
void eglSubWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	pattern = 0xAAAA;
	xrot = yrot = 0.0f;
}
void eglSubWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
	GLsizei width = LOWORD(lParam);
    GLsizei height = HIWORD(lParam);
    if (height == 0)
        height = 1; 
    glViewport( 0, 0, width, height ); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    glOrtho(-5, 5, -5, 5, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
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
		yrot = LOWORD(lParam) - oldPoint.y/3.6;
		xrot = HIWORD(lParam) - oldPoint.x/3.6;
	}
}
void eglSubWindow::RenderGLScene(void)
{
	eglWindow::RenderGLScene();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glLineStipple(4, pattern);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-4.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 0.0f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 4.0f, 0.0f, 0.0f);
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 4.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f,-4.0f, 0.0f);
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -4.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 4.0f);
	glEnd();
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	eglSubWindow app;
	app.Create(FALSE, "EDin's OpenGL glLineStipple");
	return app.Run();
}