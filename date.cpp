#include"date.h"

date::date(unsigned int day, unsigned int month, unsigned int year)
	:m_serial(DMY_to_serial(day, month, year))
{}
date::date(unsigned int numdays)
	:m_serial(numdays)
{}
int date::getSerial()
{
	return m_serial;
}
std::tuple<int, int, int> date::getDMY()
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
	serial_to_DMY(m_serial, day, month, year);
	return std::make_tuple(day, month, year);
}
void date::addDays(int days)
{
	m_serial += days;
}
void date::addMonths(int months)
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
	serial_to_DMY(m_serial, day, month, year);

	if (months < 0 && month <= unsigned int(abs(months))) {
		year -= abs(months) / 12;
		month += months % 12;
        if (month <= 0) {
            month += 12;
            year--;
        }
	}
	else if (months > 12) {
		year += months / 12;
		month += months % 12;
        if (month > 12) {
            month -= 12;
            year++;
        }
	}
	else {
		month += months;
	}
	m_serial = DMY_to_serial(day, month, year);

}
void date::addYears(int years)
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
	serial_to_DMY(m_serial, day, month, year);

	year += years;
	m_serial = DMY_to_serial(day, month, year);
}
int date::daysDiff(date dt)
{
	return m_serial - dt.getSerial();
}
date::Weekday date::weekday()
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
    serial_to_DMY(m_serial, day, month, year);

    // Zeller's Congruence algorithm
    if (month < 3) {
        month += 12;
        year--;
    }
    unsigned int k = year % 100;
    unsigned int j = year / 100;
    unsigned int dayOfWeek = (day + ((13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;

    // Adjust the result to match the Weekday enum values
    return static_cast<enum date::Weekday>(((dayOfWeek+5)%7)+1);
}
bool date::isGBD() {
    date::Weekday day = weekday();
    if (day == Sunday || day == Saturday) {
        return false;
    }
    else {
        return true;
    }
}
void date::rollToGBD() {
    while (!isGBD()) {
        m_serial++;
    }
}
void date::addBusinessDays(int days) {
    while (days != 0) {
        if (isGBD()) {
            m_serial++;
            days--;
        }
        else if (!isGBD()) {
            while (!isGBD()) {
                m_serial++;
            }
        }
    }
}
date date::operator++() {
    addDays(1);
    return *this;
}
bool date::operator!=(date dt) {
    return (m_serial != dt.m_serial);
}


int date::DMY_to_serial(int day, int month, int year) {
    // Check for valid input
    if (!isValidDate(day, month, year)) {
        std::cerr << "Invalid date input.\n";
        return -1;  // or any suitable error code
    }

    // Constants for date calculations
    const int daysInYear = 365;
    const int daysInLeapYear = 366;
    const int excelEpochYear = 1900;
    const int leapYearFrequency = 4;

    // Array to store the number of days in each month
    const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Calculate the number of days from 1900 to the input date
    int days = (year - excelEpochYear) * daysInYear + countLeapYears(excelEpochYear, year);

    // Add days for each month in the input year
    for (int i = 1; i < month; ++i) {
        days += daysInMonth[i];
    }

    // Add the day in the input month
    days += day;

    // Adjust for leap year if necessary
    if (isLeapYear(year) && month > 2) {
        days += 1;
    }

    return days;
}
void date::serial_to_DMY(int m_serial, unsigned int& day, unsigned int& month, unsigned int& year) {
    // Constants for date calculations
    const int daysInYear = 365;
    const int daysInLeapYear = 366;
    const int excelEpochYear = 1900;
    const int leapYearFrequency = 4;

    // Initial values
    day = 0;
    month = 1;
    year = excelEpochYear;

    // Handle special case for m_serial = 0 (Excel's epoch)
    if (m_serial == 0) {
        return;
    }

    // Calculate the number of days from 1900 to the adjusted input serial number
    int remainingDays = m_serial;

    // Determine the year
    while (remainingDays >= daysInYear) {
        int daysInThisYear = isLeapYear(year) || (year == excelEpochYear) ? daysInLeapYear : daysInYear;

        if (remainingDays >= daysInThisYear) {
            remainingDays -= daysInThisYear;
            year++;
        }
        else {
            break;
        }
    }

    // Determine the month and day
    for (int i = 1; i <= 12; ++i) {
        int daysInMonth = getDaysInMonth(year, i);

        if (remainingDays >= daysInMonth) {
            remainingDays -= daysInMonth;
            month++;
        }
        else {
            day += remainingDays;
            break;
        }
    }
}
bool date::isValidDate(int day, int month, int year) {
    // Basic checks for day, month, and year validity
    if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Additional checks for month-specific day validity
    if (month == 2) {
        if (isLeapYear(year)) {
            return day <= 29;
        }
        else {
            return day <= 28;
        }
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11)) {
        return day <= 30;
    }

    return true;
}
bool date::isLeapYear(int year) {
    // Check if a year is a leap year
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int date::countLeapYears(int startYear, int endYear) {
    // Count the number of leap years in the range [startYear, endYear]
    int count = 0;
    for (int year = startYear; year <= endYear; ++year) {
        if (isLeapYear(year)) {
            count++;
        }
    }
    return count;
}
int date::getDaysInMonth(int year, int month) {
    // Get the number of days in a specific month
    const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) {
        return 29; // February in a leap year
    }
    else {
        return daysInMonth[month];
    }
}