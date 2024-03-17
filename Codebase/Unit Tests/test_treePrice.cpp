#include"test_treePrice.h"

void testing_treePrice::testTree() {
	testCRR();
	testJR();
	testTri();
	std::cout << "All Testcases Passed." << std::endl;
}

void testing_treePrice::testCRR() {

	//
	// Test Case 1: Correctness test.
	// 
	// K=102, T=0.75, S=100, vol=0.25, r=0.06
	// Price: 9.815 (Call), 7.326 (Put)
	//
	vanillaEuroCall call(102, 0.75);
	vanillaEuroPut put(102, 0.75);
	tree test;
	assert(abs(test.binomialPriceCRR(&call, 100, 0.25, 0.06, 200) - 9.815) < 0.05);
	assert(abs(test.binomialPriceCRR(&put, 100, 0.25, 0.06, 200) - 7.326) < 0.05);
}

void testing_treePrice::testJR() {

	//
	// Test Case 1: Correctness test.
	// 
	// K=102, T=0.75, S=100, vol=0.25, r=0.06
	// Price: 9.815 (Call), 7.326 (Put)
	//
	vanillaEuroCall call(102, 0.75);
	vanillaEuroPut put(102, 0.75);
	tree test;
	assert(abs(test.binomialPriceJR(&call, 100, 0.25, 0.06, 200) - 9.815) < 0.05);
	assert(abs(test.binomialPriceJR(&put, 100, 0.25, 0.06, 200) - 7.326) < 0.05);
}

void testing_treePrice::testTri() {

	//
	// Test Case 1: Correctness test.
	// 
	// K=102, T=0.75, S=100, vol=0.25, r=0.06
	// Price: 9.815 (Call), 7.326 (Put)
	//
	vanillaEuroCall call(102, 0.75);
	vanillaEuroPut put(102, 0.75);
	tree test;
	assert(abs(test.trinomialPrice(&call, 100, 0.25, 0.06, 200, 2) - 9.815) < 0.05);
	assert(abs(test.trinomialPrice(&put, 100, 0.25, 0.06, 200, 2) - 7.326) < 0.05);
}