#pragma once
#include<cmath>
#include<algorithm>
#include<vector>
#include"pdf.h"
#include"numericalIntegration.h"
#include"rootFinding.h"
#include"linearInterpolation.h"

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

//
// Black - Scholes model assumed.
//

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
	option(const double& T, const optionType& type, const timeStruct& ts) :m_T(T), m_type(type), m_timeStruct(ts) {};
protected:

	//
	// Pricing methods
	//
	double binomialPriceCRR(const double& spot, const double& vol, const double& r, const int& steps) const;
	double binomialPriceJR(const double& spot, const double& vol, const double& r, const int& steps) const;
	double trinomialPrice(const double& spot, const double& vol, const double& r, const int& steps, const double& lambda) const;
	double priceByNumericalInt(const double& spot, const double& vol, const double& r, const int& steps) const;

	//
	// Polymorphic functions, defined in the payoff class when payoff class is initialised.
	// Definition will depend of initialisation of payoff class.
	//
	virtual double payoff(const double& spot) const = 0;
	virtual bool earlyExercise() const;
	
	//
	// Defaults. Have not made these polymorphic as not all options have these conditions.
	// These are overridden in the payoff classes that will see these used.
	//
	virtual bool pathDependancy() const;
	virtual double pathCondition(const double& treeNode, const double& spot) const;

	//
	// Generic methods used for a variety of functions across all kinds of options.
	//
	double N(const double& x) const;
	double phi(const double& x) const;
	const double m_T;
	const optionType m_type;
	const timeStruct m_timeStruct;
};

/************************************** Option Base Classes (Payoff structure specific) **************************************/

class vanilla : public option {
	friend class testing_options;
public:
	vanilla(const double& strike, const double& expiry, const optionType& type, const timeStruct& ts) : m_K(strike), option(expiry, type, ts) {};
	using option::binomialPriceCRR;
	using option::binomialPriceJR;
	using option::trinomialPrice;
	using option::priceByNumericalInt;
	double payoff(const double& spot) const;
protected:

	//
	// Payoff specific functions
	//
	double d_plus(const double& spot, const double& sigma, const double& r) const;
	double d_minus(const double& spot, const double& sigma, const double& r) const;

	//
	// Payoff specific member variables.
	//
	const double m_K;
};

class barrier : public option {
	friend class testing_options;
public:
	barrier(const double& strike, const double& expiry, const double& barrier, const optionType& type, const timeStruct& ts) : m_K(strike), m_B(barrier), option(expiry, type, ts) {};
	using option::binomialPriceCRR;
	using option::binomialPriceJR;
	using option::trinomialPrice;
	double payoff(const double& spot) const;
protected:

	//
	// Payoff specific functions
	//
	double D(const double& x, const double& r, const double& vol, const double& expiry) const;
	bool pathDependancy() const override;
	virtual double pathCondition(const double& treeNode, const double& spot) const override;

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
	vanillaEuroCall(const double& strike, const double& expiry) : vanilla(strike, expiry, Call, Eu) {};

	double BSAnalyticalPrice(const double& spot, const double& vol, const double& r) const;
	double deltaByBSFormula(const double& spot, const double& vol, const double& r) const;
	double gammaByBSFormula(const double& spot, const double& vol, const double& r) const;
	double thetaByBSFormula(const double& spot, const double& vol, const double& r) const;
};

class vanillaEuroPut : public vanilla {
public:
	vanillaEuroPut(const double& strike, const double& expiry) :vanilla(strike, expiry, Put, Eu) {};

	double BSAnalyticalPrice(const double& spot, const double& vol, const double& r) const;
	double deltaByBSFormula(const double& spot, const double& vol, const double& r) const;
	double gammaByBSFormula(const double& spot, const double& vol, const double& r) const;
	double thetaByBSFormula(const double& spot, const double& vol, const double& r) const;
};

class vanillaAmCall : public vanilla {
public:
	vanillaAmCall(const double& strike, const double& expiry) :vanilla(strike, expiry, Call, Am) {};
};

class vanillaAmPut : public vanilla {
public:
	vanillaAmPut(const double& strike, const double& expiry) :vanilla(strike, expiry, Put, Am) {};
};



class UpAndOutEuroCall : public barrier {
public:
	UpAndOutEuroCall(const double& strike, const double& expiry, const double& barrier) :barrier(strike, expiry, barrier, Call, Eu){};
	double BSAnalyticalPrice(const double& spot, const double& vol, const double& r) const;
};