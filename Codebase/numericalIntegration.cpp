#include"numericalIntegration.h"

numericalIntegration::numericalIntegration()
	:m_LL(0.0), m_UL(0.0), m_num(0.0)
{}
numericalIntegration::numericalIntegration(const double& lowerLim, const double& upperLim, const int& intervals)
	:m_LL(lowerLim), m_UL(upperLim), m_num(intervals)
{}
double numericalIntegration::trapezium(const std::function<double(double)>& integrand) {
	double h = (m_UL - m_LL) / m_num;
	double res = 0.5 * integrand(m_LL) + 0.5 * integrand(m_UL);
	for (int i = 1; i < m_num; ++i) {
		double x_i = m_LL + i * h;
		res += integrand(x_i);
	}
	return res * h;
}
double numericalIntegration::trapezium(const std::function<double(double)>& integrand, const double& lowerLim, const double& upperLim, const int& intervals) {
	double h = (upperLim - lowerLim) / intervals;
	double res = 0.5 * integrand(lowerLim) + 0.5 * integrand(upperLim);
	for (int i = 1; i < intervals; ++i) {
		double x_i = lowerLim + i * h;
		res += integrand(x_i);
	}
	return res * h;
}
double numericalIntegration::trapezium(const numInt_adapterFunction* f) {
	double h = (m_UL - m_LL) / m_num;
	double res = 0.5 * f->eval(m_LL) + 0.5 * f->eval(m_UL);
	for (int i = 1; i < m_num; ++i) {
		double x_i = m_LL + i * h;
		res += f->eval(x_i);
	}
	return res * h;
}
double numericalIntegration::trapezium(const numInt_adapterFunction* f, const double& lowerLim, const double& upperLim, const int& intervals) {
	double h = (upperLim - lowerLim) / intervals;
	double res = 0.5 * f->eval(lowerLim) + 0.5 * f->eval(upperLim);
	for (int i = 1; i < intervals; ++i) {
		double x_i = lowerLim + i * h;
		res += f->eval(x_i);
	}
	return res * h;
}