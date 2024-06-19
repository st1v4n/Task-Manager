#pragma once
#include <iostream>
#include "Collab_All_Commands.h"


Collab_Command* factory_collab(const char* str) {
	if (!str)return nullptr;
	if (strcompare(str, "add-collaboration")) {
		return new AddCollab;
	}
	else if (strcompare(str, "delete-collaboration")) {
		return new DeleteCollab;
	}
	else if (strcompare(str, "list-collaborations")) {
		return new ListCollab;
	}
	else if (strcompare(str, "add-user")) {
		return new AddUserCollab;
	}

	else if (strcompare(str, "list-tasks")) {
		return new ListTasksCollab;
	}
	return nullptr;
}