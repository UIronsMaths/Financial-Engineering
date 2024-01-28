#include"test_stats.h"
#include"stats.h"
#include<cassert>
#include<iostream>
#include<cmath>

void testMean()
{
	//
	// Basic mean of 1, 2, 3
	//
	stats1D test1;
	for (int i = 1; i <= 3; i++) {
		test1.add(i);
	}
	assert(test1.mean() == 2);

	//
	// Mean of U(0,1) distribution
	//
	stats1D test2;
	for (int i = 0; i < 10000; i++) {
		test2.add(double(rand()) / double(RAND_MAX));
	}
	assert(std::abs(test2.mean() - 0.5) < 0.01);

	//
	// Basic mean of 1, 2, 3
	//
	stats2D test3;
	for (int i = 1; i <= 3; i++) {
		test3.add(i,i);
	}
	assert(test3.meanX() == 2);
	assert(test3.meanY() == 2);

	//
	// Mean of U(0,1)xU(0,1) distribution
	//
	stats2D test4;
	for (int i = 0; i < 10000; i++) {
		test4.add(double(rand()) / double(RAND_MAX), double(rand()) / double(RAND_MAX));
	}
	assert(std::abs(test4.meanX() - 0.5) < 0.01);
	assert(std::abs(test4.meanY() - 0.5) < 0.01);
}

void testVar()
{

}
void testStDev()
{

}
void testCov()
{

}
void testCorr()
{

}
void testLinGrad()
{

}
void testLinInt()
{

}