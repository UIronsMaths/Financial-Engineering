#include"test_date.h"
#include<cassert>
#include<tuple>

void testing_date::testDate() {
	testDMYSerial();
	testSerialDMY();
	testValidDate();
	testDaysInMonth();
	testLeapCount();
	testGetDMY();
	testWeekday();
	testAdd();
	testBD();
	testOperator();
	std::cout << "All testcases passed." << std::endl;
}
void testing_date::testDMYSerial() {

	date test1(11, 2, 2024);
	assert(test1.getSerial() == 45333);

	date test2(11, 02, 2024);
	assert(test2.getSerial() == 45333);

	date test3(01, 01, 1900);
	assert(test3.getSerial() == 1);
}
void testing_date::testSerialDMY() {

	date test1(11, 2, 2024);
	unsigned int day = 0, month = 0, year = 0;
	test1.serial_to_DMY(test1.m_serial, day, month, year);
	assert(day == 11 && month == 2 && year == 2024);

	date test2(1, 1, 1900);
	day = 0, month = 0, year = 0;
	test2.serial_to_DMY(test2.m_serial, day, month, year);
	assert(day == 1 && month == 1 && year == 1900);
}
void testing_date::testValidDate() {

	date test(11, 2, 2024);
	assert(test.isValidDate(1, 1, 2024));
	assert(test.isValidDate(01, 01, 2024));
	assert(!test.isValidDate(1, 1, 02024));
	assert(test.isValidDate(1, 011, 2024));
	assert(test.isValidDate(001, 1, 2024));
	assert(!test.isValidDate(31, 12, 1899));
}
void testing_date::testDaysInMonth() {

	date test(11, 2, 2024);
	int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int res;
	for (int i = 1; i <= 12; i++) {
		res = test.getDaysInMonth(2001, i);
		assert(res == daysInMonth[i]);
	}
	//
	// Leap year
	//
	daysInMonth[2] = 29;
	for (int i = 1; i <= 12; i++) {
		res = test.getDaysInMonth(2020, i);
		assert(res == daysInMonth[i]);
	}
}
void testing_date::testLeapCount() {

	date test(11, 2, 2024);
	int res = test.countLeapYears(2000, 2020);
	assert(res == 6);
}
void testing_date::testGetDMY() {

	date test(11, 2, 2024);
	std::tuple<int, int, int> res = test.getDMY();
	assert(std::get<0>(res) == 11 && std::get<1>(res) == 2 && std::get<2>(res) == 2024);
}
void testing_date::testWeekday() {

	date test1(11, 2, 2024);
	assert(test1.weekday() == test1.Sunday);

	date test2(16, 2, 2024);
	assert(test2.weekday() == test2.Friday);

	date test3(1, 1, 1900);
	assert(test3.weekday() == test3.Monday);
}
void testing_date::testAdd() {

	date test1(11, 2, 2024);
	test1.addDays(1);
	std::tuple<int, int, int> res = test1.getDMY();
	assert(test1.m_serial == 45334 && std::get<0>(res) == 12 && test1.weekday() == test1.Monday);
	test1.addMonths(1);
	res = test1.getDMY();
	assert(std::get<1>(res) == 3 && std::get<0>(res) == 12);
	test1.addYears(1);
	res = test1.getDMY();
	assert(std::get<1>(res) == 3 && std::get<2>(res) == 2025);
}
void testing_date::testBD() {

	date test(16, 2, 2024);
	assert(test.isGBD());
	test.addBusinessDays(1);
	assert(test.isGBD() && test.weekday() == test.Monday);
}
void testing_date::testOperator() {

	date test1(15, 2, 2024);
	++test1;
	std::tuple<int, int, int> res = test1.getDMY();
	assert(std::get<0>(res) == 16);
	date test2(15, 2, 2024);
	assert(test1 != test2);
	date test3(15, 2, 2024);
	assert(test2 == test3);
	--test1;
	assert(test1 == test2 && test1 == test3);
	test1 += 7;
	res = test1.getDMY();
	assert(std::get<0>(res) == 22);
	test1 - 2;
	res = test1.getDMY();
	assert(std::get<0>(res) == 20);
	assert(test1 > test2 && test3 < test1);
}
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