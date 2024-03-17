#include"vanillaOptions.h"

/********************************** Option Base Classe (General & Time structure specific) **********************************/

double option::N(const double& x) const {
	const double gamma = 0.2316419;
	const double a1 = 0.319381530;
	const double a2 = -0.356563782;
	const double a3 = 1.781477937;
	const double a4 = -1.821255978;
	const double a5 = 1.330274429;
	const double pi = 4.0 * atan(1.0);
	double k = 1.0 / (1.0 + gamma * x);

	if (x >= 0) {
		return 1.0 - ((((a5 * k + a4) * k + a3) * k + a2) * k + a1) * k * exp(-x * x / 2.0) / sqrt(2.0 * pi);
	}
	else {
		return 1.0 - N(-x);
	}
}
double option::phi(const double& x) const {
	const double pi = 4.0 * atan(1.0);
	return (1 / sqrt(2 * pi)) * exp(-pow(x, 2) / 2);
}
bool option::earlyExercise() const  {
	if (m_timeStruct == Eu) {
		return false;
	}
	else {
		return true;
	}
}
bool option::pathDependancy() const { return false; }
double option::pathCondition(const double& treeNode, const double& spot) const { return 0.0; }

/************************************** Option Base Classes (Payoff structure specific) **************************************/

double vanilla::payoff(const double& spot) const {
	if (m_type == Call) {
		return spot > m_K ? spot - m_K : 0.0;
	}
	else {
		return spot < m_K ? m_K - spot : 0.0;
	}
}
double vanilla::d_plus(const double& spot, const double& sigma, const double& r) const  {
	return (log(spot / m_K) + (r + 0.5 * pow(sigma, 2)) * m_T) / (sigma * sqrt(m_T));
}
double vanilla::d_minus(const double& spot, const double& sigma, const double& r) const  {
	return d_plus(spot, sigma, r) - sigma * sqrt(m_T);
}



// This will be modified with the addition of more barrier options.
double barrier::payoff(const double& spot) const {
	return spot < m_B ? std::max(spot - m_K, 0.0) : 0.0;
}
double barrier::D(const double& x, const double& r, const double& vol, const double& T) const  {
	return (log(x) + (r + (0.5 * pow(vol, 2))) * T) / (vol * sqrt(T));
}
// This will be modified with the addition of more barrier options.
bool barrier::pathDependancy() const  {
	return true;
}
// This will be modified with the addition of more barrier options.
double barrier::pathCondition(const double& treeNode, const double& spot) const  {
	return spot < m_B ? treeNode : 0.0;
}


double chooser::d(const double& s, const double& r, const double& vol) const {
	return (log(s / m_K) + (r + 0.5 * vol * vol) * m_T) / (vol * sqrt(m_T));
}
double chooser::y(const double& s, const double& r, const double& vol) const {
	return (log(s / m_K) + (r * m_T) + (0.5 * vol * vol * m_Tc)) / (vol * sqrt(m_Tc));
}
double chooser::price(const double& s, const double& vol, const double& r) const {
	return s * N(d(s, r, vol)) - m_K * N(d(s, r, vol) - vol * sqrt(m_T)) - s * N(-y(s, r, vol)) + m_K * exp(-r * m_T) * N(-y(s, r, vol) + vol * sqrt(m_Tc));
}
double chooser::payoff(const double& x) const {
	//
	// The payoff of a chooser option is expressed at the choosing time as the maximum of the prices of call and put.
	// For this time dependancy we cannot use the payoff function to compute the intrinsic value of the option.
	// Not that you want to. It would always be optimal to hold off on choosing until the choosing date to be certain you are getting the best price.
	//
	return std::max(vanillaEuroCall(m_K, m_T).payoff(x), vanillaEuroPut(m_K, m_T).payoff(x));
}

/***************************************** Option Derived Classes (Specific Options) *****************************************/

double vanillaEuroCall::BSAnalyticalPrice(const double& spot, const double& vol, const double& r) const {
	return (spot * N(d_plus(spot, vol, r))) - (m_K * exp(-r * m_T) * N(d_minus(spot, vol, r)));
}
double vanillaEuroCall::deltaByBSFormula(const double& spot, const double& vol, const double& r) const {
	return N(d_plus(spot, vol, r));
}
double vanillaEuroCall::gammaByBSFormula(const double& spot, const double& vol, const double& r) const {
	return phi(d_plus(spot, vol, r)) / (spot * vol * sqrt(m_T));
}
double vanillaEuroCall::thetaByBSFormula(const double& spot, const double& vol, const double& r) const {
	return -(spot * phi(d_plus(spot, vol, r)) * vol) / (2 * sqrt(m_T)) - (r * m_K * exp(-r * m_T) * N(d_minus(spot, vol, r)));
}



double vanillaEuroPut::BSAnalyticalPrice(const double& spot, const double& vol, const double& r) const {
	return (m_K * exp(-r * m_T) * N(-d_minus(spot, vol, r))) - (spot * N(-d_plus(spot, vol, r)));
}
double vanillaEuroPut::deltaByBSFormula(const double& spot, const double& vol, const double& r) const {
	return N(d_plus(spot, vol, r)) - 1;
}
double vanillaEuroPut::gammaByBSFormula(const double& spot, const double& vol, const double& r) const {
	return phi(d_plus(spot, vol, r)) / (spot * vol * sqrt(m_T));
}
double vanillaEuroPut::thetaByBSFormula(const double& spot, const double& vol, const double& r) const {
	return -(spot * phi(d_plus(spot, vol, r)) * vol) / (2 * sqrt(m_T)) + (r * m_K * exp(-r * m_T) * N(-d_minus(spot, vol, r)));
}



double UpAndOutEuroCall::BSAnalyticalPrice(const double& spot, const double& vol, const double& r) const {
	double d1 = D(spot / m_K, r, vol, m_T);
	double d2 = d1 - vol * sqrt(m_T);
	double d3 = D(spot / m_B, r, vol, m_T);
	double d4 = d3 - vol * sqrt(m_T);
	double d5 = D(spot / m_B, -r, vol, m_T);
	double d6 = d5 - vol * sqrt(m_T);
	double d7 = D((spot * m_K) / pow(m_B, 2), -r, vol, m_T);
	double d8 = d7 - vol * sqrt(m_T);
	double T1 = spot * (N(d1) - N(d3) - pow(m_B / spot, 1 + 2 * r / pow(vol, 2)) * (N(d6) - N(d8)));
	double T2 = -m_K * exp(-r * m_T) * (N(d2) - N(d4) - pow(m_B / spot, -1 + 2 * r / pow(vol, 2)) * (N(d5) - N(d7)));
	return T1 + T2;
}