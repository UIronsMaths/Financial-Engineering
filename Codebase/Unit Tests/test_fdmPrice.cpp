#include"test_fdmPrice.h"

void testing_fdmPrice::testFDMPrice() {
	testVanilla();
	testBarrier();
	std::cout << "All Testcases Passed." << std::endl;
}

void testing_fdmPrice::testVanilla() {

	//
	// Test Case 1: Correctness test. Explicit Scheme.
	// 
	// Vanilla European
	// K = 100, S0 = 98, T = 1
	// vol = 0.2, r = 0.05
	// 
	// Correct Price: 
	// 9.21 (Call), 6.33 (Put)
	//
	vanillaEuroCall call(100, 1.0);
	fdm test1;
	assert(abs(test1.priceByExplicitFDM(&call, 98, 0.2, 0.05, 32'000, 800, 0, 300) - call.BSAnalyticalPrice(98, 0.2, 0.05)) < 0.01);
	vanillaEuroPut put(100, 1.0);
	assert(abs(test1.priceByExplicitFDM(&put, 98, 0.2, 0.05, 32'000, 800, 0, 300) - put.BSAnalyticalPrice(98, 0.2, 0.05)) < 0.01);

}

void testing_fdmPrice::testBarrier() {

	//
	// Test Case 1: Correctness test. Explicit Scheme.
	// 
	// Up And Out European Call
	// K = 100, S0 = 98, T = 1
	// vol = 0.2, r = 0.05
	// 
	// Correct Price:
	// 3.23
	//
	UpAndOutEuroCall uoc(100, 1.0, 130);
	fdm test1;
	assert(abs(test1.priceByExplicitFDM(&uoc, 98, 0.2, 0.05, 32'000, 800, 0, 130) - uoc.BSAnalyticalPrice(98, 0.2, 0.05)) < 0.01);

}