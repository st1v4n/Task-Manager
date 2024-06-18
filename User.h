#pragma once
#include <iostream>
#include "StringFunctions.h"
#include "Dashboard.h"
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
	void setUsername(const char* newUsername);
	void setTasks(const Dashboard& tasks);
	//we have both constant and non-constant way of getting the tasks of the user
	//when we just want to see something, we will use the constant getter
	//when we want to change something, we will use the functions updateTasks
	const Dashboard& getTasks() const;
	Dashboard& updateTasks();
	//all tasks
	void printAllTasks(std::ostream& os) const;
	//a functions that will delete all the info of the user (logout command)
	void deleteUser();
	friend bool operator==(const User& user1, const User& user2);
private:
	char* username = nullptr;
	char* password = nullptr;
	//all the user tasks will be called Dashboard, but only those who got added with a command to the dashboard will be displayed as dashboard tasks
	Dashboard tasks;
	void free();
	void copyFrom(const User& other);
	void moveFrom(User&& other);
};

