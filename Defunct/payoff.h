#pragma once
#include<algorithm>

class payoff {
	friend class testing_payoff;
public:
	payoff(double spot, double strike);
	virtual double vanilla() = 0;
	virtual double vanilla(double spot) = 0;
	virtual double vanilla(double spot, double strike) = 0;
protected:
	double m_spot;
	double m_strike;
};

class Call : public payoff {
public:
	Call(double spot, double strike);
	virtual double vanilla();
	virtual double vanilla(double spot);
	virtual double vanilla(double spot, double strike);
};

class Put : public payoff {
public:
	Put(double spot, double strike);
	virtual double vanilla();
	virtual double vanilla(double spot);
	virtual double vanilla(double spot, double strike);
};