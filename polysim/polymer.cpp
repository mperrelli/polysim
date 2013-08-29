#include <iostream>
#include <stdlib.h>
#include "polymer.h"
#include "bead.h"

polymer::polymer(void)
{
	beads[beadCount] = new bead(0, 0);
	beadCount = 1;
}

polymer::~polymer(void)
{
	
}

void polymer::addBead()
{
	int x = beads[beadCount - 1]->getX();
	int y = beads[beadCount - 1]->getY();

	int growDirection = rand() % 4 + 1;

	switch(growDirection)
	{
	case 1:
		// Grow North
		y++;

	case 2:
		// Grow South
		y--;

	case 3:
		// Grow East
		x++;

	case 4:
		// Grow West
		x--;

	default:;

	}

	bead *newBead = new bead(x, y);
	beads[beadCount] = newBead;
	beadCount++;
}

int polymer::getBeadCount()
{
	return beadCount;
}
