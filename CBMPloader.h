#pragma once

#ifndef __CBMPLOADER_H__
#define __CBMPLOADER_H__

#include <windows.h>

#define BITMAP_ID 0x4D42

//bitmap loader
class CBMPLoader
{
public:
    CBMPLoader();
    ~CBMPLoader();

    bool LoadBitmap(char* filename);
    void FreeImage();

    unsigned int ID;
    int imageWidth;
    int imageHeight; 
    unsigned char* image;
};

#endif //__CBMPLOADER_H__


