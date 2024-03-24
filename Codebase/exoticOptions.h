#pragma once
#include<vector>

/******************************************* Option Base Class (General structure) *******************************************/

class exotic {
	friend class testing_exotics;
public:
	enum optionType {
		Call,
		Put
	};
	enum timeStruct {
		Eu,
		Am
	};
	exotic(const double& T, const int& M, const optionType& type, const timeStruct& ts)
		:m_T(T), m_M(M), m_type(type), m_timeStruct(ts)
	{};
	/*
	option(const double& T)
		:m_T(T), m_type(Call), m_timeStruct(Eu)
	{};
	*/
	const double m_T;
	const int m_M;
	virtual double payoff(const std::vector<double>& path) const = 0;
protected:

	//
	// Polymorphic functions, defined in the payoff class when payoff class is initialised.
	// Definition will depend of initialisation of payoff class.
	//
	virtual bool earlyExercise() const;

	const optionType m_type;
	const timeStruct m_timeStruct;
};

/************************************** Option Base Classes (Payoff structure specific) **************************************/

class asian : public exotic {
	friend class testing_options;
public:
	asian(const double& strike, const double& expiry, const int& samplingDates, const optionType& type, const timeStruct& ts) 
		: m_K(strike), exotic(expiry, samplingDates, type, ts) 
	{};
	double payoff(const std::vector<double>& path) const;
protected:

	//
	// Payoff specific member variables.
	//
	const double m_K;
};
class rangeAccrual : public exotic {
public:
	//
	// Exotic constructor is taking defaults for option type and time structure. Will need to create a constructor for exotic that doesn't need these inputs.
	// Also, number of trading days in a year is used as magic number. While this works, it is unprofessional and needs to be fixed.
	//
	rangeAccrual(const double& notional, const double& s_min, const double& s_max, const double& expiry) 
		: m_D(252), m_B(notional), m_s_min(s_min), m_s_max(s_max), exotic(expiry, (int)(252*expiry), Call, Eu) 
	{};
	double payoff(const std::vector<double>& path) const;
protected:

	//
	// The magic number D is the number of trading days in a year.
	//
	const double m_D;
	const double m_s_min;
	const double m_s_max;
	const double m_B;
};

/***************************************** Option Derived Classes (Specific Options) *****************************************/

class asianEuroCall : public asian {
public:
	asianEuroCall(const double& strike, const double& expiry, const int& samplingDates)
		:asian(strike, expiry, samplingDates, Call, Eu)
	{};
};