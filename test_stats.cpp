#include"test_stats.h"
#include"stats.h"
#include<cassert>
#include<iostream>
#include<cmath>

void testing_stats::testMean()
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

    //
    // Edge case: Empty dataset
    //
    stats1D test5;
    try {
        test5.mean();
        // The line above should throw an exception
        assert(false);
    }
    catch (const std::runtime_error& e) {
        // Expected exception
        assert(true);
    }

    //
    // Edge case: Empty dataset (2D)
    //
    stats2D test6;
    try {
        test6.meanX();
        // The line above should throw an exception
        assert(false);
    }
    catch (const std::runtime_error& e) {
        // Expected exception
        assert(true);
    }
    try {
        test6.meanY();
        // The line above should throw an exception
        assert(false);
    }
    catch (const std::runtime_error& e) {
        // Expected exception
        assert(true);
    }
}
void testing_stats::testVar()
{
    //
    // Basic variance of 1, 2, 3
    //
    stats1D test1;
    for (int i = 1; i <= 3; i++) {
        test1.add(i);
    }
    assert(std::abs(test1.var() - 0.66) < 0.01);

    //
    // Variance of U(0,1) distribution
    //
    stats1D test2;
    for (int i = 0; i < 10000; i++) {
        test2.add(double(rand()) / double(RAND_MAX));
    }
    assert(std::abs(test2.var() - 1.0 / 12) < 0.01);

    //
    // Basic variance of 1, 2, 3
    //
    stats2D test3;
    for (int i = 1; i <= 3; i++) {
        test3.add(i, i);
    }
    assert(std::abs(test3.varX() - 0.66) < 0.01);
    assert(std::abs(test3.varY() - 0.66) < 0.01);

    //
    // Variance of U(0,1)xU(0,1) distribution
    //
    stats2D test4;
    for (int i = 0; i < 10000; i++) {
        test4.add(double(rand()) / double(RAND_MAX), double(rand()) / double(RAND_MAX));
    }
    assert(std::abs(test4.varX() - 1.0 / 12) < 0.01);
    assert(std::abs(test4.varY() - 1.0 / 12) < 0.01);

    //
    // Edge case: Single element dataset
    //
    stats1D test5;
    test5.add(42);
    assert(test5.var() == 0);

    //
    // Edge case: Single element dataset (2D)
    //
    stats2D test6;
    test6.add(42, 42);
    assert(test6.varX() == 0);
    assert(test6.varY() == 0);
}
void testing_stats::testStDev()
{
    //
    // Basic standard deviation of 1, 2, 3
    //
    stats1D test1;
    for (int i = 1; i <= 3; i++) {
        test1.add(i);
    }
    assert(std::abs(test1.stDev() - std::sqrt(2.0/3)) < 0.01);

    //
    // Standard deviation of U(0,1) distribution
    //
    stats1D test2;
    for (int i = 0; i < 10000; i++) {
        test2.add(double(rand()) / double(RAND_MAX));
    }
    assert(std::abs(test2.stDev() - std::sqrt(1.0 / 12)) < 0.01);

    //
    // Basic standard deviation of 1, 2, 3
    //
    stats2D test3;
    for (int i = 1; i <= 3; i++) {
        test3.add(i, i);
    }
    assert(std::abs(test3.stDevX() - std::sqrt(2.0 / 3)) < 0.01);
    assert(std::abs(test3.stDevY() - std::sqrt(2.0 / 3)) < 0.01);

    //
    // Standard deviation of U(0,1)xU(0,1) distribution
    //
    stats2D test4;
    for (int i = 0; i < 10000; i++) {
        test4.add(double(rand()) / double(RAND_MAX), double(rand()) / double(RAND_MAX));
    }
    assert(std::abs(test4.stDevX() - std::sqrt(1.0 / 12)) < 0.01);
    assert(std::abs(test4.stDevY() - std::sqrt(1.0 / 12)) < 0.01);

    //
    // Edge case: Single element dataset
    //
    stats1D test5;
    test5.add(42);
    assert(test5.stDev() == 0);

    //
    // Edge case: Single element dataset (2D)
    //
    stats2D test6;
    test6.add(42, 42);
    assert(test6.stDevX() == 0);
    assert(test6.stDevY() == 0);
}
void testing_stats::testCov()
{
    //
    // Covariance of 1, 2, 3
    //
    stats2D test1;
    for (int i = 1; i <= 3; i++) {
        test1.add(i, i);
    }
    assert(std::abs(test1.cov() - 2.0 / 3) < 0.01);

    //
    // Covariance of U(0,1)xU(0,1) distribution
    //
    stats2D test2;
    for (int i = 0; i < 10000; i++) {
        test2.add(double(rand()) / double(RAND_MAX), double(rand()) / double(RAND_MAX));
    }
    assert(std::abs(test2.cov()) < 0.01);

    //
    // Edge case: Single element dataset
    //
    stats2D test3;
    test3.add(42, 42);
    assert(test3.cov() == 0);
}
void testing_stats::testCorr()
{
    //
    // Correlation of 1, 2, 3
    //
    stats2D test1;
    for (int i = 1; i <= 3; i++) {
        test1.add(i, i);
    }
    assert(std::abs(test1.corr() - 1) < 0.01);

    //
    // Correlation of U(0,1)xU(0,1) distribution
    //
    stats2D test2;
    for (int i = 0; i < 10000; i++) {
        test2.add(double(rand()) / double(RAND_MAX), double(rand()) / double(RAND_MAX));
    }
    assert(std::abs(test2.corr()) < 0.01);

    //
    // Edge case: Single element dataset
    //
    stats2D test3;
    test3.add(42, 42);
    try {
        test3.corr();
        // The line above should throw an exception
        assert(false);
    }
    catch (const std::runtime_error& e) {
        // Expected exception
        assert(true);
    }
}
void testing_stats::testLinGrad()
{
    //
    // Linear gradient of 1, 2, 3
    //
    stats2D test1;
    for (int i = 1; i <= 3; i++) {
        test1.add(i, i);
    }
    assert(test1.lineargradient() == 1);

    //
    // Linear gradient of U(0,1)xU(0,1) distribution
    //
    stats2D test2;
    for (int i = 0; i < 10000; i++) {
        test2.add(double(rand()) / double(RAND_MAX), double(rand()) / double(RAND_MAX));
    }
    assert(std::abs(test2.lineargradient()) < 0.01);

    //
    // Edge case: Zero variance in Y
    //
    stats2D test3;
    test3.add(1, 42);
    test3.add(2, 42);
    test3.add(3, 42);
    assert(test3.lineargradient() == 0);

    //
    // Edge case: Zero variance in X
    //
    stats2D test4;
    test4.add(1, 42);
    test4.add(1, 43);
    test4.add(1, 44);
    try {
        test4.lineargradient();
        // The line above should throw an exception
        assert(false);
    }
    catch (const std::runtime_error& e) {
        // Expected exception
        assert(true);
    }
}
void testing_stats::testLinInt()
{
    //
    // Linear intercept of 1, 2, 3
    //
    stats2D test1;
    for (int i = 1; i <= 3; i++) {
        test1.add(i, i);
    }
    assert(test1.linearintercept() == 0);

    //
    // Linear intercept of U(0,1)xU(0,1) distribution
    //
    stats2D test2;
    for (int i = 0; i < 10000; i++) {
        test2.add(double(rand()) / double(RAND_MAX), double(rand()) / double(RAND_MAX));
    }
    assert(std::abs(test2.linearintercept() - 0.5) < 0.01);

    //
    // Edge case: Zero variance in Y
    //
    stats2D test3;
    test3.add(1, 42);
    test3.add(2, 42);
    test3.add(3, 42);
    assert(test3.linearintercept() == 42);

    //
    // Edge case: Zero variance in X
    //
    stats2D test4;
    test4.add(1, 42);
    test4.add(1, 43);
    test4.add(1, 44);
    try {
        test4.linearintercept();
        // The line above should throw an exception
        assert(false);
    }
    catch (const std::runtime_error& e) {
        // Expected exception
        assert(true);
    }
}
void testing_stats::testGen() {
    NormalRandomGenerator testG1;
    stats1D testS1;
    for (int i = 0; i < 10000; i++) {
        testS1.add(testG1.generate());
    }
    assert(testS1.mean() < 0.01);
    assert(testS1.var() - 1 < 0.01);

    //
    // The 21278th standards normal variable generated is generated as Inf.
    //
    stats1D testS2;
    NormalRandomGenerator testG2;
    for (int i = 0; i < 21278; i++) {
        testS2.add(testG2.generate());
    }
    assert(testS1.mean() < 0.01);
}
void testing_stats::test_stats() {
    testMean();
    testVar();
    testStDev();
    testCov();
    testCorr();
    testLinGrad();
    testLinInt();
    testGen();
    std::cout << "All testcases passed." << std::endl;
}
