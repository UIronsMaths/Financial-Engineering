#include"finiteDifference.h"

double FDMethod::v(const double& t, const double& x) const
{
	int i = (int)(t / m_dt);
	int j = (int)((x - m_xmin) / m_dx);
	double l1 = (t - FDMethod::t(i)) / m_dt, l0 = 1.0 - l1;
	double w1 = (x - FDMethod::x(j)) / m_dx, w0 = 1.0 - w1;
	return l1 * w1 * m_v[i + 1][j + 1] + l1 * w0 * m_v[i + 1][j]
		+ l0 * w1 * m_v[i][j + 1] + l0 * w0 * m_v[i][j];
}
double explicitMethod::solvePDE(const BSPDE* pde, const double& X0) const
{

	//
	// Boundary condition on t. This can be at t=0 or at t=T.
	// For Black-Scholes this is t=T.
	//
	std::vector<double> v(m_jmax + 1);
	for (int j = 0; j <= m_jmax; ++j)
	{
		//
		// For options pricing the boundary is the Payoff function
		//
		v[j] = terminalBC(j);
	}

	//
	// Moving over t axis. This will be dependant on whether the Boundary condition on t is at 0 or T.
	// If T, we need to move backwards in time. Our explicit scheme will be constructed using backward difference approximations.
	// If 0, we are moving forwards in time. Our explicit scheme will be constructed using forward difference approximations.
	//
	int start, end;
	if (!m_ptrPDE->termBCatStart()) {
		start = m_imax;
		end = 0;
	}
	else {
		start = 0;
		end = m_imax;
	}
	for (int i = start; (!m_ptrPDE->termBCatStart() ? i >= end : i <= end); (!m_ptrPDE->termBCatStart() ? --i : ++i))
	{
		std::vector<double> u(m_jmax + 1);

		//
		// Moving over x axis.
		//
		for (int j = 1; j < m_jmax; ++j)
		{
			u[j] = A(i,j) * v[j - 1] + B(i,j) * v[j] + C(i,j) * v[j + 1];
		}

		//
		// The other (upper and lower) boundary conditions at x-min and x-max.
		//
		u[0] = pde->m_ptr->payoff(m_xmin);
		u[m_jmax] = pde->m_ptr->payoff(m_xmax);

		v = u;
	}

	//
	// Linearly interpolate since X0 may not correspond to a gridpoint.
	//
	const int left = floor(X0 - m_xmin) / m_dx;
	const double w = (X0 - (m_xmin + left * m_dx)) / m_dx;
	const double res = v[left] * (1.0 - w) + v[left + 1] * w;

	return res;
}