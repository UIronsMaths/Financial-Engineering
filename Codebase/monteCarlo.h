#pragma once
#include<vector>
#include<chrono>
#include<float.h>
#include"stats.h"
#include"vanillaOptions.h"
#include"exoticOptions.h"

struct MonteCarloResult {
	const double estimated_value;
	const double standard_error;
	const double elapsed_time;

	// Constructor to initialize members
	MonteCarloResult(const double& estimated_value_, const double& standard_error_, const double& elapsed_time_)
		: estimated_value(estimated_value_), standard_error(standard_error_), elapsed_time(elapsed_time_) {}
};

struct MonteCarloPricing {
	const double estimated_price;
	const double standard_error_price;

	const double estimated_delta;
	const double standard_error_delta;

	const double estimated_gamma;
	const double standard_error_gamma;

	const double elapsed_time;

	// Constructor to initialize members
	MonteCarloPricing(const double& estimated_price_, const double& standard_error_price_, const double& estimated_delta_, const double& standard_error_delta_, const double& estimated_gamma_, const double& standard_error_gamma_, const double& elapsed_time_)
		: estimated_price(estimated_price_), standard_error_price(standard_error_price_), estimated_delta(estimated_delta_), standard_error_delta(standard_error_delta_), estimated_gamma(estimated_gamma_), standard_error_gamma(standard_error_gamma_), elapsed_time(elapsed_time_) {}
};

class MonteCarlo {
	friend class testing_MC;
public:
	// Function to generate a random number within a specified range [min, max]
	double getRandomNumber(const double& min, const double& max) const;

	// Function to perform a Monte Carlo simulation for integration.
	// Takes a function pointer to the function to be integrated, the number of iterations, and the integration limits.
	MonteCarloResult monteCarloIntegration(double (*function)(const double&), const double& min, const double& max, const int& iterations);

	// Function to perform a Monte Carlo simulation for integration in higher dimensions
	// Takes the number of iterations, the function to be integrated, and integration limits for each dimension
	MonteCarloResult monteCarloIntegration(double (*function)(const std::vector<double>&), const std::vector<std::pair<double, double>>& limits, const int& iterations);

	// Function to perform a Monte Carlo simulation for area estimation
	// Takes the number of iterations, and the rectangle boundaries (x_min, x_max, y_min, y_max)
	MonteCarloResult monteCarloArea(bool (*function)(const double&, const double&), const double& x_min, const double& x_max, const double& y_min, const double& y_max, const int& iterations);

	// Function to perform a Monte Carlo simulation for area estimation in higher dimensions
	// Takes the number of iterations, the dimensions, and the boundary limits for each dimension
	MonteCarloResult monteCarloArea(bool (*function)(const std::vector<double>& points), const std::vector<std::pair<double, double>>& limits, const int& iterations);

	// Function to perform a Monte Carlo simulation for VANILLA Derivatives pricing.
	// NOTE: BS model assumed.
	// Takes a function pointer to the function to be integrated, the number of iterations, and the integration limits.
	MonteCarloPricing monteCarloPrice(const option* opt, const double& S0, const double& sigma, const double& r, const int& iterations, const double& perturbation = 0.005);

	MonteCarloPricing monteCarloPrice(const exotic* opt, const double& S0, const double& sigma, const double& r, const int& iterations, const double& perturbation = 0.005);
private:
	//
	// Ideal finite differencing width (for Greek calculations) is (epsilon * S0). (Jackel)
	//
	const double machine_precision = DBL_EPSILON;
public:
	const double epsilon = pow(machine_precision, 1.0 / 4.0);
};