#pragma once
#include<iostream>
#include<vector>
#include<tuple>
#include<set>

//
// Forward declaration needed to avoid circular dependancy.
//
class calendar;

class date {
	friend class testing_date;
public:
	enum Weekday { Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6, Sunday = 7 };

	date(const unsigned int& day, const unsigned int& month, const unsigned int& year);
	date(const unsigned int& numDays);
	date(const date& other);
	int getSerial() const;
	std::tuple<int, int, int> getDMY() const;
	void addDays(const int& days);
	void addMonths(const int& months);
	void addYears(const int& years);
	int daysDiff(const date& dt) const;
	enum Weekday weekday() const;
	bool isGBD() const;
	bool isGBD(const calendar& cal) const;
	void rollToGBD();
	void rollToGBD(const calendar& cal);
	void addBusinessDays(const int& days);

	date& operator++();
	date& operator--();
	date& operator+=(const int& days);
	date& operator-(const int& days);
	int operator-(const date& dt) const;
	bool operator!=(const date& dt) const;
	bool operator==(const date& dt) const;
	bool operator<(const date& dt) const;
	bool operator>(const date& dt) const;

	friend std::ostream& operator<<(std::ostream& os, const date& dt);

private:
	unsigned int m_serial;

	int DMY_to_serial(const int& day, const int& month, const int& year) const;
	void serial_to_DMY(const unsigned int m_serial, unsigned int& day, unsigned int& month, unsigned int& year) const;
    bool isValidDate(const int& day, const int& month, const int& year) const;
    bool isLeapYear(const int& year) const;
    int countLeapYears(const int& startYear, const int& endYear) const;
	int getDaysInMonth(const int& year, const int& month) const;
};

class calendar {
	friend class testing_calendar;
public:
	void addHoliday(const date& dt);
	bool isHoliday(const date& dt) const;
private:
	std::set<unsigned int> m_calendar;
};