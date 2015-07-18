#define EGL_USE_STL
#include "lib\egl.h"
struct Point3D
{
	GLfloat x, y, z;
	Point3D(GLfloat ax, GLfloat ay, GLfloat az) { x=ax; y=ay; z=az; }
};
typedef vector<Point3D> point_list;
typedef vector<Point3D>::iterator piter;
class eglSubWindow : public eglWindow
{
private:
	point_list mPointList;
	GLsizei    ClientWidth;   //윈도우의 너비
	GLsizei	   ClientHeight;  //윈도우의 높이
	GLfloat    Range; //클리핑 영역의 범위
public:
	virtual void RenderGLScene(void);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual void OnSize(WPARAM wParam, LPARAM lParam);
};
void eglSubWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	ClientWidth = ClientHeight = 0;
	Range = 5.0f; //클리핑 영역의 범의를 5 로 초기화한다.
}
void eglSubWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
	GLsizei width  = LOWORD(lParam);
	GLsizei height = HIWORD(lParam);
	ClientWidth = width;
	ClientHeight = height;

	if (height == 0)
		height = 1;                     

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

	GLfloat glX = ((xPos * (2*Range)) / ClientWidth)  - Range;
	GLfloat glY = ((yPos * (2*Range)) / ClientHeight) - Range;
	
	mPointList.push_back(Point3D(glX, -glY, 0.0f));
	TRACE("glVertex3f[ %f , %f , %f ]\n", glX, -glY, 0.0f);
}
void eglSubWindow::RenderGLScene(void)
{
	eglWindow::RenderGLScene();

	glTranslatef(0.0f, 0.0f, -10.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
		for(piter i=mPointList.begin(); i!=mPointList.end(); ++i)
		{
			glVertex3f((*i).x, (*i).y, (*i).z); 			
		}
	glEnd();
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	eglSubWindow app;
	app.Create(FALSE,"EDin's OpenGL : 점찍기");
	return app.Run();
}