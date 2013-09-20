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


// Constructor for a sample. When a sample is made it is
// automatically given an initial bead at coordinates 0,0
//
sample::sample(void)
{
	beadCount = 0;
	beadsX[beadCount] = 0;
	beadsY[beadCount] = 0;
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
	int x = beadsX[beadCount - 1];
	int y = beadsY[beadCount - 1];

	int growDirection = rand() % 4 + 1;

	switch(growDirection)
	{
	case 1:
		// Grow North
		y = y + 1;
		break;

	case 2:
		// Grow South
		y = y - 1;
		break;

	case 3:
		// Grow East
		x = x + 1;
		break;

	case 4:
		// Grow West
		x = x - 1;
		break;

	default:;

	}

	beadsX[beadCount] = x;
	beadsY[beadCount] = y;
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

	runCalculations();
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
	int x1 = beadsX[0];
	int y1 = beadsY[0];
	int x2 = beadsX[beadCount - 1];
	int y2 = beadsY[beadCount - 1];

	double distance = ((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1));

	return sqrt(distance);
}

// Returns average X coordinate accross all beads
// Shows us the X coordinate for the center of mass
// of our sample.
//
double sample::calculateXCM()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += beadsX[i];
	}

	sum = sum / beadCount;

	return sum;
}

// Returns average Y coordinate accross all beads
// Shows us the Y coordinate for the center of mass
// of our sample.
//
double sample::calculateYCM()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += beadsY[i];
	}

	sum = sum / beadCount;

	return sum;
}

// Returns the tensor for matrix position 1,1
//
double sample::calculateTensor11()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += pow((beadsX[i] - XCM), 2.0);
	}

	sum = sum / beadCount;

	return sum;
}

// Returns the tensor for matrix position 1,2
// Same as Tensor21
//
double sample::calculateTensor12()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += ((beadsX[i] - XCM) * (beadsY[i] - YCM));
	}

	sum = sum / beadCount;

	return sum;
}

// Returns the tensor for matrix position 2,2
//
double sample::calculateTensor22()
{
	double sum = 0.0;

	for(int i = 0; i < beadCount; i++)
	{
		sum += pow((beadsY[i] - YCM), 2.0);
	}

	sum = sum / beadCount;

	return sum;
}

// Returns Lamda1 which is the distance from the center of mass to the encompassing
// circle on the x-axis around the sample
//
double sample::calculateLamda1()
{
	double a = tensor11, b = tensor12, c = tensor22, lamda, factor;

	factor = (1.0 / 2) * sqrt((a*a) - (2 * a * c) + (c * c) + ((4 * (b * b))));

	lamda = ((a + c) / 2) + factor;

	return lamda;
}

// Returns Lamda2 which is the distance from the center of mass to the encompassing
// circle on the y-axis around the sample
//
double sample::calculateLamda2()
{
	double a = tensor11, b = tensor12, c = tensor22, lamda, factor;

	factor = (1.0 / 2) * sqrt((a*a) - (2 * a * c) + (c * c) + ((4 * (b * b))));

	lamda = ((a + c) / 2) - factor;

	return lamda;
}

// Returns the Asphericity which is the measure of how round a polymer is.
//
double sample::calculateAsphericity()
{
	double asphericity;

	asphericity = pow((lamda2 - lamda1), 2.0) / pow((lamda2 + lamda1), 2.0);

	return asphericity;
}

double sample::calculateRadiusofGyration()
{
	double rog;

	rog = lamda2 + lamda1;

	return rog;
}

// Runs all the necessary calculations on the sample and stores them.
//
void sample::runCalculations()
{
	XCM = calculateXCM();
	YCM = calculateYCM();
	tensor11 = calculateTensor11();
	tensor12 = calculateTensor12();
	tensor22 = calculateTensor22();
	lamda1 = calculateLamda1();
	lamda2 = calculateLamda2();
	asphericity = calculateAsphericity();
	radiusofGyration = calculateRadiusofGyration();
}

// Below this point are all get functions

double sample::getXCM()
{
	return XCM;
}

double sample::getYCM()
{
	return YCM;
}

double sample::getTensor11()
{
	return tensor11;
}

double sample::getTensor12()
{
	return tensor12;
}

double sample::getTensor22()
{
	return tensor22;
}

double sample::getLamda1()
{
	return lamda1;
}

double sample::getLamda2()
{
	return lamda2;
}
double sample::getAsphericity()
{
	return asphericity;
}

double sample::getRadiusofGyration()
{
	return radiusofGyration;
}