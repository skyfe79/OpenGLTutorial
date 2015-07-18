#ifndef _EGL_DEBUG_H_
#define _EGL_DEBUG_H_

#ifdef _DEBUG
#	define TRACE _TRACE
#else
#	define TRACE
#endif

void _TRACE(char* szMessage, ...);

#endif