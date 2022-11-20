#pragma once
#include "graphics.h"
#include "meshBuilder.h"
#include "mineSweeper.h"

class framework{
public:
	framework();
	void onMouseEvent(int x, int y);
	void onLeftMouseClick(int x, int y);
	void onRightMouseClick(int x, int y);
	void onKeyboardEvent();
	void onEnterKey();
	void setRedraw();
	void update();
	void init();

	void onResize(int width, int height, color clearColor = { 0, 0, 0, 0 });
	void draw(HWND hWnd);
private:
	meshBuilder mb;
	mineSweeper ms;
	graphics fx;
};