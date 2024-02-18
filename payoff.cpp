#include"payoff.h"

payoff::payoff(double spot, double strike)
	:m_spot(spot), m_strike(strike)
{}

Call::Call(double spot, double strike)
	:payoff(spot,strike)
{}

Put::Put(double spot, double strike)
	:payoff(spot,strike)
{}

double Call::vanilla() {
	return std::max(m_spot - m_strike, 0.0);
}

double Call::vanilla(double spot) {
	return std::max(spot - m_strike, 0.0);
}

double Call::vanilla(double spot, double strike) {
	return std::max(spot - strike, 0.0);
}

double Put::vanilla() {
	return std::max(m_strike - m_spot, 0.0);
}

double Put::vanilla(double spot) {
	return std::max(m_strike - spot, 0.0);
}

double Put::vanilla(double spot, double strike) {
	return std::max(strike - spot, 0.0);
}