#include"pdf.h"

double pdf::lognormal(const double& x, const double& mu, const double& sigma) const {
	if (x == 0) { return 0; }
	else{ return (1 / (x * sqrt(sigma) * sqrt(2 * pi))) * exp(-pow(log(x) - mu, 2) / (2 * sigma)); }
}

double pdf::normal(const double& x, const double& mean, const double& var) const {
	return (1 / (var * sqrt(2 * pi))) * exp(-pow((x-mean)/var, 2) / 2);
}