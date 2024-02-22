#include"options.h"

double option::N(double x) {
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

double option::phi(double x) {
	const double pi = 4.0 * atan(1.0);
	return (1 / sqrt(2 * pi)) * exp(-pow(x, 2) / 2);
}

bool euOption::earlyExercise() {
	return false;
}

bool amOption::earlyExercise() {
	return true;
}

double PIeu::priceByCRR(double spot, double vol, double r, int steps) {
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
			v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
		}
	}
	return v[0];
}

double wPDeu::priceByCRR(double spot, double vol, double r, int steps) {
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
			const double S = spot * pow(u, i) * pow(d, n - i);
			v[i] = pathCondition((qu * v[i + 1] + qd * v[i]) / (1.0 + R),S);
			if (earlyExercise())
			{
				const double S = spot * pow(u, i) * pow(d, n - i);
				const double exerciseValue = payoff(S);
				if (exerciseValue > v[i])
					v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}

double PIam::priceBySnell(double spot, double vol, double r, int steps) {
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
			v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
			const double S = spot * pow(u, i) * pow(d, n - i);
			const double exerciseValue = payoff(S);
			if (exerciseValue > v[i]) {
				v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}

double wPDam::priceBySnell(double spot, double vol, double r, int steps) {
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
			// Weak path dependancy modification.
			//
			v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
			const double S = spot * pow(u, i) * pow(d, n - i);
			const double exerciseValue = payoff(S);
			if (exerciseValue > v[i]) {
				v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}


/************************************************************************************************************************/


double UpAndOutEuroCall::D(double x, double r, double vol, double T) {
	return (log(x) + (r + (0.5 * pow(vol, 2))) * T) / (vol * sqrt(T));
}

double UpAndOutEuroCall::BSAnalyticalPrice(double spot, double vol, double r) {
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

double UpAndOutEuroCall::payoff(double spot) {
	return spot < m_B ? std::max(spot - m_K, 0.0) : 0.0;
}

double UpAndOutEuroCall::pathCondition(double treeNode, double spot) {
	return spot < m_B ? treeNode : 0.0;
}