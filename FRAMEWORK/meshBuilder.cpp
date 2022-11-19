#include "meshBuilder.h"


meshBuilder::meshBuilder(graphics* graphics) : gph(graphics)
{

}


void meshBuilder::drawCircle(int posx, int posy, int radius, color col)
{
    for (int y = -radius; y < radius; y++) {
        for (int x = -radius; x < radius; x++) {
            if (x * x + y * y < radius * radius){
                gph->putPixel(x + posx, y + posy, col);
            }
        }
    }
}

void meshBuilder::drawQuad(point v1, point v2, point v3, point v4, color col)
{
    //draw face v1 v2 v3 
    drawTriangle(v1, v2, v3, col);
    //draw face v1 v3 v4
    drawTriangle(v1, v3, v4, col);
}

void meshBuilder::drawTriangle(point v1, point v2, point v3, color col)
{
    if (v1.y > v2.y) swapvalue(v1, v2);
    if (v2.y > v3.y) swapvalue(v3, v2);
    if (v1.y > v2.y) swapvalue(v1, v2);

    //v1.y < v2.y < v3.y
    //draw v1.y to v2.y
    float mp = linearInterpolation((float)v1.x, (float)v3.x, (v2.y - v1.y) / (float)(v3.y - v1.y));
    for (int y = v1.y; y < v2.y; y++) {
        float adv = (y - v1.y) / (float)(v2.y - v1.y);
        float x1 = linearInterpolation((float)v1.x, (float)v2.x, adv);
        float x2 = linearInterpolation((float)v1.x, mp, adv);
        //change side if
        if (x1 > x2) swapvalue(x1, x2);
        for (int x = (int)x1+1; x <= x2; x++) {
            gph->putPixel(x, y, col);
        }
    }
    //draw v2.y to v3.y
    for (int y = v2.y; y < v3.y; y++) {
        float adv = 1 - (y - v2.y) / (float)(v3.y - v2.y);
        float x1 = linearInterpolation((float)v3.x, mp, adv);
        float x2 = linearInterpolation((float)v3.x, (float)v2.x, adv);

        //change side if
        if (x1 > x2) swapvalue(x1, x2);
        for (int x = (int)x1+1; x <= x2; x++) {
            gph->putPixel(x, y, col);
        }
    }

}