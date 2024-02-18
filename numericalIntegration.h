#pragma once
#include"pdf.h"
#include"payoff.h"
#include<iostream>
#include<functional>

class numericalIntegration {
	friend class testing_numericalIntegration;
public:
	numericalIntegration(double lowerLim, double upperLim, int intervals);
	double trapezium(std::function<double(double)> pdf, std::function<double(double)> payoff);
private:
	double m_LL;
	double m_UL;
	int m_num;
};