#pragma once
#include"finiteDifference.h"

class fdm {
	friend class testing_fdmPrice;
public:
	double priceByExplicitFDM(const option* opt, const double& spot, const double& vol, const double& r, const int& tsteps, const int& ssteps, const double& smin, const double& smax) const;
};