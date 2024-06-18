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


	return nullptr;
}