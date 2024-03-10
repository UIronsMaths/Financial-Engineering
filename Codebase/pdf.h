#pragma once
#include<cmath>

class pdf {
	friend class testing_pdf;
public:
	double lognormal(const double& x, const double& mu, const double& sigma) const;
	double normal(const double& x, const double& mean, const double& var) const;
	double exponential(const double& x, const double& lambda) const;
	double cauchy(const double& x, const double& location, const double& scale) const;
	double students(const double& x, const double& v) const;
	double weibull(const double& x, const double& k, const double& lambda) const;
	double pareto(const double& x, const double& alpha) const;
	double levy(const double& x, const double& location, const double& scale) const;
protected:
	const double pi = 4.0 * atan(1.0);
};