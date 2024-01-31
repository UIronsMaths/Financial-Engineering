#pragma once
#include<iostream>
#include<map>

class testing_linInt;

class linInterpolation {
    friend class testing_linInt;

public:
    linInterpolation();
    void add(double x, double y);
    double value(double x);

private:
    std::map<double, double> m_points;
    double m_maxX;
    double m_minX;

};