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

// Prototypes
void outputHistogramData(int bins, int sampleAmt, sample* s[]);

// Constants
const int MAX_SAMPLES = 20000;

///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  Function:  Main                                                *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
//// Variables ////////////////////////////////////////////////////////
//                                                                   //
//  samples: The array that holds pointers to sample objects         //
//                                                                   //
//  outputFile: output datafile stream                               //
//                                                                   //
//  beadAmt: Bead amount                                             //
//                                                                   //
//  sampleAmt: sample amount                                         //
//                                                                   //
//  sum,sum2,sum3,sum4: temporary variables                          //
//                                                                   //
///////////////////////////////////////////////////////////////////////
int main()
{
	// Defines a list of pointers to instances of the sample class
	sample* samples[MAX_SAMPLES];

	// Output file stream
	ofstream outputFile;

	// Variables
	int beadAmt, sampleAmt, pause;

	// Temporary variables
	double sum = 0.0, sum2 = 0.0, sum3 = 0.0, sum4 = 0.0;

	// final avg vars
	double avgSquareEndToEndDistance = 0.0,
		   avgXCM = 0.0,
		   avgYCM = 0.0,
		   avgLamda1 = 0.0,
		   avgLamda1Sq = 0.0,
		   avgLamda2 = 0.0,
		   avgLamda2Sq = 0.0,
		   avgAsphericity = 0.0,
		   avgAsphericitySq = 0.0,
		   avgRadiusOfGyration = 0.0,
		   avgRadiusOfGyrationSq = 0.0;

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
		sum3 += samples[i]->getXCM();
		sum4 += samples[i]->getYCM();
	}

	avgSquareEndToEndDistance = sum / sampleAmt;
	avgXCM = sum3 / sampleAmt;
	avgYCM = sum4 / sampleAmt;

	cout << "Average squared end to end distance: " << avgSquareEndToEndDistance << "\n";
	cout << "Average center of x: " <<  avgXCM << "\n";
	cout << "Average center of y: " <<  avgYCM << "\n";

	// Reset sums for use again
	sum = 0.0;
	sum3 = 0.0;
	sum4 = 0.0;

	// Gets the standard deviation of the mean
	for(int i = 0; i < sampleAmt; i++)
	{
		sum += (pow((samples[i]->getSquareEndToEndDistance() - avgSquareEndToEndDistance), 2) / (beadAmt - 1));
		sum3 += (pow((samples[i]->getXCM() - avgXCM), 2) / (beadAmt - 1));
		sum4 += (pow((samples[i]->getYCM() - avgYCM), 2) / (beadAmt - 1));
	}

	sdSquareEndToEndDistance = sqrt(sum);
	sdXCM = sqrt(sum3);
	sdYCM = sqrt(sum4);

	// Reset sums for use again
	sum = 0.0;
	sum2 = 0.0;
	sum3 = 0.0;
	sum4 = 0.0;

	cout << "Standard deviation of mean of squared end to end distance: " << sdSquareEndToEndDistance << "\n";
	cout << "Standard deviation of mean of center of x: " <<  sdXCM << "\n";
	cout << "Standard deviation of mean of center of y: " <<  sdYCM << "\n";

	// Gets average lamda1 and lamda2
	for(int i = 0; i < sampleAmt; i++)
	{
		sum += samples[i]->getLamda1();
		sum2 += pow(samples[i]->getLamda1(), 2.0);
		sum3 += samples[i]->getLamda2();
		sum4 += pow(samples[i]->getLamda2(), 2.0);
	}

	avgLamda1 = sum / sampleAmt;
	avgLamda1Sq = sum2 / sampleAmt;
	avgLamda2 = sum3 / sampleAmt;
	avgLamda2Sq = sum4 / sampleAmt;

	// Standard deviation of lamda1 and lamda2
	sdLamda1 = sqrt((avgLamda1Sq - avgLamda1 * avgLamda1) / (sampleAmt - 1));
	sdLamda2 = sqrt((avgLamda2Sq - avgLamda2 * avgLamda2) / (sampleAmt - 1));

	// Reset sums for use again
	sum = 0.0;
	sum2 = 0.0;
	sum3 = 0.0;
	sum4 = 0.0;

	// gets average asphoricity and radius of gyration
	for(int i = 0; i < sampleAmt; i++)
	{
		sum += samples[i]->getAsphericity();
		sum2 += pow(samples[i]->getAsphericity(), 2.0);
		sum3 += samples[i]->getRadiusofGyration();
		sum4 += pow(samples[i]->getRadiusofGyration(), 2.0);
	}

	avgAsphericitySq = sum2 / sampleAmt;
	avgAsphericity = sum / sampleAmt;
	avgRadiusOfGyrationSq = sum4 / sampleAmt;
	avgRadiusOfGyration = sum3 / sampleAmt;

	// Gets the standard deviation of the mean of asphericity and radius of gyration
	sdAsphericity = sqrt((avgAsphericitySq - avgAsphericity * avgAsphericity) / (sampleAmt - 1));
	sdRadiusOfGyration = sqrt((avgRadiusOfGyrationSq - avgRadiusOfGyration * avgRadiusOfGyration) / (sampleAmt - 1));

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

	outputHistogramData(20, sampleAmt, samples);

	// Wait
	cin >> pause;

	return 0;
}

///////////////////////////////////////////////////////////////////////
//*                                                                 *//
//*  Function:  outputHistogramData                                 *//
//*                                                                 *//
//*  Description:  Outputs a datafile for construction a histogram. *//
//*                                                                 *//
///////////////////////////////////////////////////////////////////////
//// Variables ////////////////////////////////////////////////////////
//                                                                   //
//  MAX_BINS: max amount of bins                                     //
//                                                                   //
//  binSize: bin size                                                //
//                                                                   //
//  temp: temporary variable, hold asphericity                       //
//                                                                   //
//  histInfoFile: output file stream                                 //
//                                                                   //
//  range: array that holds the upper bounds for each bin            //
//                                                                   //
//  count: array that holds the count for each bin                   //
//                                                                   //
///////////////////////////////////////////////////////////////////////
void outputHistogramData(int bins, int sampleAmt, sample* s[])
{
	const int MAX_BINS = 35;
	double binSize = 1.0 / bins;
	double temp;

	cout << binSize;

	// Output file stream
	ofstream histInfoFile;

	double range[MAX_BINS];
	int count[MAX_BINS];

	// Initialize arrays
	for(int i = 1; i <= bins; i++)
	{
		count[i - 1] = 0;
		range[i - 1] = (double)i * binSize;
	}

	// Build histogram data
	for(int i = 0; i < sampleAmt; i++)
	{
		temp = s[i]->getAsphericity();

		for(int j = 0; j < bins; j++)
		{
			if(temp <= range[j])
			{
				count[j]++;
				break;
			}
		}
	}

	// Build output
	histInfoFile.open("histogramInfo.txt");

	if(histInfoFile.fail())
	{
		cout << "Failed to open histogram file.\n";
		exit(1);
	}

	histInfoFile << "Bin\tFrequency\n";

	for(int i = 0; i < bins; i++)
	{
		histInfoFile << range[i] << "\t" << count[i] << endl;
	}

	histInfoFile.close();
}