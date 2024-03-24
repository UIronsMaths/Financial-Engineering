#include"monteCarlo.h"

// Function to generate a random number within a specified range [min, max]
double MonteCarlo::getRandomNumber(const double& min, const double& max) const {
	return min + ((double)rand() / RAND_MAX) * (max - min);
}
// Function to perform a Monte Carlo simulation for integration.
// Takes a function pointer to the function to be integrated, the number of iterations, and the integration limits.
MonteCarloResult MonteCarlo::monteCarloIntegration(double (*function)(const double&), const double& min, const double& max, const int& iterations) {
	auto start_time = std::chrono::steady_clock::now();

	stats1D stat;
	for (int i = 0; i < iterations; ++i) {
		double x = getRandomNumber(min, max);
		stat.add(function(x));
	}
	double estimated_value = stat.mean() * (max - min);
	double standard_error = stat.stDev() / sqrt(iterations);

	auto end_time = std::chrono::steady_clock::now();
	double elapsed_time = std::chrono::duration<double>(end_time - start_time).count();
	return MonteCarloResult(estimated_value, standard_error, elapsed_time);
}
// Function to perform a Monte Carlo simulation for integration in higher dimensions
// Takes the number of iterations, the function to be integrated, and integration limits for each dimension
MonteCarloResult MonteCarlo::monteCarloIntegration(double (*function)(const std::vector<double>&), const std::vector<std::pair<double, double>>& limits, const int& iterations) {
	auto start_time = std::chrono::steady_clock::now();

	int dimensions = limits.size();
	stats1D stat;
	for (int i = 0; i < iterations; ++i) {
		std::vector<double> point(dimensions);
		for (int j = 0; j < dimensions; ++j) {
			point[j] = getRandomNumber(limits[j].first, limits[j].second);
		}
		stat.add(function(point));
	}
	double estimated_value = stat.mean();
	for (int j = 0; j < dimensions; ++j) {
		estimated_value *= (limits[j].second - limits[j].first);
	}
	double standard_error = stat.stDev() / sqrt(iterations);

	auto end_time = std::chrono::steady_clock::now();
	double elapsed_time = std::chrono::duration<double>(end_time - start_time).count();
	return MonteCarloResult(estimated_value, standard_error, elapsed_time);
}
// Function to perform a Monte Carlo simulation for area estimation
// Takes the number of iterations, and the rectangle boundaries (x_min, x_max, y_min, y_max)
MonteCarloResult MonteCarlo::monteCarloArea(bool (*function)(const double&, const double&), const double& x_min, const double& x_max, const double& y_min, const double& y_max, const int& iterations) {
	auto start_time = std::chrono::steady_clock::now();

	//int inside_count = 0;
	stats1D stat;
	for (int i = 0; i < iterations; ++i) {
		double x = getRandomNumber(x_min, x_max);
		double y = getRandomNumber(y_min, y_max);
		if (function(x, y)) {
			//inside_count++;
			stat.add(1);
		}
		else {
			stat.add(0);
		}
	}
	double total_area = (x_max - x_min) * (y_max - y_min);
	double estimated_value = total_area * stat.mean();
	double standard_error = stat.stDev() / sqrt(iterations);

	auto end_time = std::chrono::steady_clock::now();
	double elapsed_time = std::chrono::duration<double>(end_time - start_time).count();
	return MonteCarloResult(estimated_value, standard_error, elapsed_time);
}
// Function to perform a Monte Carlo simulation for area estimation in higher dimensions
// Takes the number of iterations, the dimensions, and the boundary limits for each dimension
MonteCarloResult MonteCarlo::monteCarloArea(bool (*function)(const std::vector<double>& points), const std::vector<std::pair<double, double>>& limits, const int& iterations) {
	auto start_time = std::chrono::steady_clock::now();

	stats1D stat;
	int dimension = limits.size();
	for (int i = 0; i < iterations; ++i) {
		std::vector<double> point(dimension);
		for (int j = 0; j < dimension; ++j) {
			point[j] = getRandomNumber(limits[j].first, limits[j].second);
		}
		if (function(point)) {
			stat.add(1);
		}
		else {
			stat.add(0);
		}
	}
	double total_volume = 1.0;
	for (int j = 0; j < dimension; ++j) {
		total_volume *= (limits[j].second - limits[j].first);
	}
	double estimated_value = total_volume * stat.mean();
	double standard_error = stat.stDev() / sqrt(iterations);

	auto end_time = std::chrono::steady_clock::now();
	double elapsed_time = std::chrono::duration<double>(end_time - start_time).count();
	return MonteCarloResult(estimated_value, standard_error, elapsed_time);
}
//
// Functions for using Monte Carlo to price options.
//
MonteCarloPricing MonteCarlo::monteCarloPrice(const option* opt, const double& S0, const double& sigma, const double& r, const int& iterations, const double& perturbation) {
	auto start_time = std::chrono::steady_clock::now();

	const double drift = (r - sigma * sigma / 2.0) * opt->m_T;
	const double vol = sigma * sqrt(opt->m_T);
	const double discount = exp(-r * opt->m_T);
	//double importance_sample_count = 0;
	NormalRandomGenerator nrg;
	stats1D price;
	stats1D delta;
	stats1D gamma;
	for (int i = 0; i < iterations; ++i) {
		double factor = exp(drift + vol * nrg.generate());
		double S = S0 * factor;
		double S_perturbed_up = (1 + perturbation) * S0 * factor;
		double S_perturbed_down = (1 - perturbation) * S0 * factor;
		price.add(opt->payoff(S));
		delta.add((opt->payoff(S_perturbed_up) - opt->payoff(S_perturbed_down)) / (2 * S0 * perturbation));
		gamma.add(((opt->payoff(S_perturbed_up) + opt->payoff(S_perturbed_down)) - 2 * opt->payoff(S)) / ((S0 * perturbation) * (S0 * perturbation)));
	}
	//const double ITM_fraction = importance_sample_count / iterations;

	double estimated_value = discount * price.mean();
	double standard_error = discount * price.stDev() / sqrt(iterations);

	double estimated_delta = discount * delta.mean();
	double SE_delta = discount * delta.stDev() / sqrt(iterations);

	double estimated_gamma = discount * gamma.mean();
	double SE_gamma = discount * gamma.stDev() / sqrt(iterations);

	auto end_time = std::chrono::steady_clock::now();
	double elapsed_time = std::chrono::duration<double>(end_time - start_time).count();
	return MonteCarloPricing(estimated_value, standard_error, estimated_delta, SE_delta, estimated_gamma, SE_gamma, elapsed_time);
}
MonteCarloPricing MonteCarlo::monteCarloPrice(const exotic* opt, const double& S0, const double& sigma, const double& r, const int& iterations, const double& perturbation) {
	auto start_time = std::chrono::steady_clock::now();

	const double dt = opt->m_T / opt->m_M;
	const double drift = (r - sigma * sigma / 2.0) * dt;
	const double vol = sigma * sqrt(dt);
	const double discount = exp(-r * opt->m_T);
	//double importance_sample_count = 0;
	NormalRandomGenerator nrg;
	stats1D s_price;
	stats1D s_delta;
	stats1D s_gamma;

	for (unsigned int i = 0; i < iterations; ++i)
	{
		std::vector<double> S(opt->m_M + 1);
		std::vector<double> S_perturbed_up(opt->m_M + 1);
		std::vector<double> S_perturbed_down(opt->m_M + 1);
		S[0] = S0;
		S_perturbed_up[0] = S0;
		S_perturbed_down[0] = S0;
		for (unsigned int j = 1; j <= opt->m_M; ++j)
		{
			const double factor = exp(drift + vol * nrg.generate());
			S[j] = S[j - 1] * factor;
			S_perturbed_up[j] = S[j] * (1 + perturbation);
			S_perturbed_down[j] = S[j] * (1 - perturbation);
		}
		double po = opt->payoff(S);
		s_price.add(po);

		double delta = (opt->payoff(S_perturbed_up) - opt->payoff(S_perturbed_down)) / (2 * S0 * perturbation);
		s_delta.add(delta);

		double gamma = (opt->payoff(S_perturbed_up) + opt->payoff(S_perturbed_down)) - (2 * opt->payoff(S));
		gamma /= ((S0 * perturbation) * (S0 * perturbation));
		s_gamma.add(gamma);
	}
	//const double ITM_fraction = importance_sample_count / iterations;

	double estimated_value = discount * s_price.mean();
	double standard_error = discount * s_price.stDev() / sqrt(iterations);

	double estimated_delta = discount * s_delta.mean();
	double SE_delta = discount * s_delta.stDev() / sqrt(iterations);

	double estimated_gamma = discount * s_gamma.mean();
	double SE_gamma = discount * s_gamma.stDev() / sqrt(iterations);

	auto end_time = std::chrono::steady_clock::now();
	double elapsed_time = std::chrono::duration<double>(end_time - start_time).count();
	return MonteCarloPricing(estimated_value, standard_error, estimated_delta, SE_delta, estimated_gamma, SE_gamma, elapsed_time);
}