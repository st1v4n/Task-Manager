#pragma once
#include <iostream>
#include <fstream>
#include "Date.h"
// some functions related to strings (char*)
static size_t strleng(const char* str) {
	if (!str)return -1;
	size_t count = 0;
	while (*str) {
		count++;
		str++;
	}
	return count;
}
static bool strcompare(const char* str1, const char* str2) {
	if (!str1 || !str2)return false;
	while ((*str1) && (*str2)) {
		if ((*str1) != (*str2))return false;
		str1++;
		str2++;
	}
	return (*str1) == (*str2);
}
static void strcopy(char* dest, const char* source) {
	if (!dest || !source)return;
	while (*source) {
		(*dest) = (*source);
		dest++;
		source++;
	}
	(*dest) = '\0';
}
static char* strconcat(const char* str1, const char* str2) {
	if (!str1 || !str2)return nullptr;
	char* result = new char[strleng(str1) + strleng(str2) + 1];
	int count = 0;
	while (*str1) {
		result[count++] = (*str1);
		str1++;
	}
	while (*str2) {
		result[count++] = (*str2);
		str2++;
	}
	result[count] = '\0';
	return result;
}
static void readStringFromFile(std::ifstream& ifs, char* str) {
	char symbol;
	if (!ifs.eof()) {
		ifs.read((char*)&symbol, sizeof(char));
	}
	else {
		return;
	}
	while (symbol != '\0') {
		(*str) = symbol;
		str++;
		if (ifs.eof())return;
		ifs.read((char*)&symbol, sizeof(char));
	}
	(*str) = '\0';
}
static int stringToInt(const char* str) {
	if (!str)return -1;
	int result=0;
	int symbol_null = '0';
	while (*str) {
		(result *= 10) += (*str) - symbol_null;
		str++;
	}
	return result;
}
static Date stringToDate(const char* str) {
	try {
		//trimming the empty spaces
		while ((*str) == ' ')str++;
		int day = 0;
		while ((*str) != date_separator) {
			if ((*str) < '0' || (*str) > '9')throw std::logic_error("Unknown symbol! \n");
			(day *= 10) += (*str) - '0';
			str++;
		}
		str++;
		int month = 0;
		while ((*str) != date_separator) {
			if ((*str) < '0' || (*str) > '9')throw std::logic_error("Unknown symbol! \n");
			(month *= 10) += (*str) - '0';
			str++;
		}
		str++;
		int year = 0;
		while (*str) {
			if ((*str) < '0' || (*str) > '9')throw std::logic_error("Unknown symbol! \n");
			(year *= 10) += (*str) - '0';
			str++;
		}
		Date date(day, month, year);
		return date;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
		std::cout << "Setting the date to the default one (01-01-01) \n";
		Date default_date(1, 1, 1);
		return default_date;
	}
}
static int getCharsInInt(int number) {
	if (number == 0)return 1;
	int count = 0;
	while (number > 0) {
		count++;
		number /= 10;
	}
	return count;
}
static int getCharsInDate(const Date& date) {
	int count = 2; // for the - symbol that is seen twice in the Date
	count += getCharsInInt(date.getDay()) + getCharsInInt(date.getMonth()) + getCharsInInt(date.getYear());
	return count;
}
static const char* IntToString(int number) {
	size_t size = getCharsInInt(number);
	char* result = new char[size + 1] {'\0'};
	int count = size-1;
	if (number == 0) {
		(*result) = '0';
		return result;
	}
	while (number > 0) {
		char symbol = number % 10 + '0';
		result[count--] = symbol;
		number /= 10;
	}
	return result;
}
static char* dateToString(const Date& date) {
	char* result = new char[getCharsInDate(date) + 1] {'\0'};
	int day, month, year;
	day = date.getDay();
	month = date.getMonth();
	year = date.getYear();
	result = strconcat(result, IntToString(day));
	result = strconcat(result, "-");
	result = strconcat(result, IntToString(month));
	result = strconcat(result, "-");
	result = strconcat(result, IntToString(year));
	return result;
}
