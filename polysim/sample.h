///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  File:      sample.h                                            *//
//*  Author:    Matt Perrelli                                       *//
//*                                                                 *//
//*  Header file for the sample class.                              *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
#pragma once
#include "bead.h"

const int MAX_BEADS = 10000;

class sample
{
private:
	bead* beads[MAX_BEADS];
	int beadCount;

public:
	// Constructor and destructor
	sample(void);
	~sample(void);

	// Functionality
	void addBead();
	void addBeads(int amount);

	// Gets and sets
	int getBeadCount();
	double getSquareEndToEndDistance();
	double getXCM();
	double getYCM();
	double getTensor11();
	double getTensor12();
	double getTensor22();
	double getLamda1();
	double getLamda2();
};
