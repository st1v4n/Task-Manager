#pragma once
#include <iostream>
#include <fstream>
#include "Command.h"
#include "User.h"
const char dataFileName[] = "data.dat";
class RegisterCommand : public Command {
	void execute(User& user) const override;
};
class LoginCommand : public Command {
	void getInfo(User& user) const;
	void execute(User& user) const override;
};
class AddTaskCommand : public Command {
	void execute(User& user) const override;
};
