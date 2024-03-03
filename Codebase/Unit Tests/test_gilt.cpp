#include"test_gilt.h"

void testing_gilt::testGilt() {
	testCleanPrice();
	testYield();
	std::cout << "All testcases passed." << std::endl;
}

void testing_gilt::testCleanPrice() {

	//
	// Test Case 1: Correct output. (3 dp accuracy required)
	//
	date maturity(7, 9, 2039);
	double cpn = 4.25;
	gilt test1(cpn, maturity);
	date settlement(12, 12, 2013);
	double y = 0.0423;
	assert(test1.giltCleanPrice(settlement, y) - 101.704 < 0.001);
	y = 0.0361;
	assert(test1.giltCleanPrice(settlement, y) - 111.951 < 0.001);
}

void testing_gilt::testYield() {

	//
	// Test Case 1: Correct output. (4 dp accuracy required)
	//
	date maturity(7, 9, 2039);
	double cpn = 4.25;
	gilt test1(cpn, maturity);
	date settlement(12, 12, 2013);
	assert(test1.yield(settlement, 101.704) - 0.0423 < 0.0001);
	assert(test1.yield(settlement, 111.951) - 0.0361 < 0.0001);
}