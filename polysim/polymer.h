#pragma once
#include "bead.h"

const int MAX_BEADS = 20;

class polymer
{
private:
	bead* beads[MAX_BEADS];
	int beadCount;

public:
	polymer(void);
	~polymer(void);

	void addBead();

	int getBeadCount();
};
