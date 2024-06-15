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
class UpdateTaskCommand : public Command {
	virtual void execute(User& user) const = 0;
};
class UpdateTaskNameCommand : public UpdateTaskCommand {
	void execute(User& user) const override;
};
class UpdateTaskDescriptionCommand : public UpdateTaskCommand {
	void execute(User& user) const override;
};
class StartTaskCommand : public Command {
	void execute(User& user) const override;
};
class ListTasksCommand : public Command {
	void execute(User& user) const override;
};