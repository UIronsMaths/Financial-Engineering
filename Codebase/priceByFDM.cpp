#include"priceByFDM.h"

double fdm::priceByExplicitFDM(const option* opt, const double& spot, const double& vol, const double& r, const int& tsteps, const int& ssteps, const double& smin, const double& smax) const {
	BSPDE bs(opt, vol, r, smin, smax);
	explicitMethod em(&bs, tsteps, ssteps, smin, smax);
	return em.solvePDE(&bs, spot);
}