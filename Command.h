#pragma once
#include <iostream>
#include "User.h"
//an abstact base class that will be inherited by all other commands
class Command {
public:
	virtual void execute(User& user) const = 0;
};
