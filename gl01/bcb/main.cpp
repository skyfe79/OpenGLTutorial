#include <windows.h>
#pragma hdrstop
#include "lib\egl.h"

#pragma argsused
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	eglWindow2 app;
	app.Create(hInstance);
	return app.Run();
}