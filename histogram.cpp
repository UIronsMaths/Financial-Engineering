#include<vector>
#include<fstream>
#include <iomanip>
#include"histogram.h"

histogram::histogram(double minval, double maxval, int bins)
	:m_xmin(minval), m_xmax(maxval), m_bins(bins), m_interval((maxval-minval)/bins), m_histogram(m_bins), m_underflow(0), m_overflow(0)
{}

void histogram::add(double x) 
{
	int bin = static_cast<int>(floor((x-m_xmin) / m_interval));
	//
	// Edge case: x == m_xmax. Without handling will count as an overflow.
	//
	if (x == m_xmax) {
		m_histogram[m_bins - 1]++;
	}
	else if (bin < 0) {
		m_underflow++;
	}
	else if (bin >= m_bins) {
		m_overflow++;
	}
	else {
		double boundary = m_xmin + (bin) * m_interval;
		if (x == boundary && x != m_xmin) {
			m_histogram[bin - 1]++;
		}
		else {
			m_histogram[bin]++;
		}
	}
}

std::vector<std::pair<double, int>> histogram::getResults()
{
	std::vector<std::pair<double, int>> out;
	out.push_back({ m_xmin, m_underflow });
	for (int bin = 0; bin < m_bins; bin++) {
		double boundary = m_xmin + (bin + 1) * m_interval;
		out.push_back(std::make_pair(boundary, m_histogram[bin]));
	}
	out.push_back({ std::numeric_limits<double>::infinity(), m_overflow });
	return out;
}

void histogram::writeResultsToStream(bool writeToConsole, const std::string& filename) {

	std::ofstream fileStream;
	std::ostream& os = (writeToConsole || filename.empty()) ? std::cout : (fileStream.open(filename), fileStream);

	if (!os) {
		std::cerr << "Error opening output stream.\n";
		return;
	}

	// Set precision for floating-point values in the output
	os << std::fixed << std::setprecision(2);

	os << "Boundary,Count\n";
	std::vector<std::pair<double, int>> results = getResults();
	for (const auto& result : results) {
		os << result.first << "," << result.second << "\n";
	}

	if (!writeToConsole && !filename.empty()) {
		fileStream.close();
		std::cout << "Results written to '" << filename << "'\n";
	}
}
