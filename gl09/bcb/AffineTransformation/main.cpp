#include <windows.h>
#include "lib\egl.h"

using namespace egl;

class RenderWindow : public Window
{
private:
public:
	virtual void RenderGLScene(void);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
};

void RenderWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
}

void RenderWindow::RenderGLScene(void)
{
	Window::RenderGLScene();

	static GLfloat rot=1.0f;
	static GLfloat scale=1.0f,factor=0.01f;
	glTranslatef(-2.0f, 0.0f, -10.0f);

	//5개의 삼각형 이용해서 별만들기
	glRotatef(rot,0.0f, 0.0f, 1.0f); //전체 회전
	for(int i=1; i<=5; i++)
	{
		glPushMatrix(); 
		glRotatef(72*(i-1), 0.0f, 0.0f, 1.0f); //5각형을 중심으로 삼각형 배치
		glTranslatef(0.0f, 1.35, 0.0f); //삼각형이 겹침을 막기 위해서 약간 이동
		glRotatef(i*rot, 1.0f, 0.0f, 0.0f); //각각회전
		glBegin(GL_TRIANGLES);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f( 1.0f, 0.0f, 0.0f);
			glVertex3f( 0.0f, 1.0f, 0.0f);
		glEnd();
		glPopMatrix();
	}
	//모델뷰행렬초기화
	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -10.0f);
	glScalef(scale, scale, scale); //크기변환
	glRotatef(rot, 0.0f, 1.0f, 0.0f); //Y축을 중심으로 회전
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f); //Z축을 중심으로 45도회전, 마름모
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.4f, -0.4f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 0.4f, -0.4f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 0.4f,  0.4f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-0.4f,  0.4f, 0.0f);
	glEnd();
	
	rot += 0.1f; //회전각도
	scale += factor; //크기 변환 배율

	if(scale >= 5.0f)
	{
		factor = -factor;
	}
	else if(scale <= 0.0f)
	{
		factor = -factor;
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	RenderWindow app;
	if(!app.Create(FALSE))
		return EXIT_FAILURE;
	return app.Run();
}