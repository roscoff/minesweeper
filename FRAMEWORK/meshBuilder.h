#pragma once
#include "graphics.h"
#include "utilities.h"


class meshBuilder {
public:
	meshBuilder(graphics* gph);

	void drawCircle(int x, int y, int radius, color col);
	void drawQuad(point v1, point v2, point v3, point v4, color col);
	void drawTriangle(point v1, point v2, point v3, color col);
private:
	graphics* gph;
};