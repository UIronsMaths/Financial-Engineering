#include<map>
#include<vector>
#include"histogram.h"

histogram::histogram(double minval, double maxval, int bins)
	:m_xmin(minval), m_xmax(maxval), m_bins(bins), m_interval((maxval-minval)/bins), m_underflow(0), m_overflow(0)
{
	for (int i = 0; i < bins; i++) {
		m_histogram[i] = 0;
	}
}

void histogram::add(double x) 
{
	int bin = int(floor(x-m_xmin / m_interval));
	m_histogram[bin]++;
}

void histogram::getResults()
{
	for (auto it = m_histogram.begin(); it != m_histogram.end(); it++) {
		std::cout << "Bin " << it->first << " values up to " << m_xmin + ((it->first + 1) * m_interval) << " has " << it->second << " occurrances." << std::endl;
	}
}