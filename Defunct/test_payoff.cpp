#include"test_payoff.h"

void testing_payoff::testPayoff() {
	testVanilla();
	std::cout << "All testcases passed." << std::endl;
}

void testing_payoff::testVanilla() {
	Call call(35, 30);
	assert(call.vanilla(50, 40) == 10);
	assert(call.vanilla() == 5);

	Put put(30, 35);
	assert(put.vanilla(40, 50) == 10);
	assert(put.vanilla() == 5);
}