#include"gilt.h"

double gilt::giltCleanPrice(date settlement, double ytm) const {
	int couponPeriods = m_maturity.daysDiff(settlement)*2/365; // Not every year has 365 days.
	double term1 = 0;
	for (int i = 0; i < couponPeriods; i++) {
		term1 += (m_coupon / 2.0) / pow(1 + (ytm / 2.0), i);
	}
	return term1 + (100 / pow(1 + (ytm / 2.0), couponPeriods));
}

double gilt::yield(date settlement, double price) const {
	gilt_rootFinding_adapterFunction ga(*this, settlement);
	findRoot fr;

	//
	// Thanks the the inverse relationship between price and yield, we need to target the reciprocal of price.
	//

	return fr.bisectionSolver(&ga, 1.0 / price, 0, 1, 1e-6);
}

double gilt_rootFinding_adapterFunction::eval(double x) const {

	//
	// Again, due to the inverse relationship between yields and prices, Our adapter class needs to return the reciprocal of price.
	//

	return 1.0 / m_g.giltCleanPrice(m_settlement, x);
}