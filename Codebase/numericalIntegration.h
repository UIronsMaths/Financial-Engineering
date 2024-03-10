#pragma once
#include<iostream>
#include<functional>

class numInt_adapterFunction {
public:
	virtual double eval(const double& x) const = 0;
};

class numericalIntegration {
	friend class testing_numericalIntegration;
public:

	//
	// Can instantiate the class in two ways, the first way limits your choice of trapezium method to the 4 parameter versions.
	//
	numericalIntegration();
	numericalIntegration(const double& lowerLim, const double& upperLim, const int& intervals);
	//
	// First option is to take a lambda function with a single variable parameter as input. Useful for non-repeated work.
	//
	double trapezium(const std::function<double(double)>& integrand);
	double trapezium(const std::function<double(double)>& integrand, const double& lowerLim, const double& upperLim, const int& intervals);
	//
	// Second option is to create an eval function that plugs into the adapter. Useful for repeated work.
	//
	double trapezium(const numInt_adapterFunction* f);
	double trapezium(const numInt_adapterFunction* f, const double& lowerLim, const double& upperLim, const int& intervals);
private:
	const double m_LL;
	const double m_UL;
	const int m_num;
};