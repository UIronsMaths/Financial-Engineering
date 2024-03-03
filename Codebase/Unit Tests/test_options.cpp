#include"test_options.h"

void testing_options::testOptions() {
	testVanilla();
	testBarrier();
	std::cout << "All testcases passed." << std::endl;
}

void testing_options::testVanilla() {

	//
	// Test Case 1: Correct initialisation.
	//
	vanillaEuroCall test(102, 0.75);
	assert((test.m_K == 102) && (test.m_T == 0.75) && (test.m_type == test.Call) && (test.m_timeStruct == test.Eu));
	assert(test.pathDependancy() == false && test.earlyExercise() == false);

	//
	// Test Case 2: Correct generics outputs.
	// e.g. N(0) = 0.5
	//
	assert(test.option::N(0.0) - 0.5 < 0.001);

	//
	// Test Case 3: Correct Values given. (Euro Call)
	// K=102, T=0.75, S=100, vol=0.25, r=0.06
	// Price: 9.815
	// d_plus: 0.225
	// d_minus: 0.008
	// Delta: 0.589
	// Gamma: 0.018
	// Theta: -8.559
	// Vega: 33.689
	// Rho: 36.804
	// 
	// CRR Price:
	//
	assert(test.BSAnalyticalPrice(100, 0.25, 0.06) - 9.815 < 0.001 && test.deltaByBSFormula(100, 0.25, 0.06) - 0.589 < 0.001);
	assert(test.gammaByBSFormula(100, 0.25, 0.06) - 0.018 < 0.001 && test.thetaByBSFormula(100, 0.25, 0.06) + 8.559 < 0.001);
	assert(test.vanilla::d_plus(100, 0.25, 0.06) - 0.225 < 0.001 && test.vanilla::d_minus(100, 0.25, 0.06) - 0.008 < 0.001);
	assert(test.binomialPrice(100, 0.25, 0.06, 2) - 9.815 < 0.05);
	assert(test.trinomialPrice(100, 0.25, 0.06, 2, 2) - 9.815 < 0.05);

	//
	// Test Case 4: Correct Values given. (Euro Put)
	// K=102, T=0.75, S=100, vol=0.25, r=0.06
	// Price: 7.326
	// d_plus: 0.225
	// d_minus: 0.008
	// Delta: -0.411
	// Gamma: 0.018
	// Theta: -2.708
	// Vega: 33.689
	// Rho: -36.330
	//
	vanillaEuroPut test2(102, 0.75);
	assert(test2.BSAnalyticalPrice(100, 0.25, 0.06) - 7.326 < 0.001 && test2.deltaByBSFormula(100, 0.25, 0.06) + 0.411 < 0.001);
	assert(test2.gammaByBSFormula(100, 0.25, 0.06) - 0.018 < 0.001 && test2.thetaByBSFormula(100, 0.25, 0.06) + 2.708 < 0.001);
	assert(test2.vanilla::d_plus(100, 0.25, 0.06) - 0.225 < 0.001 && test2.vanilla::d_minus(100, 0.25, 0.06) - 0.008 < 0.001);
	assert(test2.binomialPrice(100, 0.25, 0.06, 2) - 7.326 < 0.05);
	assert(test2.trinomialPrice(100, 0.25, 0.06, 2, 0.25) - 7.326 < 0.05);
}

void testing_options::testBarrier() {

	//
	// Test Case 1: Correct initialisation.
	//
	UpAndOutEuroCall test1(100, 1, 130);
	assert((test1.m_K == 100) && (test1.m_T == 1) && test1.m_B == 130 && (test1.m_type == test1.Call) && (test1.m_timeStruct == test1.Eu));
	assert(test1.pathDependancy() == true && test1.earlyExercise() == false);

	//
	// Test Case 2: Correct Values given. (Up and Out Call)
	//
	assert(test1.BSAnalyticalPrice(98, 0.2, 0.05) - 3.2375 < 0.001);
	assert(test1.binomialPrice(98, 0.2, 0.05, 200) - 3.2375 < 0.05);
	assert(test1.trinomialPrice(98, 0.2, 0.05, 200, 2) - 3.2375 < 0.05);
}