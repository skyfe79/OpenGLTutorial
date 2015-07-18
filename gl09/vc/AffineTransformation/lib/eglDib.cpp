#include "eglDib.h"
#include <stdio.h>

namespace egl {

BOOL Dib::LoadFromFile(const char *filename)
{
	if( mBMPFileHeader )
		free( mBMPFileHeader );

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
	mColorCount= GetColorCount();
	return TRUE;
}
void Dib::CreateLogicalPallete(void)
{
	for(int i=0; i<256; i++)
	{
		RedPal[i]	= (float)mRGBTable[i].rgbRed / 255;
		GreenPal[i]	= (float)mRGBTable[i].rgbGreen / 255;
		BluePal[i]  = (float)mRGBTable[i].rgbBlue / 255;
	}
}
Dib::Dib() : mBMPFileHeader(NULL),mBMPInfo(NULL),mBMPInfoHeader(NULL),
								       mRGBTable(NULL), mRawData(NULL), mColorCount(0)
{
}
Dib::Dib(const char *filename) : mBMPFileHeader(NULL),mBMPInfo(NULL),mBMPInfoHeader(NULL),
								       mRGBTable(NULL), mRawData(NULL), mColorCount(0)
{
	if(!LoadFromFile(filename))
		return ;
}
Dib::~Dib(void)
{
	if( mBMPFileHeader )
		free(mBMPFileHeader);
}
DWORD Dib::GetImageSize(void)
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

UINT Dib::GetWidth(void)
{
	return (UINT)mBMPInfoHeader->biWidth;
}

UINT Dib::GetHeight(void)
{
	return (UINT)mBMPInfoHeader->biHeight;
}
UINT Dib::GetColorCount(void)
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
UINT Dib::GetChannelCount(void)
{
	return mBMPInfoHeader->biBitCount/8;
}
UINT Dib::GetPixelDepth(void)
{
	return mBMPInfoHeader->biBitCount;
}
LPBITMAPINFOHEADER Dib::GetInfoHeaderPtr(void)
{
	return mBMPInfoHeader;
}
LPBITMAPINFO Dib::GetInfoPtr(void)
{
	return mBMPInfo;
}
LPRGBQUAD Dib::GetRGBTablePtr(void)
{
	return mRGBTable;
}
BYTE* Dib::GetRawData(void)
{
	return mRawData;
}

}; //end of namespace