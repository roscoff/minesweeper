#pragma once
#include <iostream>
#include <Windows.h>
#include "utilities.h"

class image {
public:
	image();
	~image();
	bool loadImage(std::string loadimage);
	color getPixel(int x, int y);
	int getWidth();
	int getHeight();

private:
	HBITMAP hbmp;
	BITMAP bmp;
};