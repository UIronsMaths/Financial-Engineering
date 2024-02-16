#include"test_euroOption.h"
#include<cassert>
#include<iostream>

void testing_euroOption::testEuroOption() {
	testBase();
	testPricing();
	std::cout << "All testcases passed." << std::endl;
}

void testing_euroOption::testBase() {
	euroCall test1(102, 0.75);
	assert(test1.m_strike == 102 && test1.m_expiry == 0.75 && abs(test1.N(0) - 0.5) < 0.01);
}

void testing_euroOption::testPricing() {
	euroCall test1(102, 0.75);
	euroPut test2(102, 0.75);
	assert(abs(test1.priceByBSFormula(100, 0.25, 0.06) - 9.81) < 0.01 && abs(test2.priceByBSFormula(100, 0.25, 0.06) - 7.33) < 0.01);
	assert(abs(test1.deltaByBSFormula(100, 0.25, 0.06) - 0.588) < 0.01 && abs(test2.deltaByBSFormula(100,0.25,0.06) + 0.411) < 0.01);
	assert(abs(test1.gammaByBSFormula(100, 0.25, 0.06) - 0.018) < 0.01 && abs(test2.gammaByBSFormula(100, 0.25, 0.06) - 0.018) < 0.01);
	assert(abs(test1.thetaByBSFormula(100, 0.25, 0.06) + 8.83) < 0.01 && abs(test2.thetaByBSFormula(100, 0.25, 0.06) + 2.43) < 0.01);
}