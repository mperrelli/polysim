///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  File:      sample.h                                            *//
//*  Author:    Matt Perrelli                                       *//
//*                                                                 *//
//*  Header file for the sample class.                              *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
#pragma once

const int MAX_BEADS = 10000;

class sample
{
private:
	int beadsX[MAX_BEADS];
	int beadsY[MAX_BEADS];

	int beadCount;

	double XCM, YCM, tensor11, tensor12, tensor22, lamda1, lamda2, 
		asphericity, radiusofGyration, squareEndToEndDist;

	void runCalculations();

	// Calculation functions
	double calculateSquareEndToEndDist();
	double calculateXCM();
	double calculateYCM();
	double calculateTensor11();
	double calculateTensor12();
	double calculateTensor22();
	double calculateLamda1();
	double calculateLamda2();
	double calculateAsphericity();
	double calculateRadiusofGyration();

public:
	// Constructor and destructor
	sample(void);
	~sample(void);

	// Functionality
	void addBead();
	void addBeads(int amount);

	// Gets and sets
	int getBeadCount();
	double getSquareEndToEndDist();
	double getXCM();
	double getYCM();
	double getTensor11();
	double getTensor12();
	double getTensor22();
	double getLamda1();
	double getLamda2();
	double getAsphericity();
	double getRadiusofGyration();
};
