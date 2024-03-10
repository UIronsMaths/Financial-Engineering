#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include <iomanip>

class testing_hist;

class histogram {
	friend class testing_hist;

public:
	histogram(const double& minval, const double& maxval, const int& bins);
	void add(const double& x);
	std::vector<std::pair<double, int>> getResults() const;
	void writeResultsToStream(const bool& writeToConsole, const std::string& filename = "");

private:
	const double m_xmin;
	const double m_xmax;
	const int m_bins;
	int m_overflow;
	int m_underflow;
	std::vector<int> m_histogram;

	const double m_interval;
};