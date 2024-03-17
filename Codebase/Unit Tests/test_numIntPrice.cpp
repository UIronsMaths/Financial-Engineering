#include"test_numIntPrice.h"

void testing_numIntPrice::testNumIntPrice() {
	testTrapeziumPrice();
	std::cout << "All Testcases Passed." << std::endl;
}

void testing_numIntPrice::testTrapeziumPrice() {

	//
	// Test Case 1: Correctness test.
	// 
	// K=102, T=0.75, S=100, vol=0.25, r=0.06
	// Price: 9.815 (Call), 7.326 (Put)
	//
	vanillaEuroCall call(102, 0.75);
	vanillaEuroPut put(102, 0.75);
	numInt test;
	assert(abs(test.priceByNumericalInt(&call, 100, 0.25, 0.06, 200) - 9.815) < 0.05);
	assert(abs(test.priceByNumericalInt(&put, 100, 0.25, 0.06, 200) - 7.326) < 0.05);
}