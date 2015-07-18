#include <windows.h>
#define  EGL_USE_STL
#include "lib\egl.h"

struct Point3D
{
public:
	GLfloat x, y, z;
	Point3D() { x = y = z = 0.0f; }
	Point3D(GLfloat ax, GLfloat ay, GLfloat az) { x=ax; y=ay; z=az; }
};

struct Line
{
	Point3D startPoint;
	Point3D endPoint;
	Line(Point3D aStartPoint, Point3D aEndPoint) { startPoint=aStartPoint; endPoint=aEndPoint; }
};

typedef vector<Line> line_list;
typedef vector<Line>::iterator liter;

class eglSubWindow : public eglWindow
{
private:
	line_list mLineList;
	GLfloat	Range;
	GLsizei ClientWidth;
	GLsizei ClientHeight;
	GLfloat LineWidth;
public:
	virtual void RenderGLScene(void);
	virtual void OnSize(WPARAM wParam, LPARAM lParam);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual void OnRButtonUp(WPARAM wParam, LPARAM lParam);
};

void eglSubWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	ClientWidth = ClientHeight = 0.0f;
	Range = 5.0f;
	LineWidth = 1.0f;
}
void eglSubWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
	GLsizei width = LOWORD(lParam);
    GLsizei height = HIWORD(lParam);

    if (height == 0)
        height = 1; 

    ClientWidth = width;
    ClientHeight = height;

    glViewport( 0, 0, width, height ); 

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 

    glOrtho(-Range, Range, -Range, Range, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
}
void eglSubWindow::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	GLfloat xPos = (GLfloat)(LOWORD(lParam));
	GLfloat yPos = (GLfloat)(HIWORD(lParam));

	GLfloat glX = ((xPos * (2*Range)) / ClientWidth) - Range;
    GLfloat glY = ((yPos * (2*Range)) / ClientHeight) - Range;

	mLineList.push_back(Line(Point3D(glX, glY, 0.0f), Point3D(glX, glY, 0.0f)));
	SetCapture(GetHWND());
}
void eglSubWindow::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	GLfloat xPos = (GLfloat)(LOWORD(lParam));
	GLfloat yPos = (GLfloat)(HIWORD(lParam));

	GLfloat glX = ((xPos * (2*Range)) / ClientWidth) - Range;
    GLfloat glY = ((yPos * (2*Range)) / ClientHeight) - Range;

	if(!mLineList.empty())
	{
		mLineList[mLineList.size()-1].endPoint.x = glX;
		mLineList[mLineList.size()-1].endPoint.y = glY;
		mLineList[mLineList.size()-1].endPoint.z = 0.0f;
	}
	ReleaseCapture();
}
void eglSubWindow::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	LineWidth += 1.0f;
	if(LineWidth > 10.0f)
	{
		LineWidth = 10.0f;
	}
}
void eglSubWindow::RenderGLScene(void)
{
	eglWindow::RenderGLScene();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glLineWidth(LineWidth);
	glBegin(GL_LINES);
		for(liter i=mLineList.begin(); i!=mLineList.end(); ++i)
		{
			glVertex3f((*i).startPoint.x, -(*i).startPoint.y, (*i).startPoint.z);
			glVertex3f((*i).endPoint.x, -(*i).endPoint.y, (*i).endPoint.z);
		}
	glEnd();
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	eglSubWindow app;
	app.Create(FALSE, "EDin's OpenGL glLine");
	return app.Run();
}