#include "lib\egl.h"

using namespace egl;

class RenderWindow : public Window
{
private:
	GLfloat ambientLight[4];
	GLfloat diffuseLight[4];
	GLfloat lightPosition[4];
	GLfloat specular[4];
	GLfloat specref[4]; //전반사 반사율
	GLfloat xrot,yrot;
public:
	virtual BOOL InitGL(void);
	virtual void RenderGLScene(void);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
};

void RenderWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	ambientLight[0] = 0.3f;
	ambientLight[1] = 0.3f;
	ambientLight[2] = 0.3f;
	ambientLight[3] = 1.0f;

	diffuseLight[0] = 0.7f;
	diffuseLight[1] = 0.7f;
	diffuseLight[2] = 0.7f;
	diffuseLight[3] = 1.0f;

	lightPosition[0] = 0.0f;
	lightPosition[1] = 0.0f;
	lightPosition[2] = 5.0f;
	lightPosition[3] = 1.0f;

	specular[0] = 1.0f;
	specular[1] = 1.0f;
	specular[2] = 1.0f;
	specular[3] = 1.0f;
	
	specref[0] = 0.0f;
	specref[1] = 0.5f;
	specref[2] = 0.0f;
	specref[3] = 1.0f;

	xrot = yrot = 0.1f;
}
BOOL RenderWindow::InitGL(void)
{
	Window::InitGL();

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	return TRUE;
}
void RenderWindow::RenderGLScene(void)
{
	Window::RenderGLScene();
	
	static Vector nv; //법선벡터

	glTranslatef(0.0f, 0.0f, -5.0f);
	
	//glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	
	glColor3f(0.7f, 0.7f, 0.0f); //재질의 색깔
	glBegin( GL_TRIANGLES );

	    //{ Front }
		nv = getNormal( Vector(0.0f, 1.0f, 0.0f),
						Vector(-1.0f,-1.0f, 1.0f),
						Vector(1.0f, -1.0f, 1.0f) );
		glNormal3f(nv.x, nv.y, nv.z);
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)


		//{ Right }
		nv = getNormal( Vector(0.0f, 1.0f, 0.0f),
						Vector(1.0f,-1.0f, 1.0f),
						Vector(1.0f,-1.0f,-1.0f) );
		glNormal3f(nv.x, nv.y, nv.z);
		glVertex3f( 0.0f, 1.0f, 0.0f );
		glVertex3f( 1.0f,-1.0f, 1.0f );
		glVertex3f( 1.0f,-1.0f,-1.0f );

		//{ Back }
		nv = getNormal( Vector(0.0f, 1.0f, 0.0f),
						Vector(1.0f,-1.0f,-1.0f),
						Vector(-1.0f,-1.0f,-1.0f) );
		glNormal3f(nv.x, nv.y, nv.z);
		glVertex3f( 0.0f, 1.0f, 0.0f );
		glVertex3f( 1.0f,-1.0f,-1.0f );
		glVertex3f(-1.0f,-1.0f,-1.0f );

		//{ Left }
		nv = getNormal( Vector(0.0f, 1.0f, 0.0f),
						Vector(-1.0f,-1.0f,-1.0f),
						Vector(-1.0f,-1.0f,1.0f) );
		glNormal3f(nv.x, nv.y, nv.z);
		glVertex3f( 0.0f, 1.0f, 0.0f );
		glVertex3f(-1.0f,-1.0f,-1.0f );
		glVertex3f(-1.0f,-1.0f, 1.0f );
	glEnd(); 

	xrot += 0.1f;
	yrot += 0.1f;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	RenderWindow app;
	if(!app.Create(FALSE,"EDin's OpenGL - Light"))
		return EXIT_FAILURE;
	return app.Run();
}