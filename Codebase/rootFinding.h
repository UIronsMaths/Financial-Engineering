#pragma once
#include<cmath>

class findRoot_adapterFunction {
public:
	virtual double eval(double x) const = 0;
};

class findRoot {
	friend class testing_rootFinding;
public:
	double bisectionSolver(const findRoot_adapterFunction* f, double target, double left, double right, double accuracy);
	double NewtonRaphson(const findRoot_adapterFunction* f, double target, double left, double right, double accuracy);
};