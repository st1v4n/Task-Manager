#pragma once
#include <iostream>
#include "Collab_array.h"
class Collab_Command {
public:
	virtual void execute(Collab_array& collaborations, User& currentUser) const = 0;
};
