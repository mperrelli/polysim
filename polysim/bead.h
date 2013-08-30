///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  File:      bead.h                                              *//
//*  Author:    Matt Perrelli                                       *//
//*                                                                 *//
//*  Header file for the bead class.                                *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
#pragma once

class bead
{
private:
	int x, y;

public:
	// Constructor & destructor
	bead(int x, int y);
	~bead(void);

	// Gets and sets
	int getX();
	int getY();
};
