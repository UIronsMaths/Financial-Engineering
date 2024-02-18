#include"numericalIntegration.h"

numericalIntegration::numericalIntegration(double lowerLim, double upperLim, int intervals)
	:m_LL(lowerLim), m_UL(upperLim), m_num(intervals)
{}

double numericalIntegration::trapezium(std::function<double(double)> pdf, std::function<double(double)> payoff) {
	double h = (m_UL - m_LL) / m_num;
	double res = 0.5 * (pdf(m_LL) * payoff(m_LL)) + 0.5 * (pdf(m_UL) * payoff(m_UL));
	for (int i = 1; i < m_num; ++i) {
		double x_i = m_LL + i * h;
		res += (pdf(x_i)*payoff(x_i));
	}
	return res * h;
}