#pragma once
#include <windows.h>
#include "utilities.h"
#include "image.h"

class graphics {
public:
	graphics();
	~graphics();

	void drawImage(image& img);
	void drawImage(image& img,int x, int y, int width, int height);
	void putPixel(int x, int y, color col);
	color getPixel(int x, int y);

	void draw(HWND hWnd);
	void onResize(int width, int height, color clearColor = { 0, 0, 0, 0 });
	void clearBackground(color col = { 0,0,0 });

	int getHeight();
	int getWidth();

private:
	HBITMAP hBackBuffer;
	BITMAP  backBuffer;
	HDC hdc;
};