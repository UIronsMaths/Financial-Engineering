#pragma once
#include"vanillaOptions.h"
#include"pdf.h"
#include"numericalIntegration.h"

class numInt {
	friend class testing_numIntPrice;
public:
	double priceByNumericalInt(const option* opt, const double& spot, const double& vol, const double& r, const int& steps) const;
};