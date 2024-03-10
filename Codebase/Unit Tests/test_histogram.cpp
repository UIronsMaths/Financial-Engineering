#include"test_histogram.h"
#include<cassert>

void testing_hist::testAdd() {
	//
	// Edge case: x == m_xmax. Without handling will count as an overflow.
	//
	histogram test1(2, 4, 3);
	test1.add(2);
	test1.add(4);
	assert(test1.m_underflow == 0);
	assert(test1.m_histogram.at(0) == 1);
	assert(test1.m_histogram.at(1) == 0);
	assert(test1.m_histogram.at(2) == 1);
	assert(test1.m_overflow == 0);

	//
	// Test Case: Adding negative numbers.
	//
	histogram test2(-10, 10, 20);
	test2.add(-10);
	test2.add(10);
	test2.add(0);
	assert(test2.m_histogram.at(0) == 1);
	assert(test2.m_histogram.at(19) == 1);
	assert(test2.m_histogram.at(5) == 0);

	//
	// Test Case: Checking correct bin counts featuring double type data.
	//
	histogram test3(0, 10, 5);
	test3.add(2.5);
	test3.add(7.8);
	test3.add(12.0);
	test3.add(10.0);
	assert(test3.m_underflow == 0);
	assert(test3.m_histogram.at(0) == 0);
	assert(test3.m_histogram.at(1) == 1);
	assert(test3.m_histogram.at(2) == 0);
	assert(test3.m_histogram.at(3) == 1);
	assert(test3.m_histogram.at(4) == 1);
	assert(test3.m_overflow == 1);
	test3.add(10.01);
	assert(test3.m_overflow == 2);
	test3.add(-0.01);
	assert(test3.m_underflow == 1);

	//
	// Test Case: Checking that observations on the bin boundaries are correct.
	//
	histogram test4(0, 5, 2);
	test4.add(2.5);
	test4.add(3.5);
	test4.add(7.0);
	assert(test4.m_underflow == 0);
	assert(test4.m_histogram.at(0) == 1);
	assert(test4.m_histogram.at(1) == 1);
	assert(test4.m_overflow == 1);
}
void testing_hist::testGetRes() {
	//
	// Edge case: x == m_xmax. Without handling will count as an overflow.
	//
	histogram test1(2, 4, 3);
	test1.add(2);
	test1.add(4);
	std::vector<std::pair<double, int>> res1 = test1.getResults();
	assert(res1[0].first == 2);
	assert(res1[0].second == 0);
	assert(res1[1].first == 2 + test1.m_interval);
	assert(res1[1].second == 1);
	assert(res1[2].first == 2 + 2*test1.m_interval);
	assert(res1[2].second == 0);
	assert(res1[3].first == 4);
	assert(res1[3].second == 1);
	assert(res1[4].first == std::numeric_limits<double>::infinity());
	assert(res1[4].second == 0);

	//
	// Test Case: Checking correct bin counts featuring double type data.
	//
	histogram test2(0, 5, 2);
	test2.add(-0.01);
	test2.add(0.01);
	test2.add(2.5);
	test2.add(3.5);
	test2.add(5.0);
	test2.add(5.01);
	test2.add(7.0);
	std::vector<std::pair<double, int>> res2 = test2.getResults();
	assert(res2[0].first == 0);
	assert(res2[0].second == 1);
	assert(res2[1].first == 2.5);
	assert(res2[1].second == 2);
	assert(res2[2].first == 5);
	assert(res2[2].second == 2);
	assert(res2[3].first == std::numeric_limits<double>::infinity());
	assert(res2[3].second == 2);
}
void testing_hist::testHist() {
	testAdd();
	testGetRes();
	std::cout << "All testcases passed." << std::endl;
}