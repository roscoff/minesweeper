#include "image.h"



image::image()
{
}

image::~image()
{
	DeleteObject(hbmp);
}


bool image::loadImage(std::string loadimage){
	hbmp = (HBITMAP)LoadImageA(NULL, loadimage.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION);
	GetObject(hbmp, sizeof(bmp), &bmp);
	return hbmp == nullptr;
}

color image::getPixel(int x, int y){
	y = bmp.bmHeight - 1 - y;
	BYTE* p = ((BYTE*)bmp.bmBits) + y * bmp.bmWidthBytes + x * bmp.bmBitsPixel/8;
	color out{};
	out.b = *p++;
	out.g = *p++;
	out.r = *p;
	out.a = 0;
	return out;
}

int image::getWidth(){
	return bmp.bmWidth;
}

int image::getHeight(){
	return bmp.bmHeight;
}

