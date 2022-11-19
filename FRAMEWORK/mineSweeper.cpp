#include "mineSweeper.h"
#include "utilities.h"

field::field(int nbxcell, int nbycell, int nbBomb)
{
	xcell = nbxcell;
	ycell = nbycell;
	tab = new cell[ycell * xcell]();
	//tab = (cell*)malloc(sizeof(cell) * xcell * ycell);

	replaceBomb(xcell, ycell, nbBomb);
}

field::~field()
{
	delete[] tab;
}

cell& field::getCell(int x, int y){
	return tab[y * xcell + x];
}

void field::replaceBomb(int nbxcell, int nbycell, int nbBomb){
	//clear bomb if exist
	for (int y = 0; y < nbycell; y++) {
		for (int x = 0; x < nbxcell; x++) {
			getCell(x, y).removeBomb();
			getCell(x, y).setNbBomb(0);
		}
	}


	while (nbBomb > 0) {
		int x = randBetween(0, nbxcell - 1);
		int y = randBetween(0, nbycell - 1);
		if (!getCell(x, y).hasBomb()) {
			//place the bomb
			getCell(x, y).placeBomb();
			nbBomb--;
			//calcul bomb around
			for (int j = max(y - 1, 0); j <= min(y + 1, nbycell - 1); j++) {
				for (int i = max(x - 1, 0); i <= min(x + 1, nbxcell - 1); i++) {
					getCell(i, j).setNbBomb(getCell(i, j).getNbBomb() + 1);
				}
			}
		}
	}

	//calcul bomb around
	/*for (int j = 0; j < ycell; j++) {
		for (int i = 0; i < xcell; i++) {
			int nbBomb = 0;
			for (int y = max(j - 1, 0); y <= min(j + 1, ycell-1) ; y++) {
				for (int x = max(i - 1, 0); x <= min(i + 1, xcell-1); x++) {

					if (getCell(x, y).hasBomb()) {
						nbBomb++;
					}
				}
			}
			getCell(i, j).setNbBomb(nbBomb);
		}
	}*/
}

void field::maskAndDeflagAll(){
	for (int y = 0; y < ycell; y++) {
		for (int x = 0; x < xcell; x++) {
			getCell(x, y).hide();
			getCell(x, y).removeFlag();
		}
	}
}

void field::revealAll(){
	for (int y = 0; y < ycell; y++) {
		for (int x = 0; x < xcell; x++) {
			getCell(x, y).reveal();
		}
	}
}

cell::cell():mined(false), breveal(false), flaged(false), nbBombAround(0) {
}


bool cell::hasBomb(){
	return mined;
}

bool cell::revealed(){
	return breveal;
}

bool cell::isFlaged(){
	return flaged;
}

void cell::placeBomb(){
	mined = true;
}

void cell::removeBomb(){
	mined = false;
}

void cell::placeFlag(){
	flaged = true;
}

void cell::removeFlag(){
	flaged = false;
}

void cell::reveal(){
	breveal = true;
}

void cell::hide()
{
	breveal = false;
}

void cell::setNbBomb(int bomb){
	nbBombAround = bomb;
}

int cell::getNbBomb(){
	return nbBombAround;
}

mineSweeper::mineSweeper(int x, int y, int width, int height, graphics* gfx, float bombDensity) :
	xpos(x), ypos(y),
	width(width), height(height),
	cellwidth(30), cellheight(30),
	xcell(width / cellwidth), ycell(height / cellheight),
	firstClick(true),
	bombDensity(bombDensity),
	gameOver(false),
	gfx(gfx),
	fld(xcell, ycell, int(xcell* ycell * bombDensity))
{
	flag.loadImage("images/minesweeper/flag.bmp");
	bomb.loadImage("images/minesweeper/bomb.bmp");
	over.loadImage("images/minesweeper/over.bmp");
	hidecase.loadImage("images/minesweeper/case.bmp");
	revealedcase.loadImage("images/minesweeper/caseempty.bmp");
	case1.loadImage("images/minesweeper/case1.bmp");
	case2.loadImage("images/minesweeper/case2.bmp");
	case3.loadImage("images/minesweeper/case3.bmp");
	case4.loadImage("images/minesweeper/case4.bmp");
	case5.loadImage("images/minesweeper/case5.bmp");
	case6.loadImage("images/minesweeper/case6.bmp");
	case7.loadImage("images/minesweeper/case7.bmp");
	case8.loadImage("images/minesweeper/case8.bmp");
}

mineSweeper::~mineSweeper()
{
}

void mineSweeper::draw()
{
	if (gameOver) {
		fld.revealAll();
	}
	for (int y = 0; y < ycell; y++) {
		for (int x = 0; x < xcell; x++) {
			int nbb = fld.getCell(x, y).getNbBomb();
			bool hasbomb = fld.getCell(x, y).hasBomb();
			bool flaged = fld.getCell(x, y).isFlaged();
			bool revealed = fld.getCell(x, y).revealed();
			int xcoord = x * cellwidth + xpos;
			int ycoord = y * cellheight + ypos;
			if (revealed) {
				if (hasbomb) {
					gfx->drawImage(bomb, xcoord, ycoord, cellwidth, cellheight);
				}
				else {
					switch (nbb)
					{
					case 1:
						gfx->drawImage(case1, xcoord, ycoord, cellwidth, cellheight);
						break;
					case 2:
						gfx->drawImage(case2, xcoord, ycoord, cellwidth, cellheight);
						break;
					case 3:
						gfx->drawImage(case3, xcoord, ycoord, cellwidth, cellheight);
						break;
					case 4:
						gfx->drawImage(case4, xcoord, ycoord, cellwidth, cellheight);
						break;
					case 5:
						gfx->drawImage(case5, xcoord, ycoord, cellwidth, cellheight);
						break;
					case 6:
						gfx->drawImage(case6, xcoord, ycoord, cellwidth, cellheight);
						break;
					case 7:
						gfx->drawImage(case7, xcoord, ycoord, cellwidth, cellheight);
						break;
					case 8:
						gfx->drawImage(case8, xcoord, ycoord, cellwidth, cellheight);
						break;
					default:
						gfx->drawImage(revealedcase, xcoord, ycoord, cellwidth, cellheight);
						break;
					}
				}
			}
			else {
				if (flaged) gfx->drawImage(flag, xcoord, ycoord, cellwidth, cellheight);
				else gfx->drawImage(hidecase, xcoord, ycoord, cellwidth, cellheight);
			}
		}
	}

	if (gameOver) {
		gfx->drawImage(over, xcell*cellwidth/2.0f - over.getWidth()/2.0f + xpos, ycell * cellheight / 2.0f - over.getHeight() / 2.0f + ypos, over.getWidth(), over.getHeight());
	}
}

void mineSweeper::onLeftMouseClick(int mouseX, int mouseY)
{
	if (!gameOver) {
		mouseX -= xpos;
		mouseY -= ypos;
		if (0 <= mouseX && mouseX < xcell * cellwidth && 0 <= mouseY && mouseY < ycell * cellheight) {
			int xc = (mouseX) / cellwidth;
			int yc = (mouseY) / cellheight;
			cell* c = &fld.getCell(xc, yc);
			if (firstClick) {
				while (fld.getCell(xc, yc).getNbBomb() != 0) {
					fld.replaceBomb(xcell, ycell, int(xcell * ycell * bombDensity));
				}
				firstClick = false;
			}

			if (!c->isFlaged()) {
				if (c->getNbBomb() == 0) {
					revealSurrounding(xc, yc);
				}
				else {
					c->reveal();
					if (c->hasBomb()) {
						gameOver = true;
					}
				}
			}
		}
	}
	draw();
}

void mineSweeper::onRightMouseClick(int mouseX, int mouseY){
	if (!gameOver) {
		mouseX -= xpos;
		mouseY -= ypos;
		if (0 <= mouseX && mouseX < xcell * cellwidth && 0 <= mouseY && mouseY < ycell * cellheight) {
			int xcell = (mouseX) / cellwidth;
			int ycell = (mouseY) / cellheight;
			cell* c = &fld.getCell(xcell, ycell);
			if (!c->revealed()) {
				if (c->isFlaged()) {
					c->removeFlag();
				}
				else {
					c->placeFlag();
				}
			}
		}
	}
	draw();
}

void mineSweeper::startNewGame()
{
	gameOver = false;
	firstClick = true;
	fld.replaceBomb(xcell, ycell, xcell*ycell*bombDensity);
	fld.maskAndDeflagAll();
	draw();
}

void mineSweeper::revealSurrounding(int xc, int yc)
{
	if(fld.getCell(xc, yc).getNbBomb() == 0) {
		for (int ycs = max(yc - 1, 0); ycs < min(yc + 2, ycell); ycs++) {
			for (int xcs = max(xc - 1, 0); xcs < min(xc + 2, xcell); xcs++) {

				if (!fld.getCell(xcs, ycs).revealed()) {
					fld.getCell(xcs, ycs).reveal();
					revealSurrounding(xcs, ycs);
				}
			}
		}
	}
}
