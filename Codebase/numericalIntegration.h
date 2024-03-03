#pragma once
#include<iostream>
#include<functional>

class numericalIntegration {
	friend class testing_numericalIntegration;
public:
	//
	// Trapezium method takes a lambda function with a single variable parameter as input.
	//

	numericalIntegration();
	numericalIntegration(double lowerLim, double upperLim, int intervals);
	double trapezium(std::function<double(double)> integrand);
	double trapezium(std::function<double(double)> integrand, double lowerLim, double upperLim, int intervals);
private:
	double m_LL;
	double m_UL;
	int m_num;
};