#include"pdf.h"

double pdf::lognormal(double x, double mean, double var) {
	if (x == 0) { return 0; }
	else{ return (1 / (x * sqrt(var) * sqrt(2 * pi))) * exp(-pow(log(x) - mean, 2) / (2 * var)); }
}

double pdf::normal(double x, double mean, double var) {
	return (1 / (var * sqrt(2 * pi))) * exp(-pow((x-mean)/var, 2) / 2);
}