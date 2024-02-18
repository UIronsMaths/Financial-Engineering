#pragma once
#include<cmath>

class pdf {
	friend class testing_pdf;
public:
	double lognormal(double x, double mean, double var);
private:
	const double pi = 3.1415926535897932;
};