#include"rootFinding.h"

double findRoot::bisectionSolver(const findRoot_adapterFunction* f, double target, double left, double right, double accuracy) {
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