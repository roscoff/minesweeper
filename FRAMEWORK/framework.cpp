#include "framework.h"


framework::framework() : fx(), mb(&fx), ms(100,100,1600, 800, &fx, 0.13f)
{

}

void framework::onMouseEvent(int x, int y)
{
    //mb.drawCircle(x, y, 5, { 255,255,255 });
}



void framework::onLeftMouseClick(int x, int y)
{
    ms.onLeftMouseClick(x, y);
}

void framework::onRightMouseClick(int x, int y)
{
    ms.onRightMouseClick(x, y);
}

void framework::onKeyboardEvent()
{
}

void framework::onEnterKey()
{
    ms.startNewGame();
}

void framework::setRedraw()
{
    ms.setRedraw();
}

void framework::update()
{
    int w = fx.getWidth(), h = fx.getHeight();
    //drawCircle(randBetween(0, w), randBetween(0, h), randBetween(5, 12), { (BYTE)randBetween(0, 255),(BYTE)randBetween(0, 255),(BYTE)randBetween(0, 255) });
    //clearBackground({255,0,0});
    /*mb.drawTriangle({ 100,100 }, { 300, 200 }, { 200,400 }, { 0,0,255 });
    mb.drawTriangle({ 300,100 }, { 100, 200 }, { 200,400 }, { 0,255,255 });*/

    /*int x = randBetween(0, w);
    int y = randBetween(0, h);
    int dx = randBetween(10, 100);
    int dy = randBetween(10, 100);
    mb.drawQuad({ x, y }, {x+dx,y + randBetween(-50,50)}, {x + dx + randBetween(-50,50) ,y + dy}, {x + +randBetween(-50,50) ,y + dy+ +randBetween(-50,50) }, {255,255,255, 253});
    mb.drawTriangle({ 500,100 }, { 400, 200 }, { 600,200 }, { 0,255,0,200 });*/

    /*for (int y = 0; y < backBuffer.bmHeight/10; y++) {
        for (int x = 0; x < backBuffer.bmWidth/10; x++) {
            int factor = nbDivisor(y * backBuffer.bmWidth + x)*5;
            color c = { (BYTE)factor, (BYTE)factor, (BYTE)factor };

            mb.drawQuad({ x * 10, y * 10 }, { x * 10 + 10, y * 10 }, { x * 10 + 10, y * 10 + 10 }, { x * 10, y * 10 + 10 }, c);
        }
    }*/
}

void framework::init()
{
}

void framework::onResize(int width, int height, color clearColor)
{
    fx.onResize(width, height, clearColor);
    setRedraw();
}

void framework::draw(HWND hWnd)
{
    if (ms.needRedraw()) {
        ms.draw();
        fx.draw(hWnd);
    }
}
