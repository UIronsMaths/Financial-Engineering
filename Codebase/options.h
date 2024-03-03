#pragma once
#include<cmath>
#include<algorithm>
#include<vector>

//
// The idea of the class structure in this file is to utilise the "Is a" relationships that exists in options.
// For example:
//     A European Option is an Option.
//     A Vanilla Call Option is an Option with a vanilla payoff structure.
// 
// I have implemented the option base class which contains all the base functionality that could be used for specific options.
// This was done to reduce the number of times I have to write the same code. But it means the code I write has to be more generic.
// There are at least two protected base class methods that are set as a default. These are overidden when useful.
// 
// The payoff structure classes contain methods shared across specific options with that payoff structure.
// Generally this is methods that are used in the Analytical Formula price implementations.
// This is also where my option specific data such as strike price is stored.
// In these we I also specify which pricing methods can be used (if applicable to both European and American options).
// 
// The derived classes are the specific options you could encounter out in the wild. 
// These classes contain only the methods that cannot be shared.
//

/******************************************* Option Base Class (General structure) *******************************************/

class option {
	friend class testing_options;
public:
	enum optionType {
		Call,
		Put
	};
	enum timeStruct {
		Eu,
		Am
	};
	option(double T, optionType type, timeStruct(ts)) :m_T(T), m_type(type), m_timeStruct(ts) {};
protected:

	//
	// Pricing methods
	//
	double binomialPrice(double spot, double vol, double r, int steps);
	double trinomialPrice(double spot, double vol, double r, int steps, double lambda);
	double priceByNumericalInt(double spot, double vol, double r);

	//
	// Polymorphic functions, defined in the payoff class when payoff class is initialised.
	// Definition will depend of initialisation of payoff class.
	//
	virtual double payoff(double spot) = 0;
	virtual bool earlyExercise();
	
	//
	// Defaults. Have not made these polymorphic as not all options have these conditions.
	// These are overridden in the payoff classes that will see these used.
	//
	virtual bool pathDependancy();
	virtual double pathCondition(double treeNode, double spot);

	//
	// Generic methods used for a variety of functions across all kinds of options.
	//
	double N(double x);
	double phi(double x);
	const double m_T;
	optionType m_type;
	timeStruct m_timeStruct;
};

/************************************** Option Base Classes (Payoff structure specific) **************************************/

class vanilla : public option {
	friend class testing_options;
public:
	vanilla(double strike, double expiry, optionType type, timeStruct ts) : m_K(strike), option(expiry, type, ts) {};
	using option::binomialPrice;
	using option::trinomialPrice;
	double payoff(double spot);
protected:

	//
	// Payoff specific functions
	//
	double d_plus(double spot, double sigma, double r);
	double d_minus(double spot, double sigma, double r);

	//
	// Payoff specific member variables.
	//
	const double m_K;
};

class barrier : public option {
	friend class testing_options;
public:
	barrier(double strike, double expiry, double barrier, optionType type, timeStruct ts) : m_K(strike), m_B(barrier), option(expiry, type, ts) {};
	using option::binomialPrice;
	using option::trinomialPrice;
	double payoff(double spot);
protected:

	//
	// Payoff specific functions
	//
	double D(double x, double r, double vol, double expiry);
	bool pathDependancy() override;
	virtual double pathCondition(double treeNode, double spot) override;

	//
	// Payoff specific member variables.
	//
	const double m_K;
	const double m_B;
};

/***************************************** Option Derived Classes (Specific Options) *****************************************/

//
// Key note: With few exceptions, it is not possible to find exact formulae for the value of American Options.
// It should be noted however that there do exists several excellent closed form approximations.
// For example: The Barone-Adesi and Whaley approximation, or The Bjerksund and Stensland Approximation.
// These approximations are not included. Currently no plans exist to include them, preferring instead more generic implementations
// of other numerical pricing techniques such as trees and monte carlo.
//

class vanillaEuroCall : public vanilla {
public:
	vanillaEuroCall(double strike, double expiry) : vanilla(strike, expiry, Call, Eu) {};

	double BSAnalyticalPrice(double spot, double vol, double r);
	double deltaByBSFormula(double spot, double sigma, double r);
	double gammaByBSFormula(double spot, double sigma, double r);
	double thetaByBSFormula(double spot, double sigma, double r);
};

class vanillaEuroPut : public vanilla {
public:
	vanillaEuroPut(double strike, double expiry) :vanilla(strike, expiry, Put, Eu) {};

	double BSAnalyticalPrice(double spot, double vol, double r);
	double deltaByBSFormula(double spot, double sigma, double r);
	double gammaByBSFormula(double spot, double sigma, double r);
	double thetaByBSFormula(double spot, double sigma, double r);
};

class vanillaAmCall : public vanilla {
public:
	vanillaAmCall(double strike, double expiry) :vanilla(strike, expiry, Call, Am) {};
};

class vanillaAmPut : public vanilla {
public:
	vanillaAmPut(double strike, double expiry) :vanilla(strike, expiry, Put, Am) {};
};



class UpAndOutEuroCall : public barrier {
public:
	UpAndOutEuroCall(double strike, double expiry, double barrier) :barrier(strike, expiry, barrier, Call, Eu){};
	double BSAnalyticalPrice(double spot, double vol, double r);
};