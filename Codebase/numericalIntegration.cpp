#include"numericalIntegration.h"

numericalIntegration::numericalIntegration()
	:m_LL(0.0), m_UL(0.0), m_num(0.0)
{}

numericalIntegration::numericalIntegration(double lowerLim, double upperLim, int intervals)
	:m_LL(lowerLim), m_UL(upperLim), m_num(intervals)
{}

double numericalIntegration::trapezium(std::function<double(double)> integrand) {
	double h = (m_UL - m_LL) / m_num;
	double res = 0.5 * integrand(m_LL) + 0.5 * integrand(m_UL);
	for (int i = 1; i < m_num; ++i) {
		double x_i = m_LL + i * h;
		res += integrand(x_i);
	}
	return res * h;
}

double numericalIntegration::trapezium(std::function<double(double)> integrand, double lowerLim, double upperLim, int intervals) {
	m_LL = lowerLim;
	m_UL = upperLim;
	m_num = intervals;
	double h = (m_UL - m_LL) / m_num;
	double res = 0.5 * integrand(m_LL) + 0.5 * integrand(m_UL);
	for (int i = 1; i < m_num; ++i) {
		double x_i = m_LL + i * h;
		res += integrand(x_i);
	}
	return res * h;
}