#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include <iomanip>

class testing_hist;

class histogram {
	friend class testing_hist;

public:
	histogram(double minval, double maxval, int bins);
	void add(double x);
	std::vector<std::pair<double, int>> getResults();
	void writeResultsToStream(bool writeToConsole, const std::string& filename = "");

private:
	double m_xmin;
	double m_xmax;
	int m_bins;
	int m_overflow;
	int m_underflow;
	std::vector<int> m_histogram;

	double m_interval;
};