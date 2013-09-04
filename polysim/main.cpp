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
#include "sample.h"
#include "bead.h"

const int MAX_SAMPLES = 20000;

int main()
{
	// Defines a list of pointers to instances of the sample class
	sample* samples[MAX_SAMPLES];

	// Variables
	int beadAmt, sampleAmt, pause;
	double sum = 0.0, avg = 0.0, avgx = 0.0, avgy = 0.0, sumxcm = 0.0, sumycm = 0.0;

	// User input
	cout << "Bead Amount: ";
	cin >> beadAmt;
	cout << "Sample Amount: ";
	cin >> sampleAmt;

	// Builds the samples
	for(int i = 0; i < sampleAmt; i++)
	{
		sample* p = new sample();
		samples[i] = p;
		samples[i]->addBeads(beadAmt- 1);
	}

	// Gets the average of various properties.
	for(int i = 0; i < sampleAmt; i++)
	{
		sum += samples[i]->getSquareEndToEndDistance();
		sumxcm += samples[i]->getXCM();
		sumycm += samples[i]->getYCM();
	}

	avg = sum / sampleAmt;
	avgx = sumxcm / sampleAmt;
	avgy = sumycm /sampleAmt;

	cout << "Average squared end to end distance: " << avg << "\n";
	cout << "Average center of x: " <<  avgx << "\n";
	cout << "Average center of y: " <<  avgy << "\n";

	// Reset sums for use again
	sum = 0.0;
	sumxcm = 0.0;
	sumycm = 0.0;

	// Gets the standard deviation of the mean
	for(int i = 0; i < sampleAmt; i++)
	{
		sum += (pow((samples[i]->getSquareEndToEndDistance() - avg), 2) / (beadAmt - 1));
		sumxcm += (pow((samples[i]->getXCM() - avgx), 2) / (beadAmt - 1));
		sumycm += (pow((samples[i]->getYCM() - avgy), 2) / (beadAmt - 1));
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