#include "Collab_All_Commands.h"
static int global_id = 10;
void AddCollab::execute(Collab_array& collab, User& currentUser) const
{
	char buff[50];
	std::cin >> buff;
	if (buff) {
		Collaboration new_collab;
		new_collab.setCreator(currentUser);
		new_collab.setName(buff);
		new_collab.setId(global_id);
		global_id++;
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

void ListCollab::execute(Collab_array& collab, User& currentUser) const
{
	std::cout << "Your collaborations: \n";
	size_t size = collab.getSize();
	for (int i = 0;i < size;i++) {
		Collaboration current_collab = collab.getCollab(i);
		if (current_collab.findUser(currentUser.getUsername())) {
			current_collab.print();
		}
	}
}

void AddUserCollab::execute(Collab_array& collab, User& currentUser) const
{
	char buff[50];
	std::cin >> buff;
	char username[50];
	std::cin >> username;
	if (buff && username) {
		size_t size = collab.getSize();
		for (int i = 0;i < size;i++) {
			try {
				Collaboration& current_collab = collab.findCollab(buff);
				if (!current_collab.findUser(username)) {
					User worker;
					worker.setUsername(username);
					current_collab.addWorker(worker);
					std::cout << "Added user successfully! \n";
					return;
				}
				else {
					std::cout << "User already in the collab! \n";
					return;
				}
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
				return;
			}
		}
	}
}

void ListTasksCollab::execute(Collab_array& collab, User& currentUser) const
{
	char buff[50];
	std::cin >> buff;
	if (buff) {
		try {
			Collaboration& current_collab = collab.findCollab(buff);
			size_t size = current_collab.getSizeTasks();
			for (int i = 0;i < size;i++) {
				current_collab.getTask(i).print(std::cout, currentUser.getTasks().getCurrentDate());
			}
		}
		catch (std::exception& ex) {
			std::cout << ex.what();
			return;
		}
	}
}

void AssignTaskCollab::execute(Collab_array& collab, User& currentUser) const
{
	char collab_name[50];
	std::cin >> collab_name;
	try {
		Collaboration current_collab = collab.findCollab(collab_name);
		char username[50];
		std::cin >> username;
		if (current_collab.findUser(username)) {
			User user = current_collab.getUser(username);
			Command* add = new AddTaskCommand;
			//we will use their files to add and save the assigned tasks
			//therefore we need to check if the currentUser is the one that gets the tasks
			if (user == currentUser) {
				add->execute(currentUser);
			}
			else {
				LoginCommand login;
				LogoutTaskCommand logout;
				login.getInfo(user);
				add->execute(user);
				logout.save(user);
			}
			delete add;
		}

	}
	catch (std::exception& ex) {
		std::cout << ex.what();
		return;
	}
}
