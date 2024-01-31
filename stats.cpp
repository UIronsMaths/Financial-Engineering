#include"stats.h"
#include<iostream>
#include<cmath>

stats1D::stats1D()
	:m_size(0), m_sum(0), m_sumsquared(0)
{}
void stats1D::add(double x)
{
	m_size++;

	m_sum += x;
	m_sumsquared += x * x;
}
double stats1D::mean()
{
	if (m_size != 0) {
		return m_sum / m_size;
	}
	else {
		throw std::runtime_error("Error in stats1D::mean(). Attempted division by zero.");
	}
}
double stats1D::var()
{
	if (m_size != 0) {
		return (m_sumsquared / m_size) - (mean() * mean());
	}
	else {
		throw std::runtime_error("Error in stats1D::var(). Attempted division by zero.");
	}
}
double stats1D::stDev()
{
	return std::sqrt(var());
}

stats2D::stats2D()
	:m_size(0), m_sum_x(0), m_sumsquared_x(0), m_sum_y(0), m_sumsquared_y(0), m_sum_xy(0)
{}
void stats2D::add(double x, double y)
{
	m_size++;
	m_sum_x += x;
	m_sumsquared_x += x * x;
	m_sum_y += y;
	m_sumsquared_y += y * y;
	m_sum_xy += x * y;
}
double stats2D::meanX()
{
	if (m_size != 0) {
		return m_sum_x / m_size;
	}
	else {
		throw std::runtime_error("Error in stats2D::meanX(). Attempted division by zero.");
	}
}
double stats2D::varX()
{
	if (m_size != 0) {
		return (m_sumsquared_x / m_size) - (meanX() * meanX());
	}
	else {
		throw std::runtime_error("Error in stats2D::varX(). Attempted division by zero.");
	}
}
double stats2D::stDevX()
{
	return std::sqrt(varX());
}
double stats2D::meanY()
{
	if (m_size != 0) {
		return m_sum_y / m_size;
	}
	else {
		throw std::runtime_error("Error in stats2D::meanY(). Attempted division by zero.");
	}
}
double stats2D::varY()
{
	if (m_size != 0) {
		return (m_sumsquared_y / m_size) - (meanY() * meanY());
	}
	else {
		throw std::runtime_error("Error in stats2D::varY(). Attempted division by zero.");
	}
}
double stats2D::stDevY()
{
	return std::sqrt(varY());
}
double stats2D::cov()
{
	if (m_size != 0) {
		return (m_sum_xy / m_size) - (meanX() * meanY());
	}
	else {
		throw std::runtime_error("Error in stats2D::cov(). Attempted division by zero.");
	}
}
double stats2D::corr()
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
double stats2D::lineargradient()
{
	if (varX() != 0) {
		return cov() / varX();
	}
	else {
		throw std::runtime_error("Error in stats2D::lineargradient(). Attempted division by zero.");
	}
}
double stats2D::linearintercept()
{
	if (varX() != 0) {
		return meanY() - (lineargradient() * meanX());
	}
	else {
		throw std::runtime_error("Error in stats2D::linearintercept(). No Y-intercept term exists when X has no variability.");
	}
}

NormalRandomGenerator::NormalRandomGenerator()
	:m_U1(double(rand())/double(RAND_MAX)), m_U2(double(rand()) / double(RAND_MAX))
{}

double NormalRandomGenerator::boxMuller() 
{
	double m_U1 = double(rand()) / double(RAND_MAX);
	double m_U2 = double(rand()) / double(RAND_MAX);
	double Z1 = std::sqrt(-2 * log(m_U1)) * std::cos(2 * pi * m_U2);
	//double Z2 = std::sqrt(-2 * log(m_U1)) * std::sin(2 * pi * m_U2);

	//
	// The 21278th standards normal variable generated is generated as Inf. 
	// While standard normal variables are allowed extreme values, this presents an edge case.
	// We need to clip the generated values to a reasonable set of values, say [-10,10].
	//
	return (Z1 > -10 && Z1 < 10) ? Z1 : 0;
}

double NormalRandomGenerator::generate() 
{
	return boxMuller();
}