#include "Date.h"

Date::Date(uint16_t day, uint16_t month, int32_t year)
{
	setDate(day, month, year);
}

void Date::print() const
{
	std::cout << day << date_separator << month << date_separator << year << std::endl;
}

void Date::setDate(const Date& newDate)
{
	day = newDate.day;
	month = newDate.month;
	year = newDate.year;
}

void Date::setDate(uint16_t day, uint16_t month, int32_t year)
{
	if (month < (int)Months::JANUARY || month > (int)Months::DECEMBER)throw std::logic_error("Invalid month!");
	uint16_t maxDays = getDays(month, year);
	if (day < 1 || day > maxDays)throw std::logic_error("Invalid day!");
	this->day = day;
	this->month = month;
	this->year = year;

}

const Date& Date::getDate() const
{
	return *this;
}

uint16_t Date::getDay() const
{
	return day;
}

uint16_t Date::getMonth() const
{
	return month;
}

int32_t Date::getYear() const
{
	return year;
}

bool operator==(const Date& date1, const Date& date2)
{
	return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year);
}

bool operator<(const Date& date1, const Date& date2)
{
	//dont ask, will try to limit the usage of this function to minimum
	if (date1.year > date2.year)return false;
	else if (date1.year < date2.year)return true;
	else {
		if (date1.month > date2.month)return false;
		else if (date1.month < date2.month)return true;
		else {
			if (date1.day >= date2.day)return false;
			else return true;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	std::cout << date.day << date_separator << date.month << date_separator << date.year;
	return os;
}

uint16_t Date::getRemainingDays(const Date& end) const
{
	Date start(*this);
	if (end < start)return 0;
	uint16_t count = 0;
	uint16_t maxDays = getDays(start.month, start.year);
	while (!(start == end)) {
		start.day++;
		count++;
		if (start.day > maxDays) {
			start.month++;
			start.day = 1;
			if (start.month > (int)Months::DECEMBER) {
				start.year++;
				start.month = (int)Months::JANUARY;
			}
			maxDays = getDays(start.month, start.year);
		}
	}
	return count;
}


