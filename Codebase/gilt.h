#pragma once
#include"date.h"
#include"rootFinding.h"

class gilt {
	//
	// This class assumes that coupons are paid semi-annually. This class represents UK government bonds (aka. gilts).
	// Gilts pay their coupons semi-annually.
	//
	friend class testing_gilt;
public:
	gilt(double couponRate, date maturity)
		:m_coupon(couponRate), m_maturity(maturity)
	{}
	double giltCleanPrice(date settlement, double ytm) const;
	double giltDirtyPrice();
	double yield(date settlement, double price) const;
private:
	const double m_coupon;
	const date m_maturity;
};

class gilt_rootFinding_adapterFunction : public findRoot_adapterFunction {
public:
	gilt_rootFinding_adapterFunction(const gilt g, date settlement)
		:m_g(g), m_settlement(settlement)
	{}
	virtual double eval(double x) const;
private:
	const gilt m_g;
	date m_settlement;
};