#pragma once
#include <iostream>
enum class Months {
    UNKNOWN,
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};
static bool isLeapYear(int32_t year)
{
    if (year % 4 == 0) {
        if (year % 400 == 0) {
            return true;
        }
        else if (year % 100 == 0) {
            return false;
        }
        return true;
    }
    return false;
}

static uint16_t getDays(uint16_t month, int32_t year)
{
    switch (month) {
    case (int)Months::JANUARY:
    case (int)Months::MARCH:
    case (int)Months::MAY:
    case (int)Months::JULY:
    case (int)Months::AUGUST:
    case (int)Months::OCTOBER:
    case (int)Months::DECEMBER: return 31;
    case (int)Months::APRIL:
    case (int)Months::JUNE:
    case (int)Months::SEPTEMBER:
    case (int)Months::NOVEMBER: return 30;
    case (int)Months::FEBRUARY: return isLeapYear(year) ? 29 : 28;
    }
    throw std::logic_error("Invalid month!");
}
