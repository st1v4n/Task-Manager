#pragma once
#include "Collab_Command.h"
#include "AllCommands.h"

class AddCollab : public Collab_Command {
	void execute(Collab_array& collab, User& currentUser) const override;
};
class DeleteCollab : public Collab_Command {
	void execute(Collab_array& collab, User& currentUser) const override;
};
