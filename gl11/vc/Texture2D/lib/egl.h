/***************************************************************************
 {                                                                                      
 { EDin's OpenGL Framework 0.3                                                          
 { 03/20/2003                                                                           
 { Sungchul Kim																		  
 { paranwave@korea.com																 
 { 03.20 : support Message Macro system														 
 { 04.08 : using namespace egl
 {
***************************************************************************/


#ifndef _EGL_H_
#define _EGL_H_

#include "eglMsgMacro.h"
#include "eglWindow.h"
#include "eglDib.h"
#include "eglMathUtil.h"
#include "eglDebug.h"

#ifdef EGL_USE_STL
#	include "eglStlUse.h"
#endif

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "odbccp32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#endif