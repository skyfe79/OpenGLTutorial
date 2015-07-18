#include <windows.h>
#include "lib\egl.h"

struct Point3D
{
	GLfloat x, y, z;
};

class eglSubWindow : public eglWindow
{
private:
	GLfloat mPointSize;    //점의 크기
	Point3D mPointList[5]; //점의 리스트 
public:
	virtual void RenderGLScene(void);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
};

void eglSubWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	mPointList[0].x = 0.0f;
	mPointList[0].y = 0.0f;
	mPointList[0].z = -10.0f;

	mPointList[1].x = 1.0f;
	mPointList[1].y = 1.0f;
	mPointList[1].z = -10.0f;

	mPointList[2].x = 2.0f;
	mPointList[2].y = 2.0f;
	mPointList[2].z = -10.0f;

	mPointList[3].x = -1.0f;
	mPointList[3].y = -1.0f;
	mPointList[3].z = -10.0f;

	mPointList[4].x = -2.0f;
	mPointList[4].y = -2.0f;
	mPointList[4].z = -10.0f;

	mPointSize = 1.0f;
}
void eglSubWindow::RenderGLScene(void)
{
	static int i=0;
	static GLfloat step=0.1f;

	eglWindow::RenderGLScene();
	
	glColor3f(1.0f, 0.0f, 0.0f); //점의 색을 빨강색으로 설정한다.
	glPointSize(mPointSize);     //점의 크기를 설정한다.
	glBegin(GL_POINTS);
		for(i=0; i<sizeof(mPointList)/sizeof(Point3D); ++i)
		{
			glVertex3f(mPointList[i].x, mPointList[i].y, mPointList[i].z);
		}
	glEnd();

	mPointSize += step;

	if(mPointSize >= 10.0f)
	{
		step = -step;
	}
	else if(mPointSize <= 0.0f)
	{
		step = -step;
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	eglSubWindow app;
	app.Create(FALSE,"OpenGL glPoint");
	return app.Run();
}