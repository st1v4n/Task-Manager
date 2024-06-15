#pragma once
#include <iostream>
#include "AllCommands.h"
#include "Task.h"

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
	else if (strcompare(str, "list-tasks")) {
		return new ListTasksCommand;
	}
	return nullptr;
}

