#pragma once
#include<cmath>

class findRoot_adapterFunction {
public:
	virtual double eval(const double& x) const = 0;
};

class findRoot {
	friend class testing_rootFinding;
public:
	double bisectionSolver(const findRoot_adapterFunction* f, const double& target, double left, double right, const double& accuracy) const;
	double NewtonRaphson(const findRoot_adapterFunction* f, const double& initial, const double& accuracy) const;
	double secant(const findRoot_adapterFunction* f, const double& initial, const double& accuracy) const;
	double Bairstows(const findRoot_adapterFunction* f, const double& initial, const double& accuracy) const;
	double Mullers(const findRoot_adapterFunction* f, const double& initial, const double& accuracy) const;
	double Brents(const findRoot_adapterFunction* f, const double& initial, const double& accuracy) const;
private:
	double derivativeO4(const findRoot_adapterFunction* f, const double& x, const double& delta) const;
};