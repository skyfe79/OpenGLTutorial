#include "eglDib.h"
#include <stdio.h>

BOOL eglDib::LoadBitmapFromFile(const char *filename)
{
	HANDLE	hFile;
	DWORD	FileSize, ReadCount;
	hFile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}
	FileSize = GetFileSize(hFile, NULL);
	if(mBMPFileHeader)
		free(mBMPFileHeader);

	mBMPFileHeader = (BITMAPFILEHEADER*)malloc(FileSize);
	ReadFile(hFile, mBMPFileHeader, FileSize, &ReadCount, NULL);
	CloseHandle(hFile);

	mRawData  = (PBYTE)mBMPFileHeader + mBMPFileHeader->bfOffBits;
	mBMPInfo  = (BITMAPINFO*)((PBYTE)mBMPFileHeader+sizeof(BITMAPFILEHEADER));
	mBMPInfoHeader = (BITMAPINFOHEADER*)((PBYTE)mBMPFileHeader+sizeof(BITMAPFILEHEADER));
	mRGBTable = (RGBQUAD*)((PBYTE)mBMPInfoHeader + mBMPInfoHeader->biSize);
	if(mBMPInfoHeader->biBitCount == 8)
	{
		CreateLogicalPallete();
	}
	mNumColors= GetNumColors();
	return TRUE;
}
void eglDib::CreateLogicalPallete(void)
{
	for(int i=0; i<256; i++)
	{
		RedPal[i]	= (float)mRGBTable[i].rgbRed / 255;
		GreenPal[i]	= (float)mRGBTable[i].rgbGreen / 255;
		BluePal[i]  = (float)mRGBTable[i].rgbBlue / 255;
	}
}
eglDib::eglDib(const char *filename) : mBMPFileHeader(NULL),mBMPInfo(NULL),mBMPInfoHeader(NULL),
								       mRGBTable(NULL), mRawData(NULL), mNumColors(0)
{
	if(!LoadBitmapFromFile(filename))
		return ;
}
eglDib::~eglDib(void)
{
	free(mBMPFileHeader);
}
DWORD eglDib::GetImageSize(void)
{
	if(mBMPInfoHeader->biSizeImage == 0)
	{
		DWORD Width  = (DWORD)GetWidth();
		DWORD Height = (DWORD)GetHeight();

		DWORD imageSize = Width*Height;
		return imageSize;
	}
	else
	{
		return mBMPInfoHeader->biSizeImage;
	}
}

UINT eglDib::GetWidth(void)
{
	return (UINT)mBMPInfoHeader->biWidth;
}

UINT eglDib::GetHeight(void)
{
	return (UINT)mBMPInfoHeader->biHeight;
}
UINT eglDib::GetNumColors(void)
{
	if((mBMPInfoHeader->biClrUsed == 0) && (mBMPInfoHeader->biBitCount<9))
	{
		return (1<<mBMPInfoHeader->biBitCount);
	}
	else
	{
		return (UINT)mBMPInfoHeader->biClrUsed;
	}
}
UINT eglDib::GetNumChannels(void)
{
	return mBMPInfoHeader->biBitCount/8;
}
UINT eglDib::GetPixelDepth(void)
{
	return mBMPInfoHeader->biBitCount;
}
LPBITMAPINFOHEADER eglDib::GetInfoHeaderPtr(void)
{
	return mBMPInfoHeader;
}
LPBITMAPINFO eglDib::GetInfoPtr(void)
{
	return mBMPInfo;
}
LPRGBQUAD eglDib::GetRGBTablePtr(void)
{
	return mRGBTable;
}
BYTE* eglDib::GetRawData(void)
{
	return mRawData;
}