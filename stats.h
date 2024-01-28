#pragma once

class stats1D {
public:
	stats1D();
	void add(double x);
	double mean();
	double var();
	double stDev();
private:
	int m_size;
	double m_sum;
	double m_sumsquared;
};

class stats2D {
public:
	stats2D();
	void add(double x, double y);
	double meanX();
	double varX();
	double stDevX();
	double meanY();
	double varY();
	double stDevY();
	double cov();
	double corr();
	double lineargradient();
	double linearintercept();
private:
	int m_size;
	double m_sum_x;
	double m_sumsquared_x;
	double m_sum_y;
	double m_sumsquared_y;
	double m_sum_xy;
};