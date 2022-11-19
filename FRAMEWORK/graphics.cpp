#include "graphics.h"




graphics::graphics()
{
    hdc = CreateCompatibleDC(nullptr);
}

graphics::~graphics()
{
    DeleteObject(hBackBuffer);
    DeleteDC(hdc);
}

void graphics::drawImage(image& img){
    for (int y = 0; y < img.getHeight(); y++) {
        for (int x = 0; x < img.getWidth() ; x++) {
            putPixel(x, y, img.getPixel(x, y));
        }
    }
    
}

void graphics::drawImage(image& img, int posx, int posy, int width, int height)
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            putPixel(x+ posx, y+ posy, img.getPixel(x*(img.getWidth() / (float)width), y * (img.getHeight() / (float)height)));
        }
    }
}

void graphics::putPixel(int x, int y, color col)
{
    if (0 <= x && x < backBuffer.bmWidth  && 0 <= y && y < backBuffer.bmHeight) {
        y = backBuffer.bmHeight - 1 - y;
        BYTE* p = ((BYTE*)backBuffer.bmBits) + y * backBuffer.bmWidthBytes + x * sizeof(color);
        if (col.a > 0) {
            y = backBuffer.bmHeight - 1 - y;
            color back = getPixel(x, y);
            col = back * (col.a / 255.0f) + col * ((255.0f-col.a) / 255.0f);
        }
        *p++ = col.b;
        *p++ = col.g;
        *p = col.r;
   
    }
}

color graphics::getPixel(int x, int y)
{
    y = backBuffer.bmHeight - 1 - y;
    BYTE* p = ((BYTE*)backBuffer.bmBits) + y * backBuffer.bmWidthBytes + x * sizeof(BYTE) * 4;
    color out{*p++, *p++ ,*p++ ,*p };
    return out;
}


void graphics::draw(HWND hWnd)
{
    PAINTSTRUCT paint;
    HDC hWndDc = BeginPaint(hWnd, &paint);
    BitBlt(hWndDc, 0, 0, backBuffer.bmWidth, backBuffer.bmHeight, hdc, 0, 0, SRCCOPY);
    EndPaint(hWnd, &paint);
}

void graphics::onResize(int width, int height, color clearColor)
{
    DeleteObject(hBackBuffer);

    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    hBackBuffer = CreateDIBSection(nullptr, &bmi, DIB_RGB_COLORS, nullptr, 0, 0);
    GetObject(hBackBuffer, sizeof(backBuffer), &backBuffer);
    SelectObject(hdc, hBackBuffer);

    for (int row = 0; row < backBuffer.bmHeight; ++row) {
        BYTE* p = ((BYTE*)backBuffer.bmBits) + row * backBuffer.bmWidthBytes;
        for (int col = 0; col < backBuffer.bmWidth; ++col){
            //base color
            *p++ = clearColor.b; // blue
            *p++ = clearColor.g; // green
            *p++ = clearColor.r; // red
            *p++ = clearColor.a; // alpha
        }
    }
}

void graphics::clearBackground(color col)
{
    BYTE* p = nullptr;
    color* cp = nullptr;
    for (int y = 0; y < backBuffer.bmHeight; y++) {
        p = ((BYTE*)backBuffer.bmBits) + y * backBuffer.bmWidthBytes;
        cp = (color*)p;
        for (int x = 0; x < backBuffer.bmWidth; x++) {
            cp[x] = col;
        }
    }
}

int graphics::getHeight()
{
    return backBuffer.bmHeight;
}

int graphics::getWidth()
{
    return backBuffer.bmWidth;
}



