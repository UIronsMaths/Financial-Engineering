#include"priceByTree.h"

double tree::binomialPriceCRR(const option* opt, const double& spot, const double& vol, const double& r, const int& steps) const {
	const double delta = opt->m_T / steps;
	const double u = exp(vol * sqrt(delta));
	const double d = 1.0 / u;
	const double R = exp(r * delta) - 1.0;

	const double qu = (1.0 + R - d) / (u - d);
	const double qd = 1.0 - qu;

	std::vector<double> v(steps + 1);
	for (int i = 0; i <= steps; ++i)
	{
		const double ST = spot * pow(u, i) * pow(d, steps - i);
		v[i] = opt->payoff(ST);
	}
	for (int n = steps - 1; n >= 0; --n)
	{
		for (int i = 0; i <= n; ++i)
		{
			//
			// Weak Path dependancy modification.
			//
			if (opt->pathDependancy()) {
				const double S = spot * pow(u, i) * pow(d, n - i);
				v[i] = opt->pathCondition((qu * v[i + 1] + qd * v[i]) / (1.0 + R), S);
			}
			else {
				v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
			}
			if (opt->earlyExercise())
			{
				const double S = spot * pow(u, i) * pow(d, n - i);
				double exerciseValue = opt->payoff(S);
				if (opt->pathDependancy()) {
					exerciseValue = opt->pathCondition(exerciseValue, S);
				}
				if (exerciseValue > v[i])
					v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}
double tree::binomialPriceJR(const option* opt, const double& spot, const double& vol, const double& r, const int& steps) const {
	const double delta = opt->m_T / steps;
	const double u = exp((r - vol * vol / 2) * delta + vol * sqrt(delta));
	const double d = exp((r - vol * vol / 2) * delta - vol * sqrt(delta));
	const double R = exp(r * delta) - 1.0;

	const double qu = (1.0 + R - d) / (u - d);
	const double qd = 1.0 - qu;

	std::vector<double> v(steps + 1);
	for (int i = 0; i <= steps; ++i)
	{
		const double ST = spot * pow(u, i) * pow(d, steps - i);
		v[i] = opt->payoff(ST);
	}
	for (int n = steps - 1; n >= 0; --n)
	{
		for (int i = 0; i <= n; ++i)
		{
			//
			// Weak Path dependancy modification.
			//
			if (opt->pathDependancy()) {
				const double S = spot * pow(u, i) * pow(d, n - i);
				v[i] = opt->pathCondition((qu * v[i + 1] + qd * v[i]) / (1.0 + R), S);
			}
			else {
				v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
			}
			if (opt->earlyExercise())
			{
				const double S = spot * pow(u, i) * pow(d, n - i);
				double exerciseValue = opt->payoff(S);
				if (opt->pathDependancy()) {
					exerciseValue = opt->pathCondition(exerciseValue, S);
				}
				if (exerciseValue > v[i])
					v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}
double tree::trinomialPrice(const option* opt, const double& spot, const double& vol, const double& r, const int& steps, const double& lambda) const {
	const double delta = opt->m_T / steps;
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
		const double ST = spot * pow(u, std::max(i - steps, 0)) * pow(d, std::max(steps - i, 0));
		v[i] = opt->payoff(ST);
	}
	for (int n = steps - 1; n > 0; --n)
	{
		for (int i = 0; i <= 2 * n; ++i)
		{
			//
			// Weak Path dependancy modification.
			//
			if (opt->pathDependancy()) {
				const double S = spot * pow(u, std::max(i - steps, 0)) * pow(d, std::max(steps - i, 0));
				v[i] = opt->pathCondition((qu * v[i + 2] + qm * v[i + 1] + qd * v[i]) / (1.0 + R), S);
			}
			else {
				v[i] = (qu * v[i + 2] + qm * v[i + 1] + qd * v[i]) / (1.0 + R);
			}
			if (opt->earlyExercise())
			{
				const double S = spot * pow(u, std::max(i - steps, 0)) * pow(d, std::max(steps - i, 0));
				double exerciseValue = opt->payoff(S);
				if (opt->pathDependancy()) {
					exerciseValue = opt->pathCondition(exerciseValue, S);
				}
				if (exerciseValue > v[i])
					v[i] = exerciseValue;
			}
		}
	}
	return v[0];
}
