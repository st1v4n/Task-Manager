#pragma once
#include <iostream>
#include "User.h"
class Command {
public:
	virtual void execute(User& user) const = 0;
};
