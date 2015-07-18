#include <windows.h>
#include "resource.h"
#include "lib\egl.h"

class eglSubWindow : public eglWindow
{
private:
	int mCheck;
	GLfloat mPointSize; //점크기
	GLfloat mLineWidth; //선굵기
	BOOL	mIsStipple; //스티플
	GLenum  mStateMode; //선택모드
	
	//heler functions
	void DrawPoint(GLfloat PointSize);
	void DrawLine(GLfloat LineWidth, BOOL IsStipple);
	void DrawObject(GLenum StateMode);
	void DrawLineLoop(void);
	static BOOL CALLBACK PointDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK LineDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
public:
	virtual void RenderGLScene(void);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
	virtual void OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnSize(WPARAM wParam, LPARAM lParam);
};
eglSubWindow app;

void eglSubWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	mCheck = 1;
	mPointSize = 1.0f;
	mLineWidth = 1.0f;
	mIsStipple = FALSE;
	mStateMode = GL_POLYGON;
}
void eglSubWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
	GLsizei width  = LOWORD(lParam);
	GLsizei height = HIWORD(lParam);

	if (height == 0)
		height = 1;                     // Making Height Equal One

	glViewport( 0, 0, width, height ); // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);       // Select The Projection Matrix
	glLoadIdentity();                  // Reset The Projection Matrix

	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 10.0f);
	
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity();           // Reset The Mode
}
void eglSubWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch(LOWORD(wParam))
	{
	case IDM_DRAW_POINT:
		mCheck=1;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_POINT_DIALOG), mHWnd,PointDlgProc);
		break;
	case IDM_DRAW_LINE:
		mCheck=2;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_LINE_DIALOG), mHWnd, LineDlgProc);
		break;
	case IDM_DRAW_LINELOOP:
		mCheck=4;
		break;
	case IDM_DRAW_STIPPLE_LINE:
		mIsStipple = !mIsStipple;
		mCheck=2;
		break;
	case IDM_DRAW_POLYGON:
		mCheck=3;
		mStateMode = GL_POLYGON;
		break;
	case IDM_DRAW_QUADS:
		mCheck=3;
		mStateMode = GL_QUADS;
		break;
	case IDM_DRAW_TRIANGLE:
		mCheck=3;
		mStateMode = GL_TRIANGLES;
		break;
	}
}

void eglSubWindow::RenderGLScene(void)
{
	eglWindow::RenderGLScene();
	glColor3f(1.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch(mCheck)
	{
	case 1:
		DrawPoint(mPointSize);
		break;
	case 2:
		DrawLine(mLineWidth, mIsStipple);
		break;
	case 3:
		DrawObject(mStateMode);
		break;
	case 4:
		DrawLineLoop();
		break;
	}
}

void eglSubWindow::DrawPoint(GLfloat PointSize)
{
	glPointSize(PointSize);
	glBegin(GL_POINTS);
		glVertex2f(0.0f, 0.0f);
	glEnd();
}

void eglSubWindow::DrawLine(GLfloat LineWidth, BOOL IsStipple)
{
	if(IsStipple)
	{
		glLineStipple(4, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
	}
	glLineWidth(LineWidth);
	glBegin(GL_LINES);
		glVertex2f(-0.7f, 0.0f);
		glVertex2f(0.7f, 0.0f);
	glEnd();
	glLineWidth(1.0f);

	glDisable(GL_LINE_STIPPLE);
}

void eglSubWindow::DrawObject(GLenum StateMode)
{
	if(StateMode == GL_POLYGON)
	{
		glBegin(GL_POLYGON);
			glVertex2f(-0.3f,  0.3f);
			glVertex2f( 0.4f,  0.4f);
			glVertex2f( 0.6f, -0.4f);
			glVertex2f(-0.3f, -0.6f);
			glVertex2f(-0.6f, -0.5f);
		glEnd();
	}
	else if(StateMode == GL_QUADS)
	{
		glBegin(GL_QUADS);
			glVertex2f(-0.5f,  0.5f);
			glVertex2f(-0.75f, 0.25f);
			glVertex2f(-0.25f, 0.0f);
			glVertex2f(0.0f, 0.5f);
		glEnd();
	}
	else if(StateMode == GL_TRIANGLES)
	{
		glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f,  0.3f);
			glVertex2f(-0.6f, -0.3f);
			glVertex2f( 0.5f,  0.1f);
		glEnd();
	}
}

void eglSubWindow::DrawLineLoop(void)
{
	glBegin(GL_LINE_LOOP);
		glVertex2f(-1.0f,  0.75f);
		glVertex2f( 1.0f,  0.75f);

		glVertex2f(-1.0f, 0.25f);
		glVertex2f( 1.0f, 0.25f);

		glVertex2f(-1.0f, -0.25f);
		glVertex2f( 1.0f, -0.25f);

		glVertex2f(-1.0f, -0.75f);
		glVertex2f( 1.0f, -0.75f);
	glEnd();
}

BOOL CALLBACK eglSubWindow::PointDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			app.mPointSize = (GLfloat)GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
BOOL CALLBACK eglSubWindow::LineDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			app.mLineWidth = (GLfloat)GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	app.Create(FALSE, "OpenGL ex03-Menu", 640, 480, 16, MAKEINTRESOURCE(IDR_MAINMENU));
	return app.Run();
}