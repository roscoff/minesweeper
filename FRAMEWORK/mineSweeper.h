#pragma once
#include "graphics.h"
#include "image.h"


class cell {
public:
	cell();
	bool hasBomb();
	bool revealed();
	bool isFlaged();

	void placeBomb();
	void removeBomb();
	void placeFlag();
	void removeFlag();
	void reveal();
	void hide();
	void setNbBomb(int bomb);
	int getNbBomb();
private:
	bool breveal;
	bool mined;
	bool flaged;
	int nbBombAround;
};

class field {
public:
	field(int xcell, int ycell, int nbBomb);
	~field();
	cell& getCell(int x, int y);
	void replaceBomb(int nbxcell, int nbycell, int nbBomb);
private:
	int xcell, ycell;
	cell* tab;
};

class mineSweeper {
public:
	mineSweeper(int x, int y, int width, int height, graphics* gfx, float bombDensity);
	~mineSweeper();
	void draw();
	void onLeftMouseClick(int x, int y);
	void onRightMouseClick(int x, int y);
private:
	void revealSurrounding(int xcell, int ycell);
	int x, y;
	int width, height;
	int cellwidth, cellheight;
	int xcell, ycell;
	bool firstClick;
	float bombDensity;
	bool gameOver;
	graphics* gfx;
	field fld;

	image flag;
	image bomb;
	image hidecase;
	image revealedcase;
	image case1;
	image case2;
	image case3;
	image case4;
	image case5;
	image case6;
	image case7;
	image case8;
};