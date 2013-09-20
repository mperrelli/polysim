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

const int MAX_SAMPLES = 20000;

int main()
{
	// Defines a list of pointers to instances of the sample class
	sample* samples[MAX_SAMPLES];

	// Variables
	int beadAmt, sampleAmt, pause;

	// Temporary variables
	double sum = 0.0, avg = 0.0, avgx = 0.0, avgy = 0.0, sumxcm = 0.0, sumycm = 0.0;

	// final avg vars
	double avgSquareEndToEndDistance = 0.0,
		   avgXCM = 0.0,
		   avgYCM = 0.0,
		   avgLamda1 = 0.0,
		   avgLamda2 = 0.0,
		   avgAsphericity = 0.0,
		   avgRadiusOfGyration = 0.0;

	// final standard deviations
	double sdSquareEndToEndDistance = 0.0,
		   sdXCM = 0.0,
		   sdYCM = 0.0,
		   sdLamda1 = 0.0,
		   sdLamda2 = 0.0,
		   sdAsphericity = 0.0,
		   sdRadiusOfGyration = 0.0;


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
		samples[i]->addBeads(beadAmt - 1);
	}

	// Gets the average of various properties.
	for(int i = 0; i < sampleAmt; i++)
	{
		sum += samples[i]->getSquareEndToEndDistance();
		sumxcm += samples[i]->getXCM();
		sumycm += samples[i]->getYCM();
	}

	avgSquareEndToEndDistance = sum / sampleAmt;
	avgXCM = sumxcm / sampleAmt;
	avgYCM = sumycm / sampleAmt;

	cout << "Average squared end to end distance: " << avgSquareEndToEndDistance << "\n";
	cout << "Average center of x: " <<  avgXCM << "\n";
	cout << "Average center of y: " <<  avgYCM << "\n";

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

	sdSquareEndToEndDistance = sqrt(sum);
	sdXCM = sqrt(sumxcm);
	sdYCM = sqrt(sumycm);

	// Reset sums for use again
	sum = 0.0;
	sumxcm = 0.0;
	sumycm = 0.0;

	cout << "Standard deviation of mean of squared end to end distance: " << sdSquareEndToEndDistance << "\n";
	cout << "Standard deviation of mean of center of x: " <<  sdXCM << "\n";
	cout << "Standard deviation of mean of center of y: " <<  sdYCM << "\n";

	// Gets average lamda1 and lamda2
	for(int i = 0; i < sampleAmt; i++)
	{
		sum += samples[i]->getLamda1();
		sumxcm += samples[i]->getLamda2();
	}

	avgLamda1 = sum /sampleAmt;
	avgLamda2 = sumxcm / sampleAmt;

	cout << "Average Lamda1: " << avgLamda1 << "\n";
	cout << "Average Lamda2: " << avgLamda2 << "\n";

	// Reset sums for use again
	sum = 0.0;
	sumxcm = 0.0;
	sumycm = 0.0;

	// Gets the standard deviation of the mean of lamdas
	for(int i = 0; i < sampleAmt; i++)
	{
		sumxcm += (pow((samples[i]->getLamda1() - avg), 2) / (beadAmt - 1));
		sumycm += (pow((samples[i]->getLamda2() - avgx), 2) / (beadAmt - 1));
	}

	sdLamda1 = sqrt(sumxcm);
	sdLamda2 = sqrt(sumycm);

	cout << "Standard deviation of the average lamda1: " << sdLamda1 << "\n";
	cout << "Standard deviation of the average lamda2: " << sdLamda2 << "\n";

	// Reset sums for use again
	sum = 0.0;
	sumxcm = 0.0;
	sumycm = 0.0;

	// gets average asphoricity and radius of gyration
	for(int i = 0; i < sampleAmt; i++)
	{
		sum += samples[i]->getAsphericity();
		sumxcm += samples[i]->getRadiusofGyration();
	}

	avgAsphericity = sum / sampleAmt;
	avgRadiusOfGyration = sum / sampleAmt;

	cout << "Average Asphericity: " << avgAsphericity << "\n";
	cout << "Average Radius of Gyration: " << avgRadiusOfGyration << "\n";

	// Reset sums for use again
	sum = 0.0;
	sumxcm = 0.0;
	sumycm = 0.0;

	// Gets the standard deviation of the mean of asphericity and radius of gyration
	for(int i = 0; i < sampleAmt; i++)
	{
		sumxcm += (pow((samples[i]->getAsphericity() - avg), 2) / (beadAmt - 1));
		sumycm += (pow((samples[i]->getRadiusofGyration() - avgx), 2) / (beadAmt - 1));
	}

	sdAsphericity = sqrt(sumxcm);
	sdRadiusOfGyration = sqrt(sumycm);

	cout << "Standard deviation of the average asphericity: " << sdAsphericity << "\n";
	cout << "Standard deviation of the average radius of gyration: " << sdRadiusOfGyration << "\n";

	// Wait
	cin >> pause;

	return 0;
}