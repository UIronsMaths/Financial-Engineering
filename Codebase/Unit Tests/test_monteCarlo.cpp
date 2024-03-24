#include"test_monteCarlo.h"

void testing_MC::testMC() {
	testMCint();
	testMCarea();
	testMCprice();
	std::cout << "All testcases Passed." << std::endl;
}
void testing_MC::testMCint() {

	//
	// Test Case 1: Correctness test.
	// Integral over [0,1] of x^2 is 1/3.
	//
	auto func1 = [](const double& x) { return x * x; };
	MonteCarlo mc;
	MonteCarloResult test1 = mc.monteCarloIntegration(func1, 0, 1, 100'000);
	assert(abs(test1.estimated_value - ((double)1 / 3)) < 0.01);

	//
	// Test Case 2: Correctness test.
	// Integral (using multidimensional MC) over [0,1] of (x^2) is 1/3.
	//
	auto func2 = [](const std::vector<double>& x) { return x[0] * x[0]; };
	std::pair<double, double> p = std::make_pair(0, 1);
	std::vector<std::pair<double, double>> limits;
	limits.push_back(p);
	MonteCarloResult test2 = mc.monteCarloIntegration(func2, limits, 100'000);
	assert(abs(test2.estimated_value - ((double)1 / 3)) < 0.01);

	//
	// Test Case 3: Correctness test.
	// Double Integral over [0,1]x[0,1] of (x^2)(y^2) is 1/9.
	//
	auto func3 = [](const std::vector<double>& x) { return x[0] * x[0] * x[1] * x[1]; };
	limits.push_back(p);
	MonteCarloResult test3 = mc.monteCarloIntegration(func3, limits, 100'000);
	assert(abs(test3.estimated_value - ((double)1 / 9)) < 0.01);
}
void testing_MC::testMCarea() {

	//
	// Test Case 1: Correctness test.
	// Area of unit circle approximates pi.
	//
	auto func1 = [](const double& x, const double& y) { return x * x + y * y <= 1; };
	MonteCarlo mc;
	MonteCarloResult test1 = mc.monteCarloArea(func1, -1, 1, -1, 1, 100'000);
	assert(abs(test1.estimated_value - pi) < 0.01);

	//
	// Test Case 2: Correctness test.
	// Area bounded by curve given by polar coordinates r=3-cos(8t) and 0<=t<=2pi is 19pi/2.
	//
	auto func2 = [](const double& x, const double& y) { return sqrt(x * x + y * y) <= (3 - cos(8 * std::atan(y / x))); };
	MonteCarloResult test2 = mc.monteCarloArea(func2, -4, 4, -4, 4, 1'000'000);
	assert(abs(test2.estimated_value - (19*pi/2)) < 0.01);

	//
	// Test Case 3: Correctness test.
	// Volume of a unit sphere is given by 4pi/3.
	//
	auto func3 = [](const std::vector<double>& x) {    
		double X = x[0] * x[0];
		double Y = x[1] * x[1];
		double Z = x[2] * x[2];
		return X + Y + Z <= 1; 
	};
	std::vector<std::pair<double, double>> limits;
	std::pair<double,double>p = std::make_pair(-1, 1);
	limits.push_back(p);
	limits.push_back(p);
	limits.push_back(p);
	MonteCarloResult test3 = mc.monteCarloArea(func3, limits, 1'000'000);
	assert(abs(test3.estimated_value - (4 * pi / 3)) < 0.01);
}
void testing_MC::testMCprice() {

	//
	// Test Case 1: Correct Values given. (Euro Call)
	// K=102, T=0.75, S=100, vol=0.25, r=0.06
	// Price: 9.815
	//
	vanillaEuroCall ec(102, 0.75);
	MonteCarlo mc;
	MonteCarloPricing test1 = mc.monteCarloPrice(&ec, 100, 0.25, 0.06, 100'000);
	assert(abs(test1.estimated_price - ec.BSAnalyticalPrice(100, 0.25, 0.06)) < 0.03);
	assert(abs(test1.estimated_delta - ec.deltaByBSFormula(100,0.25,0.06)) < 0.02);
	assert(abs(test1.estimated_delta - ec.gammaByBSFormula(100, 0.25, 0.06)) < 0.01);
	

	//
	// Test Case 2: Correct Values given. (Euro Put)
	// K=102, T=0.75, S=100, vol=0.25, r=0.06
	// Price: 7.326
	//
	vanillaEuroPut ep(102, 0.75);
	MonteCarloPricing test2 = mc.monteCarloPrice(&ep, 100, 0.25, 0.06, 100'000);
	assert(abs(test2.estimated_price - ep.BSAnalyticalPrice(100, 0.25, 0.06)) < 0.03);
	assert(abs(test2.estimated_delta - ep.deltaByBSFormula(100, 0.25, 0.06)) < 0.02);
	assert(abs(test2.estimated_delta - ep.gammaByBSFormula(100, 0.25, 0.06)) < 0.01);

	//
	// Test Case 3: Approximately Correct Values given (Range Accrual)
	// K=102, T=1, S0=100, sigma=0.25, r=0.06, payout=1'000'000
	// lower bound = 100, upper bound =110
	// Exact values are
	// Price: 254,582
	// Delta: -923
	// Gamma: -2332
	// Testing will check if within 2 standard deviations of the exact values.
	//
	rangeAccrual ra(1'000'000, 100, 110, 1);
	MonteCarloPricing test3 = mc.monteCarloPrice(&ra, 100, 0.25, 0.06, 450'000);
	assert(abs(test3.estimated_price - 254583) < 2 * test3.standard_error_price);
	assert(abs(test3.estimated_delta + 923) < 2 * test3.standard_error_delta);
	assert(abs(test3.estimated_gamma + 2332) < 2 * test3.standard_error_gamma);
}