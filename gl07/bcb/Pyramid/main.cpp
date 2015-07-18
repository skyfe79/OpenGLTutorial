#include <windows.h>
#include "lib\egl.h"

using namespace egl;

class RenderWindow : public Window
{
private:
	GLfloat rot;
public:
	virtual void RenderGLScene(void);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
};

void RenderWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	rot = 0.0f;
}

void RenderWindow::RenderGLScene(void)
{
	Window::RenderGLScene();

	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);

	glBegin( GL_TRIANGLES );
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f); // { Front }
		glVertex3f(-1.0f,-1.0f, 1.0f); // { Front }
		glVertex3f( 1.0f,-1.0f, 1.0f); // { Front }

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f); // { Right }
		glVertex3f( 1.0f,-1.0f, 1.0f); // { Right }
		glVertex3f( 1.0f,-1.0f,-1.0f); // { Right }

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f); // { Back }
		glVertex3f( 1.0f,-1.0f,-1.0f); // { Back }
		glVertex3f(-1.0f,-1.0f,-1.0f); // { Back }

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f); // { Left }
		glVertex3f(-1.0f,-1.0f,-1.0f); // { Left }
		glVertex3f(-1.0f,-1.0f, 1.0f); // { Left }
	glEnd();

	rot += 0.01f;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	RenderWindow app;
	app.Create(FALSE,"EDin's OpenGL - 3D Pyramid");
	return app.Run();
}