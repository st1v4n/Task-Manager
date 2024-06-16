#pragma once
#include <iostream>
#include "AllCommands.h"
#include "Task.h"
//factory, returning pointers to the right classes 
Command* factory(const char* str) {
	if (!str) return nullptr;
	if (strcompare(str, "register")) {
		return new RegisterCommand;
	}
	else if (strcompare(str, "login")) {
		return new LoginCommand;
	}
	else if (strcompare(str, "add-task")) {
		return new AddTaskCommand;
	}
	else if (strcompare(str, "update-task-name")) {
		return new UpdateTaskNameCommand;
	}
	else if (strcompare(str, "update-task-description")) {
		return new UpdateTaskDescriptionCommand;
	}
	else if (strcompare(str, "start-task")) {
		return new StartTaskCommand;
	}
	else if (strcompare(str, "remove-task-from-dashboard")) {
		return new RemoveTaskDashboardCommand;
	}
	else if (strcompare(str, "add-task-to-dashboard")) {
		return new AddTaskDashboardCommand;
	}
	else if (strcompare(str, "delete-task")) {
		return new DeleteTaskCommand;
	}
	else if (strcompare(str, "get-task")) {
		return new GetTaskCommand;
	}
	else if (strcompare(str, "list-tasks")) {
		return new ListTasksCommand;
	}
	else if (strcompare(str, "list-completed-tasks")) {
		return new ListCompletedTasksCommand;
	}
	else if (strcompare(str, "list-dashboard")) {
		return new ListDashboardCommand;
	}
	else if (strcompare(str, "finish-task")) {
		return new FinishTaskCommand;
	}
	else if (strcompare(str, "logout")) {
		return new LogoutTaskCommand;
	}
	else if (strcompare(str, "exit")) {
		return new ExitCommand;
	}
	return nullptr;
}

