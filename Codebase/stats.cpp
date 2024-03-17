#include"stats.h"

void stats1D::add(const double& x)
{
	m_size++;

	m_sum += x;
	m_sumsquared += x * x;
}
double stats1D::mean() const
{
	if (m_size != 0) {
		return m_sum / m_size;
	}
	else {
		throw std::runtime_error("Error in stats1D::mean(). Attempted division by zero.");
	}
}
double stats1D::var() const
{
	if (m_size != 0) {
		return (m_sumsquared / m_size) - (mean() * mean());
	}
	else {
		throw std::runtime_error("Error in stats1D::var(). Attempted division by zero.");
	}
}
double stats1D::stDev() const
{
	return std::sqrt(var());
}
int stats1D::size() const { return m_size; }
void stats2D::add(const double& x, const double& y)
{
	m_size++;
	m_sum_x += x;
	m_sumsquared_x += x * x;
	m_sum_y += y;
	m_sumsquared_y += y * y;
	m_sum_xy += x * y;
}
double stats2D::meanX() const
{
	if (m_size != 0) {
		return m_sum_x / m_size;
	}
	else {
		throw std::runtime_error("Error in stats2D::meanX(). Attempted division by zero.");
	}
}
double stats2D::varX() const
{
	if (m_size != 0) {
		return (m_sumsquared_x / m_size) - (meanX() * meanX());
	}
	else {
		throw std::runtime_error("Error in stats2D::varX(). Attempted division by zero.");
	}
}
double stats2D::stDevX() const
{
	return std::sqrt(varX());
}
double stats2D::meanY() const
{
	if (m_size != 0) {
		return m_sum_y / m_size;
	}
	else {
		throw std::runtime_error("Error in stats2D::meanY(). Attempted division by zero.");
	}
}
double stats2D::varY() const
{
	if (m_size != 0) {
		return (m_sumsquared_y / m_size) - (meanY() * meanY());
	}
	else {
		throw std::runtime_error("Error in stats2D::varY(). Attempted division by zero.");
	}
}
double stats2D::stDevY() const
{
	return std::sqrt(varY());
}
double stats2D::cov() const
{
	if (m_size != 0) {
		return (m_sum_xy / m_size) - (meanX() * meanY());
	}
	else {
		throw std::runtime_error("Error in stats2D::cov(). Attempted division by zero.");
	}
}
double stats2D::corr() const
{
	if (varX() != 0 && varY() != 0 && m_size >= 2) {
		return cov() / (std::sqrt(varX() * varY()));
	}
	else if (varX() != 0 && varY() != 0 && m_size < 2) {
		throw std::runtime_error("Error in stats2D::corr(). Too few data points, correlation requires at least 2.");
	}
	else {
		throw std::runtime_error("Error in stats2D::corr(). Attempted division by zero.");
	}
}
double stats2D::lineargradient() const
{
	if (varX() != 0) {
		return cov() / varX();
	}
	else {
		throw std::runtime_error("Error in stats2D::lineargradient(). Attempted division by zero.");
	}
}
double stats2D::linearintercept() const
{
	if (varX() != 0) {
		return meanY() - (lineargradient() * meanX());
	}
	else {
		throw std::runtime_error("Error in stats2D::linearintercept(). No Y-intercept term exists when X has no variability.");
	}
}
int stats2D::size() const { return m_size; }
double NormalRandomGenerator::boxMuller()
{
	if (m_boolFlag) {
		m_boolFlag = false;
		return m_val;
	}
	else {
		m_boolFlag = true;
		double U1 = double(rand() + 0.5) / double(RAND_MAX + 1.0);
		double U2 = double(rand() + 0.5) / double(RAND_MAX + 1.0);
		m_val = std::sqrt(-2 * log(U1)) * std::cos(2 * pi * U2);
		return std::sqrt(-2 * log(U1)) * std::sin(2 * pi * U2);
	}
}
double NormalRandomGenerator::generate()
{
	return boxMuller();
}