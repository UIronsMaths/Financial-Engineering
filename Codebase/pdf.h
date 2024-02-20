#pragma once
#include<cmath>

class pdf {
	friend class testing_pdf;
public:
	double lognormal(double x, double mean, double var);
	double normal(double x, double mean, double var);
private:
	const double pi = 4.0*atan(1.0);
};