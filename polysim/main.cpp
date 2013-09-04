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
#include <cstdlib>
#include <cmath>
using namespace std;
#include "polymer.h"
#include "bead.h"

const int MAX_POLYMERS = 20000;

int main()
{
	// Defines a list of pointers to instances of the polymer class
	polymer* polymers[MAX_POLYMERS];

	// Variables
	int beadAmt, polymerAmt, pause;
	double sum = 0.0, avg = 0.0, avgx = 0.0, avgy = 0.0, sumxcm = 0.0, sumycm = 0.0;

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

	// Gets the average of various properties.
	for(int i = 0; i < polymerAmt; i++)
	{
		sum += polymers[i]->getSquareEndToEndDistance();
		sumxcm += polymers[i]->getXCM();
		sumycm += polymers[i]->getYCM();
	}

	avg = sum / polymerAmt;
	avgx = sumxcm / polymerAmt;
	avgy = sumycm /polymerAmt;

	cout << "Average squared end to end distance: " << avg << "\n";
	cout << "Average center of x: " <<  avgx << "\n";
	cout << "Average center of y: " <<  avgy << "\n";

	// Reset sums for use again
	sum = 0.0;
	sumxcm = 0.0;
	sumycm = 0.0;

	// Gets the standard deviation of the mean
	for(int i = 0; i < polymerAmt; i++)
	{
		sum += (pow((polymers[i]->getSquareEndToEndDistance() - avg), 2) / (beadAmt - 1));
		sumxcm += (pow((polymers[i]->getXCM() - avgx), 2) / (beadAmt - 1));
		sumycm += (pow((polymers[i]->getYCM() - avgy), 2) / (beadAmt - 1));
	}

	avg = sqrt(sum);
	avgx = sqrt(sumxcm);
	avgy = sqrt(sumycm);

	cout << "Standard deviation of mean of squared end to end distance: " << avg << "\n";
	cout << "Standard deviation of mean of center of x: " <<  avgx << "\n";
	cout << "Standard deviation of mean of center of y: " <<  avgy << "\n";

	// Wait
	cin >> pause;

	return 0;
}