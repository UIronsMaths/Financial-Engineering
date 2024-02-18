#pragma once
#include"pdf.h"
#include"payoff.h"
#include<iostream>
#include<functional>

class numericalIntegration {
	friend class testing_numericalIntegration;
public:
	//
	// Considering adding default constructor initialising limits as [0,1] and number of steps to be 100.
	// This would need an overloaded trapezium method to take advantage of.
	// This gives some choice in how to use the numericalIntegration object.
	//

	numericalIntegration(double lowerLim, double upperLim, int intervals);
	double trapezium(std::function<double(double)> integrand);
private:
	double m_LL;
	double m_UL;
	int m_num;
};