///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  File:      polymer.cpp                                         *//
//*  Author:    Matt Perrelli                                       *//
//*                                                                 *//
//*  This is the implementation code for the polymer class. This    *//
//*  holds all the basic functionality for managing linear          *//
//*  polymers.                                                      *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "polymer.h"
#include "bead.h"


// Constructor for a polymer. When a polymer is made it is
// automatically given an initial bead at coordinates 0,0
//
polymer::polymer(void)
{
	beadCount = 0;
	bead* newBead = new bead(0, 0);
	beads[beadCount] = newBead;
	beadCount++;	
}

// Destructor for a polymer.
//
polymer::~polymer(void)
{
	
}

// Adds a bead to the end of a polymer. Uses a random number to
// select which direction to grow in
//
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

// A conveniance function to add multiple beads at once
//
void polymer::addBeads(int amount)
{
	for(int i = 0; i < amount; i++)
	{
		addBead();
	}
}

// Returns the next available bead location in the array of beads
//
int polymer::getBeadCount()
{
	return beadCount;
}

// Returns the Squared Radius of Gyration. Calculated by running
// the coordinate distance formula on the first and last beads
// in a polymer.
//
double polymer::getSquaredRadiusGyration()
{
	int x1 = beads[0]->getX();
	int y1 = beads[0]->getY();
	int x2 = beads[beadCount - 1]->getX();
	int y2 = beads[beadCount - 1]->getY();

	double distance = ((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1));

	return sqrt(distance);
}
