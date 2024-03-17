#pragma once
#include<cmath>
#include"vanillaOptions.h"

//
// A second order PDE has the general form:
// Auxx + 2Buxy + Cuyy + Dux + Euy + F = 0
// It is said to be parabolic if:
// B^2 - AC = 0
// That is, there is only one set of characteristic curves.
//
//
// A general FDM solver for a general PDE of this form is under consideration.
// The generality required of this presents some challenge with no payoff for financial engineering.
// Meanwhile, the Black-Scholes PDE has been implemented to meet our actual needs for financial engineering.
//

class BSPDE {
	friend class FDMethod;
	friend class explicitMethod;
public:
	BSPDE(const option* ptr, const double& vol, const double& r, const double& s_min, const double& s_max)
		:m_ptr(ptr), m_T(ptr->m_T), m_vol(vol), m_r(r), m_smin(s_min), m_smax(s_max)
	{};
	double a(const double& t, const double& x)const;
	double b(const double& t, const double& x)const;
	double c(const double& t, const double& x)const;

	bool termBCatStart()const;
	double getT() const;
protected:
	const option* m_ptr;
	const double m_vol;
	const double m_r;
	const double m_T;
	const double m_smin;
	const double m_smax;
};