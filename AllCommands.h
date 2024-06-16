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
class RemoveTaskDashboardCommand : public Command {
	void execute(User& user) const override;
};
class AddTaskDashboardCommand : public Command {
	void execute(User& user) const override;
};
class DeleteTaskCommand : public Command {
	void execute(User& user) const override;
};
class GetTaskCommand : public Command {
	void execute(User& user) const override;
};
class ListTasksCommand : public Command {
	void executeWithDate(User& user, const Date& input_date) const;
	void execute(User& user) const override;
};
class ListCompletedTasksCommand : public Command {
	void execute(User& user) const override;
};
// this will give information about all tasks that have been added to the dashboard or whose due_date is the same as the current date
class ListDashboardCommand : public Command {
	void execute(User& user) const override;
};
class FinishTaskCommand : public Command {
	void execute(User& user) const override;
};
class LogoutTaskCommand : public Command {
	void save(User& user) const;
public:
	void execute(User& user) const override;
};
class ExitCommand : public Command {
	void execute(User& user) const override;
};