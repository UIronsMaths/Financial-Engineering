#include"exoticOptions.h"

/******************************************* Option Base Class (General structure) *******************************************/

bool exotic::earlyExercise() const {
	if (m_timeStruct == Eu) {
		return false;
	}
	else {
		return true;
	}
}

/************************************** Option Base Classes (Payoff structure specific) **************************************/

double asian::payoff(const std::vector<double>& path) const {
	double path_total = 0;
	for (int i = 1; i < path.size(); i++) {
		path_total += path[i];
	}
	const double avg = path_total / (path.size() - 1);
	if (m_type == Call) {
		return avg - m_K > 0 ? avg - m_K : 0.0;
	}
	else {
		return m_K - avg > 0 ? m_K - avg : 0.0;
	}
}
double rangeAccrual::payoff(const std::vector<double>& path) const {
	int countDays = 0;
	for (int i = 1; i < path.size(); i++) {
		if (path[i] >= m_s_min && path[i] <= m_s_max) {
			countDays++;
		}
	}
	return m_B * countDays / (m_D * m_T);
}

/***************************************** Option Derived Classes (Specific Options) *****************************************/