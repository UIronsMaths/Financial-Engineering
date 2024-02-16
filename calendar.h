#pragma once
#include"date.h"
#include<set>

class calendar {
	friend class testing_calendar;
public:
	/*
	void addHoliday(const date& dt);
	bool isHoliday(const date& dt) const;
	*/
private:
	std::set<unsigned int> m_calendar;
};