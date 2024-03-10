#include"rootFinding.h"

double findRoot::derivativeO4(const findRoot_adapterFunction* f, const double& x, const double& delta) const {
    return (8 * (f->eval(x + delta) - f->eval(x - delta)) - f->eval(x + 2 * delta) + f->eval(x - 2 * delta)) / (12 * delta);
}

double findRoot::bisectionSolver(const findRoot_adapterFunction* f, const double& target, double left, double right, const double& accuracy) const {
    double l = f->eval(left);
    double r = f->eval(right);

    while (abs(l - r) >= accuracy) {
        double m = left + (right - left) / 2.0;
        double fm = f->eval(m);
        if (fm - target < 0) {
            left = m;
            l = f->eval(left);
        }
        else if (fm - target > 0) {
            right = m;
            r = f->eval(right);
        }
        else {
            return m;
        }
    }
    // You may return either left or right, they are very close to each other at this point.
    return left;
}

double findRoot::NewtonRaphson(const findRoot_adapterFunction* f, const double& initial, const double& accuracy) const {
    double ansatz = initial;
    while (abs(f->eval(ansatz)) >= accuracy) {
        ansatz -= (f->eval(ansatz) / derivativeO4(f, ansatz, 0.001));
    }
    return ansatz;
}