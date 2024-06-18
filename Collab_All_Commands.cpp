#include "Collab_All_Commands.h"

void AddCollab::execute(Collab_array& collab, User& currentUser) const
{
	char buff[50];
	std::cin >> buff;
	if (buff) {
		Collaboration new_collab;
		new_collab.setCreator(currentUser);
		new_collab.setName(buff);
		collab.addCollab(new_collab);
		std::cout << "Collaboration added successfully! \n";
		return;
	}
	std::cout << "Invalid name! \n";
}

void DeleteCollab::execute(Collab_array& collab, User& currentUser) const
{
	char buff[50];
	std::cin >> buff;
	try {
		collab.removeCollab(buff, currentUser);
		std::cout << "Collab deleted successfully! \n";
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
}
