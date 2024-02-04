#pragma once
#include<iostream>

class testing_hist;

class histogram {
public:
	histogram(double minval, double maxval, int bins);
	void add(double x);
	void getResults();

private:
	double m_xmin;
	double m_xmax;
	int m_bins;
	int m_underflow;
	int m_overflow;
	std::map<int,int> m_histogram;

	double m_interval;
};