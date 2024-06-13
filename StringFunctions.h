#pragma once
#include <iostream>

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
