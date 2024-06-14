#pragma once
#include <iostream>
#include "StringFunctions.h"
//we will need a special symbol when we save a user to the database file
const char user_symbol = '@';
class User
{
public:
	User() = default;
	User(const User& other);
	User& operator=(const User& other);
	User(User&& other);
	User& operator=(User&& other);
	~User();
	User(const char* username, const char* password);
	const char* getUsername() const;
private:
	char* username = nullptr;
	char* password = nullptr;
	void free();
	void copyFrom(const User& other);
	void moveFrom(User&& other);
};

