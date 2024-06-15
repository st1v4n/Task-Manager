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
	return nullptr;
}

