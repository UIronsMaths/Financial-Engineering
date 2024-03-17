#include"parabolicPDE.h"

double BSPDE::a(const double& t, const double& x)const {
	return -0.5 * m_vol * m_vol * x * x;
}
double BSPDE::b(const double& t, const double& x)const {
	return -m_r * x;
}
double BSPDE::c(const double& t, const double& x)const {
	return m_r;
}
bool BSPDE::termBCatStart() const {
	return false;
}
double BSPDE::getT()const {
	return m_T;
}