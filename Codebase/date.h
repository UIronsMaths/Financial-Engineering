#pragma once
#include<iostream>
#include<vector>
#include<tuple>
#include<set>
#include"calendar.h"

//
// Forward declaration needed to avoid circular dependancy.
//
class calendar;

class date {
	friend class testing_date;
public:
	enum Weekday { Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6, Sunday = 7 };

	date(unsigned int day, unsigned int month, unsigned int year);
	date(unsigned int numDays);
	int getSerial() const;
	std::tuple<int, int, int> getDMY();
	void addDays(int days);
	void addMonths(int months);
	void addYears(int years);
	int daysDiff(date dt);
	enum Weekday weekday();
	bool isGBD();
	bool isGBD(const calendar& cal);
	void rollToGBD();
	void rollToGBD(const calendar& cal);
	void addBusinessDays(int days);

	date operator++();
	bool operator!=(date dt);

private:
	unsigned int m_serial;

	int DMY_to_serial(int day, int month, int year);
	void serial_to_DMY(int m_serial, unsigned int& day, unsigned int& month, unsigned int& year);
    bool isValidDate(int day, int month, int year);
    bool isLeapYear(int year);
    int countLeapYears(int startYear, int endYear);
	int getDaysInMonth(int year, int month);
};