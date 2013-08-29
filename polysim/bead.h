#pragma once

class bead
{
private:
	int x, y;

public:
	bead(int x, int y);
	~bead(void);

	int getX();
	int getY();
};
