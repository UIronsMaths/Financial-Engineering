#pragma once
#include<cmath>

class euroOption {
	friend class testing_euroOption;
public:
	euroOption(double strike, double expiry);
	virtual double priceByBSFormula(double spot, double sigma, double r) = 0;
	virtual double deltaByBSFormula(double spot, double sigma, double r) = 0;
	virtual double gammaByBSFormula(double spot, double sigma, double r) = 0;
	virtual double thetaByBSFormula(double spot, double sigma, double r) = 0;
protected:
	//
	// We have inputted data that will be used in this class.
	// Data Validation should be handled in the class/object we make for data input.
	// We want to keep each class as light as possible (Encapsulation principle).
	//
	double m_strike;
	double m_expiry;
	double N(double x);
	double phi(double x);
	double d_plus(double spot, double sigma, double r);
	double d_minus(double spot, double sigma, double r);
};

//
// The Euro Call and Put are objects of the Option type. So we use inheritance to embody this relationship.
//

class euroCall : public euroOption {
public:
	euroCall(double strike, double expiry);
	virtual double priceByBSFormula(double spot, double sigma, double r);
	virtual double deltaByBSFormula(double spot, double sigma, double r);
	virtual double gammaByBSFormula(double spot, double sigma, double r);
	virtual double thetaByBSFormula(double spot, double sigma, double r);
};

class euroPut : public euroOption {
public:
	euroPut(double strike, double expiry);
	virtual double priceByBSFormula(double spot, double sigma, double r);
	virtual double deltaByBSFormula(double spot, double sigma, double r);
	virtual double gammaByBSFormula(double spot, double sigma, double r);
	virtual double thetaByBSFormula(double spot, double sigma, double r);
};