#include"priceByNumInt.h"

double numInt::priceByNumericalInt(const option* opt, const double& spot, const double& vol, const double& r, const int& steps) const {
	const double mean = log(spot) + ((r - (0.5 * pow(vol, 2))) * opt->m_T);
	const double var = pow(vol * sqrt(opt->m_T), 2);
	const double upperLim = 5 * spot;

	numericalIntegration numInt;
	pdf pf;

	double res = numInt.trapezium(
		[opt, &pf, &mean, &var, &upperLim](const double& x) -> double {return pf.lognormal(x, mean, var) * opt->payoff(x); }
	, 0.0, upperLim, steps);

	res *= exp(-r * opt->m_T);
	return res;
}