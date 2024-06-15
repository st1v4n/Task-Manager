#pragma once
#include <iostream>
#include <fstream>
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
	ifs.read((char*)&symbol, sizeof(char));
	while (symbol) {
		(*str) = symbol;
		str++;
		ifs.read((char*)&symbol, sizeof(char));
	}
	(*str) = '\0';
}
static int stringToInt(const char* str) {
	if (!str)return -1;
	int result=0;
	while (*str) {
		(result *= 10) += (*str) - '0';
		str++;
	}
	return result;
}
