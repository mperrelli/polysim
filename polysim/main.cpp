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
#include <fstream>
#include <iomanip>
using namespace std;
#include "sample.h"

const int MAX_SAMPLES = 20000;

int main()
{
	// Defines a list of pointers to instances of the sample class
	sample* samples[MAX_SAMPLES];

	// Output file stream
	ofstream outputFile;

	// Variables
	int beadAmt, sampleAmt, pause;

	// Temporary variables
	double sum = 0.0, sumxcm = 0.0, sumycm = 0.0;

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

	// Set format
	cout.setf(ios::fixed);

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
		sum += (pow((samples[i]->getSquareEndToEndDistance() - avgSquareEndToEndDistance), 2) / (beadAmt - 1));
		sumxcm += (pow((samples[i]->getXCM() - avgXCM), 2) / (beadAmt - 1));
		sumycm += (pow((samples[i]->getYCM() - avgYCM), 2) / (beadAmt - 1));
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
		sumxcm += (pow((samples[i]->getLamda1() - avgLamda1), 2) / (beadAmt * (beadAmt - 1)));
		sumycm += (pow((samples[i]->getLamda2() - avgLamda2), 2) / (beadAmt * (beadAmt - 1)));
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
	avgRadiusOfGyration = sumxcm / sampleAmt;

	cout << "Average Asphericity: " << avgAsphericity << "\n";
	cout << "Average Radius of Gyration: " << avgRadiusOfGyration << "\n";

	// Reset sums for use again
	sum = 0.0;
	sumxcm = 0.0;
	sumycm = 0.0;

	// Gets the standard deviation of the mean of asphericity and radius of gyration
	for(int i = 0; i < sampleAmt; i++)
	{
		sumxcm += (pow((samples[i]->getAsphericity() - avgAsphericity), 2) / (beadAmt * (beadAmt - 1)));
		sumycm += (pow((samples[i]->getRadiusofGyration() - avgRadiusOfGyration), 2) / (beadAmt * (beadAmt - 1)));
	}

	sdAsphericity = sqrt(sumxcm);
	sdRadiusOfGyration = sqrt(sumycm);

	cout << "Standard deviation of the average asphericity: " << sdAsphericity << "\n";
	cout << "Standard deviation of the average radius of gyration: " << sdRadiusOfGyration << "\n";

	// Build output
	outputFile.open("output.txt");

	if(outputFile.fail())
	{
		cout << "Failed to open output file.\n";
		exit(1);
	}

	cout << "\n\nQuantity" << setw(13) << "Average" << setw(27) << "Standard Deviation\n";
	cout << "-----------------------------------------------\n";
	cout << "Lamda1  " << setw(15) << setprecision(6) << avgLamda1 << setw(18) << setprecision(6) << sdLamda1 << endl;
	cout << "Lamda2  " << setw(15) << setprecision(6) << avgLamda2 << setw(18) << setprecision(6) << sdLamda2 << endl;
	cout << "s^2     " << setw(15) << setprecision(6) << avgRadiusOfGyration << setw(18) << setprecision(6) << sdRadiusOfGyration << endl;
	cout << "A       " << setw(15) << setprecision(6) << avgAsphericity << setw(18) << setprecision(6) << sdAsphericity << endl;

	outputFile << "Lamda1\tLamda2\ts^2\tA\n";

	for(int i = 0; i < sampleAmt; i++)
	{
		outputFile << samples[i]->getLamda1() << "\t" << samples[i]->getLamda2()
			<< "\t" << samples[i]->getRadiusofGyration() << "\t" << samples[i]->getAsphericity()
			<< endl;
	}

	outputFile.close();

	// Wait
	cin >> pause;

	return 0;
}