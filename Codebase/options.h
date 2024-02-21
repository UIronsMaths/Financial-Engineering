#pragma once
#include<cmath>
#include<algorithm>
#include<vector>

class option {
public:
	option(double T) :m_T(T) {};
protected:
	virtual double payoff(double spot) = 0;
	virtual bool earlyExercise() = 0;
	double N(double x);
	virtual double BSAnalyticalPrice(double spot, double vol, double r) = 0;
	virtual double priceByCRR(double spot, double vol, double r, int steps) = 0;
	const double m_T;
};

class euOption : public option {
public:
	euOption(double T) :option(T) {};
protected:
	virtual double payoff(double spot) = 0;
	bool earlyExercise();
	virtual double priceByCRR(double spot, double vol, double r, int steps) = 0;
};

class amOption : public option {
public:
	amOption(double T) :option(T) {};
protected:
	virtual double payoff(double spot) = 0;
	bool earlyExercise();
	virtual double priceBySnell(double spot, double vol, double r, int steps) = 0;
};

class PIeu : public euOption {
public:
	PIeu(double T) :euOption(T) {};
	double priceByCRR(double spot, double vol, double r, int steps);
protected:
	virtual double payoff(double spot) = 0;
};

class wPDeu : public euOption {
public:
	wPDeu(double T) :euOption(T) {};
	double priceByCRR(double spot, double vol, double r, int steps);
protected:
	virtual double payoff(double spot) = 0;
	virtual double pathCondition(double treeNode, double spot) = 0;
};

class sPDeu : public euOption {
public:
	sPDeu(double T) :euOption(T) {};
protected:
	virtual double payoff(double spot) = 0;
};

class PIam : public amOption {
public:
	PIam(double T) :amOption(T) {};
	double priceBySnell(double spot, double vol, double r, int steps);
protected:
	virtual double payoff(double spot) = 0;
};

class wPDam : public amOption {
public:
	wPDam(double T) :amOption(T) {};
	double priceBySnell(double spot, double vol, double r, int steps);
protected:
	virtual double payoff(double spot) = 0;
	virtual bool pathCondition() = 0;
};

class sPDam : public amOption {
public:
	sPDam(double T) :amOption(T) {};
protected:
	virtual double payoff(double spot) = 0;
};


/************************************************************************************************************************/


class UpAndOutEuroCall : public wPDeu {
public:
	UpAndOutEuroCall(double strike, double expiry, double barrier) :wPDeu(expiry), m_K(strike), m_B(barrier) {};
	virtual double BSAnalyticalPrice(double spot, double vol, double r);
private:
	double D(double x, double r, double vol, double expiry);
	double payoff(double spot);
	virtual double pathCondition(double treeNode, double spot);
	const double m_K;
	const double m_B;
};