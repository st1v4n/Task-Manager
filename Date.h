#pragma once
#include <iostream>
#include "DateFunctions.h"
const char date_separator = '-';
class Date
{
public:
	Date() = default;
	Date(uint16_t day, uint16_t month, int32_t year);
	void print() const;
	void setDate(const Date& newDate);
	void setDate(uint16_t day, uint16_t month, int32_t year);
	const Date& getDate() const;
	uint16_t getDay() const;
	uint16_t getMonth() const;
	int32_t getYear() const;
	//we will define a functions that helps us calculate the number of days between two dates
	friend bool operator==(const Date& date1, const Date& date2);
	uint16_t getRemainingDays(const Date& end) const;
	friend std::ostream& operator<<(std::ostream& os, const Date& date);
private:
	//could be 8 bits but we have to works with chars this way
	uint16_t day = 1; //its from 1 to 31 at most
	uint16_t month = 1; // from 1 to 12
	int32_t year = 1;
};

