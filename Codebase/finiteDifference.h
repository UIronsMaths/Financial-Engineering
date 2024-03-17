#pragma once
#include<vector>
#include"parabolicPDE.h"

class FDMethod
{
public:
	FDMethod(const BSPDE* ptr, const int& tsteps, const int& xsteps, const double& xmin, const double& xmax)
		:m_ptrPDE(ptr), m_imax(tsteps), m_jmax(xsteps), m_xmin(xmin), m_xmax(xmax), m_dx((xmax - xmin) / xsteps), m_dt( ptr->getT()  / tsteps),
		m_v(tsteps, std::vector<double>(xsteps))
	{};
	double t(const double& i) const { return m_dt * i; }
	double x(const int& j)  const { return m_xmin + m_dx * j; }

	double a(const double& i, const int& j) const { return m_ptrPDE->a(t(i), x(j)); }
	double b(const double& i, const int& j) const { return m_ptrPDE->b(t(i), x(j)); }
	double c(const double& i, const int& j) const { return m_ptrPDE->c(t(i), x(j)); }

	double terminalBC(const int& j) const { return m_ptrPDE->m_ptr->payoff(x(j)); }
	double upperBC(const int& i) const { return m_ptrPDE->m_ptr->payoff(m_xmax); }
	double lowerBC(const int& i) const { return m_ptrPDE->m_ptr->payoff(m_xmin); }

	double v(const double& t, const double& x) const;
	virtual double solvePDE(const BSPDE* pde, const double& X0) const = 0;
protected:
	const BSPDE* m_ptrPDE;
	const int m_imax, m_jmax;
	const double m_xmin, m_xmax;
	const double m_dx, m_dt;
	std::vector<std::vector<double>> m_v;
};
class explicitMethod : public FDMethod
{
public:
	explicitMethod(const BSPDE* ptr, const int& tsteps, const int& xsteps, const double& xmin, const double& xmax)
		:FDMethod(ptr, tsteps, xsteps, xmin, xmax) {}
	double A(const int& i, const int& j) const { return m_dt * (b(i, j) / 2.0 - a(i, j) / m_dx) / m_dx; }
	double B(const int& i, const int& j) const { return 1.0 - m_dt * c(i, j) + 2.0 * m_dt * a(i, j) / (m_dx * m_dx); }
	double C(const int& i, const int& j) const { return-m_dt * (b(i, j) / 2.0 + a(i, j) / m_dx) / m_dx; }

	double solvePDE(const BSPDE* pde, const double& X0) const;

};
//
// The implicit method is not genrealised here. I solved the scheme specifically in the conext of options pricing.
//