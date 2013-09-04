///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  File:      sample.cpp                                          *//
//*  Author:    Matt Perrelli                                       *//
//*                                                                 *//
//*  This is the implementation code for the sample class. This     *//
//*  holds all the basic functionality for managing linear          *//
//*  samples.                                                       *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
#include "sample.h"
#include "bead.h"


// Constructor for a sample. When a sample is made it is
// automatically given an initial bead at coordinates 0,0
//
sample::sample(void)
{
	beadCount = 0;
	bead* newBead = new bead(0, 0);
	beads[beadCount] = newBead;
	beadCount++;	
}

// Destructor for a sample.
//
sample::~sample(void)
{
	
}

// Adds a bead to the end of a sample. Uses a random number to
// select which direction to grow in
//
void sample::addBead()
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
void sample::addBeads(int amount)
{
	for(int i = 0; i < amount; i++)
	{
		addBead();
	}
}

// Returns the next available bead location in the array of beads
//
int sample::getBeadCount()
{
	return beadCount;
}

// Returns the Squared end to end distance. Calculated by running
// the coordinate distance formula on the first and last beads
// in a sample.
//
double sample::getSquareEndToEndDistance()
{
	int x1 = beads[0]->getX();
	int y1 = beads[0]->getY();
	int x2 = beads[beadCount - 1]->getX();
	int y2 = beads[beadCount - 1]->getY();

	double distance = ((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1));

	return sqrt(distance);
}

double sample::getXCM()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += beads[i]->getX();
	}

	sum = sum/beadCount;

	return sum;
}

double sample::getYCM()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += beads[i]->getY();
	}

	sum = sum/beadCount;

	return sum;
}