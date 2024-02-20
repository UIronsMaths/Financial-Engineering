#include"euroOption.h"

euroOption::euroOption(double strike, double expiry)
	:m_strike(strike), m_expiry(expiry)
{}

euroCall::euroCall(double strike, double expiry)
	:euroOption(strike, expiry)
{}

euroPut::euroPut(double strike, double expiry)
	:euroOption(strike, expiry)
{}

//
// Cumulative Normal Distribution (Numerical Approximation)
//
double euroOption::N(double x) {
	const double gamma = 0.2316419;
	const double a1 = 0.319381530;
	const double a2 = -0.356563782;
	const double a3 = 1.781477937;
	const double a4 = -1.821255978;
	const double a5 = 1.330274429;
	const double pi = 4.0 * atan(1.0);
	double k = 1.0 / (1.0 + gamma * x);

	if (x >= 0) {
		return 1.0 - ((((a5 * k + a4) * k + a3) * k + a2) * k + a1) * k * exp(-x * x / 2.0) / sqrt(2.0 * pi);
	}
	else {
		return 1.0 - N(-x);
	}
}

//
// Normal Probability Density
//
double euroOption::phi(double x) {
	const double pi = 4.0 * atan(1.0);
	return (1 / sqrt(2 * pi)) * exp(-pow(x, 2) / 2);
}

double euroOption::d_plus(double spot, double sigma, double r) {
	return (log(spot / m_strike) + (r + 0.5 * pow(sigma, 2)) * m_expiry) / (sigma * sqrt(m_expiry));
}

double euroOption::d_minus(double spot, double sigma, double r) {
	return d_plus(spot, sigma, r) - sigma * sqrt(m_expiry);
}

double euroCall::priceByBSFormula(double spot, double sigma, double r) {
	return (spot * N(d_plus(spot, sigma, r))) - (m_strike * exp(-r * m_expiry) * N(d_minus(spot, sigma, r)));
}

double euroPut::priceByBSFormula(double spot, double sigma, double r) {
	return (m_strike * exp(-r * m_expiry) * N(-d_minus(spot, sigma, r))) - (spot * N(-d_plus(spot, sigma, r)));
}

double euroCall::deltaByBSFormula(double spot, double sigma, double r) {
	return N(d_plus(spot, sigma, r));
}

double euroPut::deltaByBSFormula(double spot, double sigma, double r) {
	return N(d_plus(spot, sigma, r)) - 1;
}

double euroCall::gammaByBSFormula(double spot, double sigma, double r) {
	return phi(d_plus(spot, sigma, r)) / (spot * sigma * sqrt(m_expiry));
}

double euroPut::gammaByBSFormula(double spot, double sigma, double r) {
	return phi(d_plus(spot, sigma, r)) / (spot * sigma * sqrt(m_expiry));
}

double euroCall::thetaByBSFormula(double spot, double sigma, double r) {
	return -(spot * phi(d_plus(spot, sigma, r)) * sigma) / (2 * sqrt(m_expiry)) - (r * m_strike * exp(r * m_expiry) * N(d_minus(spot, sigma, r)));
}

double euroPut::thetaByBSFormula(double spot, double sigma, double r) {
	return -(spot * phi(d_plus(spot, sigma, r)) * sigma) / (2 * sqrt(m_expiry)) + (r * m_strike * exp(r * m_expiry) * N(-d_minus(spot, sigma, r)));
}