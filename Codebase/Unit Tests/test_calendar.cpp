#include"test_calendar.h"
#include<cassert>

void testing_calendar::testCalendar() {
	testAddHol();
	testIsHol();
	std::cout << "All testcases passed." << std::endl;
}

void testing_calendar::testAddHol() {
	calendar test;
	date dt1(1, 1, 2024);
	test.addHoliday(dt1);
	date dt2(25, 12, 2024);
	test.addHoliday(dt2);
	assert(test.m_calendar.find(dt1.getSerial()) != test.m_calendar.end() && test.m_calendar.find(dt2.getSerial()) != test.m_calendar.end());
}

void testing_calendar::testIsHol() {
	calendar test;
	date dt1(1, 1, 2024);
	test.addHoliday(dt1);
	date dt2(25, 12, 2024);
	test.addHoliday(dt2);
	assert(test.isHoliday(dt1) && test.isHoliday(dt2));
}