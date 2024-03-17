#pragma once
#include"vanillaOptions.h"

class tree {
	friend class testing_treePrice;
public:
	double binomialPriceCRR(const option* opt, const double& spot, const double& vol, const double& r, const int& steps) const;
	double binomialPriceJR(const option* opt, const double& spot, const double& vol, const double& r, const int& steps) const;
	double trinomialPrice(const option* opt, const double& spot, const double& vol, const double& r, const int& steps, const double& lambda) const;
};