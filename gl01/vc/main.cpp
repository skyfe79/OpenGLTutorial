#include <windows.h>
#include "egl.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	eglWindow2 app;
	app.Create(hInstance);
	return app.Run();
}