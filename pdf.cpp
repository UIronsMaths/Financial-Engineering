#include"pdf.h"

double pdf::lognormal(double x, double mean, double var) {
	if (x == 0) { return 0; }
	else{ return (1 / (x * sqrt(var) * sqrt(2 * pi))) * exp(-pow(log(x) - mean, 2) / (2 * var)); }
}