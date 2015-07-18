#include <windows.h>
#include "lib\egl.h"

using namespace egl;

class RenderWindow : public Window
{
private:
	GLuint textures[2];
	Dib image1, image2;
	GLfloat rot;
	GLuint currentTexId;
public:
	virtual BOOL InitGL(void);
	virtual void RenderGLScene(void);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnClose(WPARAM wParam, LPARAM lParam);
};

void RenderWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	rot = 0.0f;
	currentTexId = 0;
}
void RenderWindow::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if(wParam == VK_ESCAPE)
	{
		SendMessage(mHWnd, WM_CLOSE, 0, 0);
	}
	if(wParam == VK_F1)
	{
		if(currentTexId == textures[0])
		{
			currentTexId = textures[1];
		}
		else if(currentTexId == textures[1])
		{
			currentTexId = textures[0];
		}
		else
		{
			currentTexId = textures[0];
		}
	}
	Window::OnKeyDown(wParam, lParam);
}

void RenderWindow::OnClose(WPARAM wParam, LPARAM lParam)
{
	glDeleteTextures(2, textures);
	Window::OnClose(wParam, lParam);
}

BOOL RenderWindow::InitGL(void)
{
	Window::InitGL();
	if(!image1.LoadFromFile("edin01.bmp"))
	{
		MessageBox(NULL, "edin01.bmp 파일을 불러올 수 없습니다", "오류", MB_OK);
		return FALSE;
	}
	if(!image2.LoadFromFile("eva.bmp"))
	{
		MessageBox(NULL, "eva.bmp 파일을 불러올 수 없습니다", "오류", MB_OK);
		return FALSE;
	}

	glGenTextures(2, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1.GetWidth(), image1.GetHeight(), 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, image1.GetRawData());

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2.GetWidth(), image2.GetHeight(), 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, image2.GetRawData());

	glEnable(GL_TEXTURE_2D);
	
	currentTexId = textures[0];
	
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	return TRUE;
}

void RenderWindow::RenderGLScene(void)
{
	Window::RenderGLScene();

	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rot, 1.0f, 0.0f, 0.0f);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, currentTexId);	
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
	glEnd();

	rot += 0.1f;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	RenderWindow app;
	if(!app.Create(FALSE, "EDin's OpenGL - Texture2D-2"))
		return EXIT_FAILURE;
	return app.Run();
}