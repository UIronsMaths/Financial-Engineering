#include"options.h"

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

double option::binomialPriceCRR(const double& spot, const double& vol, const double& r, const int& steps) const {
	const double delta = m_T / steps;
	const double u = exp(vol * sqrt(delta));
	const double d = 1.0 / u;
	const double R = exp(r * delta) - 1.0;

	const double qu = (1.0 + R - d) / (u - d);
	const double qd = 1.0 - qu;

	std::vector<double> v(steps + 1);
	for (int i = 0; i <= steps; ++i)
	{
		const double ST = spot * pow(u, i) * pow(d, steps - i);
		v[i] = payoff(ST);
	}
	for (int n = steps - 1; n >= 0; --n)
	{
		for (int i = 0; i <= n; ++i)
		{
			//
			// Weak Path dependancy modification.
			//
			if (pathDependancy()) {
				const double S = spot * pow(u, i) * pow(d, n - i);
				v[i] = pathCondition((qu * v[i + 1] + qd * v[i]) / (1.0 + R), S);
			}
			else {
				v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
			}
			if (earlyExercise())
			{
				const double S = spot * pow(u, i) * pow(d, n - i);
				double exerciseValue = payoff(S);
				if (pathDependancy()) {
					exerciseValue = pathCondition(exerciseValue, S);
				}
				if (exerciseValue > v[i])
					v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}

double option::binomialPriceJR(const double& spot, const double& vol, const double& r, const int& steps) const {
	const double delta = m_T / steps;
	const double u = exp((r - vol * vol / 2) * delta + vol * sqrt(delta));
	const double d = exp((r - vol * vol / 2) * delta - vol * sqrt(delta));
	const double R = exp(r * delta) - 1.0;

	const double qu = (1.0 + R - d) / (u - d);
	const double qd = 1.0 - qu;

	std::vector<double> v(steps + 1);
	for (int i = 0; i <= steps; ++i)
	{
		const double ST = spot * pow(u, i) * pow(d, steps - i);
		v[i] = payoff(ST);
	}
	for (int n = steps - 1; n >= 0; --n)
	{
		for (int i = 0; i <= n; ++i)
		{
			//
			// Weak Path dependancy modification.
			//
			if (pathDependancy()) {
				const double S = spot * pow(u, i) * pow(d, n - i);
				v[i] = pathCondition((qu * v[i + 1] + qd * v[i]) / (1.0 + R), S);
			}
			else {
				v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
			}
			if (earlyExercise())
			{
				const double S = spot * pow(u, i) * pow(d, n - i);
				double exerciseValue = payoff(S);
				if (pathDependancy()) {
					exerciseValue = pathCondition(exerciseValue, S);
				}
				if (exerciseValue > v[i])
					v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}

double option::trinomialPrice(const double& spot, const double& vol, const double& r, const int& steps, const double& lambda) const  {
	const double delta = m_T / steps;
	const double u = exp(lambda * vol * sqrt(delta));
	const double d = 1.0 / u;
	const double R = exp(r * delta) - 1.0;

	const double M = exp(r * delta);
	const double V = exp(2.0 * r * delta) * (exp(vol * vol * delta) - 1);
	const double qu = (V + (M * M) - M) * u - (M - 1) / (u - 1) * ((u * u) - 1);
	const double qd = (V + (M * M) - M) * (u * u) - (M - 1) * (u * u * u) / (u - 1) * ((u * u) - 1);
	const double qm = 1 - qu - qd;

	std::vector<double> v(2 * steps + 1);
	for (int i = 0; i <= 2 * steps; ++i)
	{
		const double ST = spot * pow(u, std::max(i-steps, 0)) * pow(d, std::max(steps - i, 0));
		v[i] = payoff(ST);
	}
	for (int n = steps - 1; n > 0; --n)
	{
		for (int i = 0; i <= 2 * n; ++i)
		{
			//
			// Weak Path dependancy modification.
			//
			if (pathDependancy()) {
				const double S = spot * pow(u, std::max(i - steps, 0)) * pow(d, std::max(steps - i, 0));
				v[i] = pathCondition((qu * v[i + 2] + qm * v[i + 1] + qd * v[i]) / (1.0 + R), S);
			}
			else {
				v[i] = (qu * v[i + 2] + qm * v[i + 1] + qd * v[i]) / (1.0 + R);
			}
			if (earlyExercise())
			{
				const double S = spot * pow(u, std::max(i - steps, 0)) * pow(d, std::max(steps - i, 0));
				double exerciseValue = payoff(S);
				if (pathDependancy()) {
					exerciseValue = pathCondition(exerciseValue, S);
				}
				if (exerciseValue > v[i])
					v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}

double option::priceByNumericalInt(const double& spot, const double& vol, const double& r, const int& steps) const {
	const double mean = log(spot) + ((r - (0.5 * pow(vol, 2))) * m_T);
	const double var = pow(vol * sqrt(m_T), 2);
	const double upperLim = 5 * spot;

	numericalIntegration numInt;
	pdf pf;

	double res = numInt.trapezium(
		[this, &pf, &mean, &var, &upperLim](const double& x) -> double {return pf.lognormal(x, mean, var) * payoff(x); }
	, 0.0, upperLim, steps);

	res *= exp(-r * m_T);
	return res;
}

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