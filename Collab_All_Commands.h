#pragma once
#include "Collab_Command.h"


class AddCollab : public Collab_Command {
	void execute(Collab_array& collab) const override;
};

