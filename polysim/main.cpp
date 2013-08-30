///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  PolySim                                                        *//
//*                                                                 *//
//*  Modeling and simulation of polymers in two dimensions.         *//
//*                                                                 *// 
//*  File:      main.cpp                                            *//
//*  Author:    Matt Perrelli                                       *//
//*                                                                 *//
//*  This is the main file that the program runs through. All input *//
//*  data is collected here and pushed to the appropriate manager.  *//
//*  Data is then output through this file.                         *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "polymer.h"
#include "bead.h"

const int MAX_POLYMERS = 20;

int main()
{
	// Defines a list of pointers to instances of the polymer class
	polymer* polymers[MAX_POLYMERS];

	// Variables
	int beadAmt, polymerAmt, pause;
	double sum = 0, avg = 0;

	// User input
	cout << "Bead Amount: ";
	cin >> beadAmt;
	cout << "Polymer Amt: ";
	cin >> polymerAmt;

	// Builds the polymers
	for(int i = 0; i < polymerAmt; i++)
	{
		polymer* p = new polymer();
		polymers[i] = p;
		polymers[i]->addBeads(beadAmt- 1);
	}

	// Gets the mean-square radius of gyration of the polymers.
	for(int i = 0; i < polymerAmt; i++)
	{
		sum += polymers[i]->getSquaredRadiusGyration();
	}

	avg = sum / polymerAmt;

	cout << avg;

	// Wait
	cin >> pause;

	return 0;
}