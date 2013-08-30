///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  File:      polymer.h                                           *//
//*  Author:    Matt Perrelli                                       *//
//*                                                                 *//
//*  Header file for the polymer class.                             *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
#pragma once
#include "bead.h"

const int MAX_BEADS = 100;

class polymer
{
private:
	bead* beads[MAX_BEADS];
	int beadCount;

public:
	// Constructor and destructor
	polymer(void);
	~polymer(void);

	// Functionality
	void addBead();
	void addBeads(int amount);

	// Gets and sets
	int getBeadCount();
	double getSquaredRadiusGyration();
};
