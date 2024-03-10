#include"test_numericalIntegration.h"

void testing_numericalIntegration::testNumInt() {
	testTrapezium();
	std::cout << "All testcases passed." << std::endl;
}
void testing_numericalIntegration::testTrapezium() {

	//
	// Test case 1: Correctness of output.
	// Integral over [0,1] of x^2 = 1/3
	//
	numericalIntegration test1;
	assert(test1.trapezium([](double x) {return pow(x, 2); }, 0.0, 1.0, 200) - (1 / 3.0) < 0.01);
	numericalIntegration test2(0.0,1.0,200);
	assert(test2.trapezium([](double x) {return pow(x, 2); }) - (1 / 3.0) < 0.01);
	class testFunction : public numInt_adapterFunction {
		virtual double eval(const double& x) const { return x * x; }
	};
	testFunction tf;
	assert(test1.trapezium(&tf, 0.0, 1.0, 200) - (1 / 3.0) < 0.01);
	assert(test2.trapezium(&tf) - (1 / 3.0) < 0.01);

	//
	// Test case 2: Correctness of output (options pricing).
	// Black Scholes price achieved (expected discounted payoff).
	// K=102, S=100, vol=0.25, r=0.06, T=0.75
	// Price: 9.81475
	//
	numericalIntegration test3;
	pdf df;
	vanillaEuroCall po(102, 0.75);
	double mean = log(100) + ((0.06 - (0.5 * pow(0.25, 2))) * 0.75);
	double var = pow(0.25 * sqrt(0.75), 2);
	double res = test3.trapezium(
		[&df, &po, &mean, &var](double x) -> double { return df.lognormal(x, mean, var) * po.payoff(x); }, 0.0, 1000.0, 100);
	res *= exp(-0.06 * 0.75);
	assert(res - po.BSAnalyticalPrice(100,0.25,0.06) < 0.01);

	class testFunction2 : public numInt_adapterFunction, public pdf, public vanillaEuroCall {
	public:
		testFunction2(const double& m, const double& v, const double& strike, const double& expiry) : m_mean(m), m_var(v), pdf(), vanillaEuroCall(strike, expiry) {};
		virtual double eval(const double& x) const { return pdf::lognormal(x, m_mean, m_var) * vanillaEuroCall::payoff(x); }
	private:
		double m_mean;
		double m_var;
	};
	testFunction2 tf2(mean, var, 102, 0.75);
	res = test3.trapezium(&tf2, 0.0, 1000.0, 100);
	res *= exp(-0.06 * 0.75);
	assert(res - po.BSAnalyticalPrice(100, 0.25, 0.06) < 0.01);
}