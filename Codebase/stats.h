#pragma once
#include<iostream>
#include<cmath>

const double pi = 4.0 * atan(1.0);

class stats1D {
	friend class testing_stats;
public:
	stats1D()
		:m_size(0), m_sum(0), m_sumsquared(0)
	{};
	void add(const double& x);
	double mean() const;
	double var() const;
	double stDev() const;
	int size() const;
private:
	int m_size;
	double m_sum;
	double m_sumsquared;
};

class stats2D {
	friend class testing_stats;
public:
	stats2D()
		:m_size(0), m_sum_x(0), m_sumsquared_x(0), m_sum_y(0), m_sumsquared_y(0), m_sum_xy(0)
	{}
	void add(const double& x, const double& y);
	double meanX() const;
	double varX() const;
	double stDevX() const;
	double meanY() const;
	double varY() const;
	double stDevY() const;
	double cov() const;
	double corr() const;
	double lineargradient() const;
	double linearintercept() const;
	int size() const;
private:
	int m_size;
	double m_sum_x;
	double m_sumsquared_x;
	double m_sum_y;
	double m_sumsquared_y;
	double m_sum_xy;
};

class NormalRandomGenerator {
	friend class testing_stats;
public:
	NormalRandomGenerator() :m_boolFlag(false), m_val(0.0) {};
	double generate();
private:
	bool m_boolFlag;
	double m_val;
	double boxMuller();
};