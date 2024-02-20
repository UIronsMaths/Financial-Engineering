#include"test_linearInterpolation.h"
#include<cassert>

void testing_linInt::testAdd() {

	//
	// Test case: Adding duplicate x-values.
	//
	linInterpolation test1;
	test1.add(2, 3);
	test1.add(2, 4);
	test1.add(4, 5);
	assert(test1.m_points.at(2) == 4);

	//
	// Test case: Correct interpolation range.
	// 
	linInterpolation test2;
	test2.add(2, 4);
	test2.add(4, 5);
	assert(test2.m_maxX == 4 && test2.m_minX == 2);
}
void testing_linInt::testValue() {

	//
	// Test case: correct interpolation value.
	//
	linInterpolation test1;
	test1.add(2, 4);
	test1.add(4, 5);
	assert(test1.value(2) == 4 && test1.value(3) == 4.5 && test1.value(3.5) == 4.75 && test1.value(4) == 5);

	//
	// Test case: attempted extrapolation.
	//
	linInterpolation test2;
	test2.add(2, 4);
	test2.add(4, 5);
	try {
		test2.value(5);
		assert(false);
	}
	catch (const std::runtime_error& e) {
		assert(true);
	}

	//
	// Test case: too few data points.
	//
	linInterpolation test3;
	test3.add(2, 3);
	try {
		test3.value(2);
		assert(false);
	}
	catch (const std::runtime_error& e) {
		assert(true);
	}
}
void testing_linInt::testLinInt() {
	testAdd();
	testValue();
	std::cout << "All testcases passed." << std::endl;
}