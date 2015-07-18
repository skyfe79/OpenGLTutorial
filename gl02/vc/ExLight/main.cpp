#include <windows.h>
#include "resource.h"
#include "lib\egl.h"



class eglSubWindow : public eglWindow
{
private:
	GLfloat mMaterialAmbient[4];
	GLfloat mMaterialSpecular[4];
	GLfloat mMaterialEmitted[4];
	GLfloat mAmbientLight0[4];
	GLfloat mDiffuseLight0[4];
	GLfloat mSpecularLight0[4];
	GLfloat mPositionLight0[4];
	GLfloat mShininess[1];
	UINT mCurrentObject;
	UINT mCurrentMenu;
	POINT oldPoint;
	GLfloat xrot, yrot;
	UINT numSlice;
	
public:
	virtual BOOL InitGL(void);
	virtual void RenderGLScene(void);
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
	virtual void OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnSize(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual void OnMouseMove(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	friend BOOL CALLBACK ValueDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

eglSubWindow app;


BOOL eglSubWindow::InitGL(void)
{
	eglWindow::InitGL();
	
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	return TRUE;
}
void eglSubWindow::RenderGLScene(void)
{
	eglWindow::RenderGLScene();
	//광원그리기
	

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mMaterialAmbient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mMaterialSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mMaterialEmitted);
	glMaterialfv(GL_FRONT, GL_SHININESS, mShininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, mAmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mDiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mSpecularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, mPositionLight0);
	
	
	glTranslatef(0.0f, 0.0f, -5.0f);
	//광원그리기
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glColor4f(1.0f, 1.0f, 0.5f,1.0f);
	glTranslatef(mPositionLight0[0],mPositionLight0[1],mPositionLight0[2]);
	glutSolidSphere(0.1f,10,10);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	switch(mCurrentObject)
	{
	case 1:
		glutSolidCone(1.5f, 1.5f, numSlice, numSlice);
		break;
	case 2:
		glutWireCone(1.5f, 1.5f, numSlice, numSlice);
		break;
	case 3:
		glutSolidCube(1.5f);
		break;
	case 4:
		glutWireCube(1.5f);
		break;
	case 5:
		glutSolidDodecahedron();
		break;
	case 6:
		glutWireDodecahedron();
		break;
	case 7:
		glutSolidIcosahedron();
		break;
	case 8:
		glutWireIcosahedron();
		break;
	case 9:
		glutSolidOctahedron();
		break;
	case 10:
		glutWireOctahedron();
		break;
	case 11:
		glutSolidSphere(1.5f, numSlice, numSlice);
		break;
	case 12:
		glutWireSphere(1.5f, numSlice, numSlice);
		break;
	case 13:
		glutSolidTetrahedron();
		break;
	case 14:
		glutWireTetrahedron();
		break;
	case 15:
		glutSolidTorus(0.3f, 1.0f, numSlice/2, numSlice);
		break;
	case 16:
		glutWireTorus(0.3f, 1.0f, numSlice/2, numSlice);
		break;
	case 17:
		glutSolidTeapot(1.0);
		break;
	case 18:
		glutWireTeapot(1.0);
		break;
	}
}

void SetArrayValue(GLfloat ar[4], GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4)
{
	ar[0] = v1;
	ar[1] = v2;
	ar[2] = v3;
	ar[3] = v4;
}
void eglSubWindow::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if(wParam == VK_ADD) //+
	{
		++numSlice;		
	}
	if(wParam == VK_SUBTRACT) //-
	{
		--numSlice; if(numSlice<0) numSlice=0;
	}
	eglWindow::OnKeyDown(wParam, lParam);
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

	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 2.0f, 20.0f);
	
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity();           // Reset The Mode
}

void eglSubWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
	mCurrentObject = 17;
	xrot = yrot = 0.0f;
	numSlice = 10;
	SetArrayValue(mMaterialAmbient, 0.5f, 0.5f, 0.5f, 1.0f);
	SetArrayValue(mMaterialSpecular, 1.0f, 1.0f, 1.0f, 1.0f);
	SetArrayValue(mMaterialEmitted, 0.0f, 0.0f, 0.0f, 1.0f);
	
	SetArrayValue(mAmbientLight0, 0.3f, 0.3f, 0.3f, 1.0f);
	SetArrayValue(mDiffuseLight0, 0.7f, 0.7f, 0.7f, 1.0f);
	SetArrayValue(mSpecularLight0, 1.0f, 1.0f, 1.0f, 1.0f);
	SetArrayValue(mPositionLight0, 0.0f, 2.0f, 0.0f, 0.0f);
	mShininess[0] = 128.0f;
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
void eglSubWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch(LOWORD(wParam))
	{
	case IDM_LIGHT_AMBIENT:
		app.mCurrentMenu = 1;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_VALUE_DIALOG), mHWnd, ValueDlgProc);
		break;
	case IDM_LIGHT_DIFFUSE:
		app.mCurrentMenu = 2;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_VALUE_DIALOG), mHWnd, ValueDlgProc);
		break;
	case IDM_LIGHT_SPECULAR:
		app.mCurrentMenu = 3;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_VALUE_DIALOG), mHWnd, ValueDlgProc);
		break;
	case IDM_LIGHT_POSITION:
		app.mCurrentMenu = 4;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_VALUE_DIALOG), mHWnd, ValueDlgProc);
		break;
	case IDM_MATERIAL_AMBIENT_AND_DIFFUSE:
		app.mCurrentMenu = 5;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_VALUE_DIALOG), mHWnd, ValueDlgProc);
		break;
	case IDM_MATERIAL_EMITTED:
		app.mCurrentMenu = 6;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_VALUE_DIALOG), mHWnd, ValueDlgProc);
		break;
	case IDM_MATERIAL_SPECULAR:
		app.mCurrentMenu = 7;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_VALUE_DIALOG), mHWnd, ValueDlgProc);
		break;
	case IDM_MATERIAL_SHININESS:
		app.mCurrentMenu = 8;
		DialogBox(mHInstance, MAKEINTRESOURCE(IDD_VALUE_DIALOG), mHWnd, ValueDlgProc);
		break;

	case IDM_OBJECT_SOLID_CONE:
		app.mCurrentObject = 1;
		break;
	case IDM_OBJECT_WIRE_CONE:
		app.mCurrentObject = 2;
		break;
	case IDM_OBJECT_SOLID_CUBE:
		app.mCurrentObject = 3;
		break;
	case IDM_OBJECT_WIRE_CUBE:
		app.mCurrentObject = 4;
		break;
	case IDM_OBJECT_SOLID_DODECAHEDRON:
		app.mCurrentObject = 5;
		break;
	case IDM_OBJECT_WIRE_DODECAHEDRON:
		app.mCurrentObject = 6;
		break;
	case IDM_OBJECT_SOLID_ICOSAHEDRON:
		app.mCurrentObject = 7;
		break;
	case IDM_OBJECT_WIRE_ICOSAHEDRON:
		app.mCurrentObject = 8;
		break;
	case IDM_OBJECT_SOLID_OCTAHEDRON:
		app.mCurrentObject = 9;
		break;
	case IDM_OBJECT_WIRE_OCTAHEDRON:
		app.mCurrentObject = 10;
		break;
	case IDM_OBJECT_SOLID_SPHERE:
		app.mCurrentObject = 11;
		break;
	case IDM_OBJECT_WIRE_SPHERE:
		app.mCurrentObject = 12;
		break;
	case IDM_OBJECT_SOLID_TETRAHEDRON:
		app.mCurrentObject = 13;
		break;
	case IDM_OBJECT_WIRE_TETRAHEDRON:
		app.mCurrentObject = 14;
		break;
	case IDM_OBJECT_SOLID_TORUS:
		app.mCurrentObject = 15;
		break;
	case IDM_OBJECT_WIRE_TORUS:
		app.mCurrentObject = 16;
		break;
	case IDM_OBJECT_SOLID_TEAPOT:
		app.mCurrentObject = 17;
		break;
	case IDM_OBJECT_WIRE_TEAPOT:
		app.mCurrentObject = 18;
		break;
	}
}

BOOL CALLBACK ValueDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_INITDIALOG:
		switch(app.mCurrentMenu)
		{
		case 1:
			SetDlgItemInt(hDlg, IDC_VALUE1, app.mAmbientLight0[0]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE2, app.mAmbientLight0[1]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE3, app.mAmbientLight0[2]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE4, app.mAmbientLight0[3]*10, TRUE);
			break;
		case 2:
			SetDlgItemInt(hDlg, IDC_VALUE1, app.mDiffuseLight0[0]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE2, app.mDiffuseLight0[1]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE3, app.mDiffuseLight0[2]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE4, app.mDiffuseLight0[3]*10, TRUE);
			break;
		case 3:
			SetDlgItemInt(hDlg, IDC_VALUE1, app.mSpecularLight0[0]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE2, app.mSpecularLight0[1]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE3, app.mSpecularLight0[2]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE4, app.mSpecularLight0[3]*10, TRUE);
			break;
		case 4:
			SetDlgItemInt(hDlg, IDC_VALUE1, app.mPositionLight0[0]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE2, app.mPositionLight0[1]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE3, app.mPositionLight0[2]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE4, app.mPositionLight0[3]*10, TRUE);
			break;
		case 5:
			SetDlgItemInt(hDlg, IDC_VALUE1, app.mMaterialAmbient[0]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE2, app.mMaterialAmbient[1]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE3, app.mMaterialAmbient[2]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE4, app.mMaterialAmbient[3]*10, TRUE);
			break;
		case 6:
			SetDlgItemInt(hDlg, IDC_VALUE1, app.mMaterialEmitted[0]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE2, app.mMaterialEmitted[1]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE3, app.mMaterialEmitted[2]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE4, app.mMaterialEmitted[3]*10, TRUE);
			break;
		case 7:
			SetDlgItemInt(hDlg, IDC_VALUE1, app.mMaterialSpecular[0]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE2, app.mMaterialSpecular[1]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE3, app.mMaterialSpecular[2]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE4, app.mMaterialSpecular[3]*10, TRUE);
			break;
		case 8:
			SetDlgItemInt(hDlg, IDC_VALUE1, app.mShininess[0]*10, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE2, 0, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE3, 0, TRUE);
			SetDlgItemInt(hDlg, IDC_VALUE4, 0, TRUE);
			break;
		}
		return TRUE;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			switch(app.mCurrentMenu)
			{
			case 1:
				SetArrayValue(app.mAmbientLight0, 
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE1, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE2, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE3, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE4, NULL, TRUE))/10
						);
				break;
			case 2:
				SetArrayValue(app.mDiffuseLight0, 
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE1, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE2, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE3, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE4, NULL, TRUE))/10
						);
				break;
			case 3:
				SetArrayValue(app.mSpecularLight0, 
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE1, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE2, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE3, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE4, NULL, TRUE))/10
						);
				break;
			case 4:
				SetArrayValue(app.mPositionLight0, 
					((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE1, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE2, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE3, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE4, NULL, TRUE))/10
						);
				break;
			case 5:
				SetArrayValue(app.mMaterialAmbient, 
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE1, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE2, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE3, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE4, NULL, TRUE))/10
						);
				break;
			case 6:
				SetArrayValue(app.mMaterialEmitted, 
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE1, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE2, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE3, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE4, NULL, TRUE))/10
						);
				break;
			case 7:
				SetArrayValue(app.mMaterialSpecular, 
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE1, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE2, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE3, NULL, TRUE))/10,
						((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE4, NULL, TRUE))/10
						);
				break;
			case 8:
				app.mShininess[0] = ((GLfloat)GetDlgItemInt(hDlg, IDC_VALUE1, NULL, TRUE))/10;
				break;
			}
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
	app.Create(FALSE, "EDin's OpenGL - Glut 객체그리기[ ▶마우스 왼쪽버튼을 누른 후 움직이면 회전 ▶+,- 분할면늘리기 및 줄이기 ▶흰색쿼드는 광원]", 640, 480, 16, MAKEINTRESOURCE(IDR_MAINMENU));
	return app.Run();
}