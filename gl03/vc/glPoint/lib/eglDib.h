/* {                                                              } 
   { 윈도우즈 BMP 파일을 읽어 오는 역할을 한다.                     }
   { 쓰는 기능은 없다.                                             }
   { 기타 기능으로 BMP 파일의 정보 읽기 정도                        }
   {                                                              }
   { 제작 : 김성철( paranwave@korea.com )                         }
   {                                                              } */
#ifndef _EGL_DIB_H_
#define _EGL_DIB_H_

#include <windows.h>

class eglDib
{
protected:
	LPBITMAPFILEHEADER mBMPFileHeader;
	LPBITMAPINFO	   mBMPInfo;
	LPBITMAPINFOHEADER mBMPInfoHeader;
	RGBQUAD			   *mRGBTable;
	BYTE			   *mRawData;
	UINT			   mNumColors;
	BOOL LoadBitmapFromFile(const char * filename);
	void CreateLogicalPallete(void);
	eglDib();
	
public:
	float RedPal[256], GreenPal[256], BluePal[256];

	eglDib(const char * filename);
	~eglDib(void);
	DWORD GetImageSize(void);
	UINT  GetWidth(void);
	UINT  GetHeight(void);
	UINT  GetNumChannels(void);
	UINT  GetNumColors(void);
	UINT  GetPixelDepth(void);
	LPBITMAPINFOHEADER GetInfoHeaderPtr(void);
	LPBITMAPINFO GetInfoPtr(void);
	LPRGBQUAD GetRGBTablePtr(void);
	BYTE* GetRawData(void);
};


#endif