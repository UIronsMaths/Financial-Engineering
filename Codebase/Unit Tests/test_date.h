#pragma once
#include"../date.h"

class testing_date {
public:
	void testDate();
private:
	void testDMYSerial();
	void testSerialDMY();
	void testValidDate();
	void testDaysInMonth();
	void testLeapCount();
	void testGetDMY();
	void testWeekday();
	void testAdd();
	void testBD();
	void testOperator();
};

class testing_calendar {
public:
	void testCalendar();
private:
	void testAddHol();
	void testIsHol();
};