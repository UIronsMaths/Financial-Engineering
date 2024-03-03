#include"test_rootFinding.h"

void testing_rootFinding::testFindRoot() {
	testBisection();
	std::cout << "All testcases passed." << std::endl;
}

void testing_rootFinding::testBisection() {

	//
	// Test Case 1: Correctness test.
	// Root of x^2 = 2 on interval [0,2] is sqrt(2).
	//
	class testFunction : public findRoot_adapterFunction {
		virtual double eval(double x) const { return x * x; }
	};
	testFunction tf;
	findRoot test1;
	assert(test1.bisectionSolver(&tf, 1.414213562, 0, 2, 1e-6) - 1.414213 < 0.000001);
	assert(test1.bisectionSolver(&tf, -1.414213562, -2, 0, 1e-6) + 1.414213 < 0.000001);
}