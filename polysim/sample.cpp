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

// Returns average X coordinate accross all beads
// Shows us the X coordinate for the center of mass
// of our sample.
//
double sample::getXCM()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += beads[i]->getX();
	}

	sum = sum / beadCount;

	return sum;
}

// Returns average Y coordinate accross all beads
// Shows us the Y coordinate for the center of mass
// of our sample.
//
double sample::getYCM()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += beads[i]->getY();
	}

	sum = sum / beadCount;

	return sum;
}

// Returns the tensor for matrix position 1,1
//
double sample::getTensor11()
{
	double XCM = getXCM();
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += beads[i]->getX() - XCM;
	}

	sum = sum / beadCount;

	return sum;
}

// Returns the tensor for matrix position 1,2
// Same as Tensor21
//
double sample::getTensor12()
{
	double XCM = getXCM();
	double YCM = getYCM();
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += ((beads[i]->getX() - XCM) * (beads[i]->getY() - YCM));
	}

	sum = sum / beadCount;

	return sum;
}

// Returns the tensor for matrix position 2,2
//
double sample::getTensor22()
{
	double YCM = getYCM();
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += beads[i]->getY() - YCM;
	}

	sum = sum / beadCount;

	return sum;
}

// Returns Lamda1 which is the distance from the center of mass to the encompassing
// circle on the x-axis around the sample
//
double sample::getLamda1()
{
	double a = getTensor11(), b = getTensor12(), c = getTensor22(), lamda, factor;

	factor = (1.0 / 2) * sqrt((a*a) - (2 * a * c) + (c * c) + ((4 * (b * b))));

	lamda = ((a + c) / 2) + factor;

	return lamda;
}

// Returns Lamda2 which is the distance from the center of mass to the encompassing
// circle on the y-axis around the sample
//
double sample::getLamda2()
{
	double a = getTensor11(), b = getTensor12(), c = getTensor22(), lamda, factor;

	factor = (1.0 / 2) * sqrt((a*a) - (2 * a * c) + (c * c) + ((4 * (b * b))));

	lamda = ((a + c) / 2) - factor;

	return lamda;
}
