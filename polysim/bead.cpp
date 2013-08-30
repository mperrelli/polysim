///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  File:      bead.cpp                                            *//
//*  Author:    Matt Perrelli                                       *//
//*                                                                 *//
//*  This is the implementation code for the bead class. This       *//
//*  holds all the basic functionality for managing beads. Beads    *//
//*  are the building blocks of polymers.                           *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
#include "bead.h"

// Constructor for a bead. A bead always needs a set of coordinates.
//
bead::bead(int x, int y)
{
	this->x = x;
	this->y = y;
}

// Destructor for a bead.
//
bead::~bead(void)
{
}

// Returns the y-coordinate
//
int bead::getY()
{
	return y;
}

// Returns the x-coordinate
//
int bead::getX()
{
	return x;
}
