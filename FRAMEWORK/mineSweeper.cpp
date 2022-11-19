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
	x(x), y(y),
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
	for (int y = 0; y < ycell; y++) {
		for (int x = 0; x < xcell; x++) {
			int nbb = fld.getCell(x, y).getNbBomb();
			bool hasbomb = fld.getCell(x, y).hasBomb();
			bool flaged = fld.getCell(x, y).isFlaged();
			bool revealed = fld.getCell(x, y).revealed();

			if (revealed) {
				if (hasbomb) {
					gfx->drawImage(bomb, x * cellwidth, y * cellheight, cellwidth, cellheight);
				}
				else {
					switch (nbb)
					{
					case 1:
						gfx->drawImage(case1, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					case 2:
						gfx->drawImage(case2, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					case 3:
						gfx->drawImage(case3, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					case 4:
						gfx->drawImage(case4, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					case 5:
						gfx->drawImage(case5, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					case 6:
						gfx->drawImage(case6, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					case 7:
						gfx->drawImage(case7, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					case 8:
						gfx->drawImage(case8, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					default:
						gfx->drawImage(revealedcase, x * cellwidth, y * cellheight, cellwidth, cellheight);
						break;
					}
				}
			}
			else {
				if (flaged) gfx->drawImage(flag, x * cellwidth, y * cellheight, cellwidth, cellheight);
				else gfx->drawImage(hidecase, x * cellwidth, y * cellheight, cellwidth, cellheight);
			}
		}
	}
}

void mineSweeper::onLeftMouseClick(int xpos, int ypos)
{
	if (!gameOver) {
		if (x <= xpos && xpos < xcell * cellwidth && y <= ypos && ypos < ycell * cellheight) {
			int xc = (xpos - x) / cellwidth;
			int yc = (ypos - y) / cellheight;
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

void mineSweeper::onRightMouseClick(int xpos, int ypos){
	if (!gameOver) {
		if (x <= xpos && xpos < xcell * cellwidth && y <= ypos && ypos < ycell * cellheight) {
			int xcell = (xpos - x) / cellwidth;
			int ycell = (ypos - y) / cellheight;
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
