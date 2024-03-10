#include"date.h"

date::date(const unsigned int& day, const unsigned int& month, const unsigned int& year)
	:m_serial(DMY_to_serial(day, month, year))
{}
date::date(const unsigned int& numdays)
	:m_serial(numdays)
{}
date::date(const date& other) :m_serial(other.m_serial) {}
int date::getSerial()const  
{
	return m_serial;
}
std::tuple<int, int, int> date::getDMY() const
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
	serial_to_DMY(m_serial, day, month, year);
	return std::make_tuple(day, month, year);
}
void date::addDays(const int& days)
{
	m_serial += days;
}
void date::addMonths(const int& months)
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
void date::addYears(const int& years)
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
	serial_to_DMY(m_serial, day, month, year);

	year += years;
	m_serial = DMY_to_serial(day, month, year);
}
int date::daysDiff(const date& dt) const  {
	return m_serial - dt.getSerial();
}
date::Weekday date::weekday() const {
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
bool date::isGBD() const {
    date::Weekday day = weekday();
    return !(day == Sunday || day == Saturday);
}
bool date::isGBD(const calendar& cal) const {
    date::Weekday day = weekday();
    return !((day == Sunday || day == Saturday) && (!cal.isHoliday(*this)));
}
void date::rollToGBD() {
    while (!isGBD()) {
        m_serial++;
    }
}
void date::rollToGBD(const calendar& cal){
    while (!isGBD(cal)) {
        m_serial++;
    }
}
void date::addBusinessDays(const int& days) {
    int dta = days;
    while (dta != 0) {
        if (isGBD()) {
            m_serial++;
            dta--;
        }
        else if (!isGBD()) {
            rollToGBD();
        }
    }
    //
    // Edge case: advance Friday by one business day.
    //
    if (!isGBD()) {
        rollToGBD();
    }
}
date& date::operator++() {
    m_serial += 1;
    return *this;
}
date& date::operator--() {
    m_serial -= 1;
    return *this;
}
date& date::operator+=(const int& days) {
    m_serial += days;
    return *this;
}
date& date::operator-(const int& days) {
    m_serial -= days;
    return *this;
}
int date::operator-(const date& dt) const {
    return m_serial - dt.m_serial;
}
bool date::operator!=(const date& dt) const {
    return (m_serial != dt.m_serial);
}
bool date::operator==(const date& dt) const {
    return (m_serial == dt.m_serial);
}
bool date::operator<(const date& dt) const {
    return (m_serial < dt.m_serial);
}
bool date::operator>(const date& dt) const {
    return m_serial > dt.m_serial;
}
std::ostream& operator<<(std::ostream& os, const date& dt) {
    std::tuple<int, int, int> tup = dt.getDMY();
    os << std::get<0>(tup) << "/";
    os << std::get<1>(tup) << "/";
    os << std::get<2>(tup);
    return os;
}
int date::DMY_to_serial(const int& day, const int& month, const int& year) const {
    // Check for valid input
    if (!isValidDate(day, month, year)) {
        throw std::invalid_argument("Invalid date input.");
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
void date::serial_to_DMY(const unsigned int m_serial, unsigned int& day, unsigned int& month, unsigned int& year) const {
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
bool date::isValidDate(const int& day, const int& month, const int& year) const  {
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
bool date::isLeapYear(const int& year) const {
    // Check if a year is a leap year
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int date::countLeapYears(const int& startYear, const int& endYear) const {
    // Count the number of leap years in the range [startYear, endYear]
    int count = 0;
    for (int year = startYear; year <= endYear; ++year) {
        if (isLeapYear(year)) {
            count++;
        }
    }
    return count;
}
int date::getDaysInMonth(const int& year, const int& month) const {
    // Get the number of days in a specific month
    const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) {
        return 29; // February in a leap year
    }
    else {
        return daysInMonth[month];
    }
}
void calendar::addHoliday(const date& dt) {
    m_calendar.insert(dt.getSerial());
}
bool calendar::isHoliday(const date& dt) const {
    return (m_calendar.find(dt.getSerial()) != m_calendar.end());
}