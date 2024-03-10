#pragma once
#include"../stats.h"

class testing_stats {
public:
	void test_stats() const;
private:
	void testMean() const;
	void testVar() const;
	void testStDev() const;
	void testCov() const;
	void testCorr() const;
	void testLinGrad() const;
	void testLinInt() const;
	void testGen() const;
};