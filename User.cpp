#include "User.h"

void User::free()
{
	delete[] username;
	username = nullptr;
	delete[] password;
	password = nullptr;
}

void User::copyFrom(const User& other)
{
	username = new char[strleng(other.username) + 1];
	strcopy(username, other.username);
	password = new char[strleng(other.password) + 1];
	strcopy(password, other.password);

}

void User::moveFrom(User&& other)
{
	username = other.username;
	other.username = nullptr;
	password = other.password;
	other.password = nullptr;
}

User::User(const User& other)
{
	copyFrom(other);
}

User& User::operator=(const User& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

User::User(User&& other)
{
	moveFrom(std::move(other));
}

User& User::operator=(User&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

User::~User()
{
	free();
}

User::User(const char* username, const char* password)
{
	if (!username || !password) throw std::logic_error("Nullptr not allowed!");
	this->username = new char[strleng(username) + 1];
	strcopy(this->username, username);
	this->password = new char[strleng(password) + 1];
	strcopy(this->password, password);
}

const char* User::getUsername() const
{
	return username;
}

void User::setDashboard(const Dashboard& dashboard)
{
	this->tasks = dashboard;
}

const Dashboard& User::getDashboard() const
{
	return tasks;
}
