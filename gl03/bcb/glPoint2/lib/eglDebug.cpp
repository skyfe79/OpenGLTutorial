#include "eglDebug.h"
#include <windows.h> 
#include <stdio.h> 
#include <stdarg.h> 

void _TRACE(char* szMessage, ...) 
{ 
     char szDebugMsg[256]; 
     va_list va;  
     va_start(va, szMessage);  
     vsprintf(szDebugMsg, szMessage, (va_list)va);  
     va_end(va); 
     OutputDebugString(szDebugMsg); 
} 
