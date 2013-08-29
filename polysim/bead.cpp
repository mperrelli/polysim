#include "bead.h"

bead::bead(int x, int y)
{
	this->x = x;
	this->y = y;
}

bead::~bead(void)
{
}

int bead::getY()
{
	return y;
}

int bead::getX()
{
	return x;
}
