#include "Collaboration.h"

Collaboration::Collaboration(const Collaboration& other)
{
	copyFrom(other);
}

Collaboration::Collaboration(Collaboration&& other) noexcept
{
	moveFrom(std::move(other));
}

Collaboration& Collaboration::operator=(const Collaboration& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Collaboration& Collaboration::operator=(Collaboration&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Collaboration::~Collaboration() noexcept
{
	free();
}

void Collaboration::setName(const char* name)
{
	if (!name)return;
	this->name = new char[strleng(name) + 1];
	strcopy(this->name, name);
}

void Collaboration::setId(int id)
{
	if (id < 0)return;
	this->id = id;
}

void Collaboration::setCreator(const User& creator)
{
	this->creator = creator;
}

void Collaboration::addWorker(const User& worker)
{
	workers.push_back(worker);
}

const char* Collaboration::getName() const
{
	return name;
}

int Collaboration::getId() const
{
	return id;
}

const User& Collaboration::getCreator() const
{
	return creator;
}

const User& Collaboration::getWorker(int index) const
{
	return workers[index];
}

void Collaboration::save(std::ofstream& ofs) const
{
	int lenName = strleng(name);
	ofs.write(name, lenName + 1);
	ofs.write((const char*)&id, sizeof(int));
	int lenCreator = strleng(creator.getUsername());
	ofs.write(creator.getUsername(), lenCreator + 1);
	size_t size = workers.getSize();
	for (int i = 0;i < size;i++) {
		ofs.write(workers[i].getUsername(), strleng(workers[i].getUsername()) + 1);
	}
}

void Collaboration::load(std::ifstream& ifs)
{
	char buffName[50];
	readStringFromFile(ifs, buffName);
	name = new char[strleng(buffName) + 1];
	strcopy(name, buffName);
	ifs.read((char*)&id, sizeof(int));
	char buff[50];
	readStringFromFile(ifs, buff);
	creator.setUsername(buff);
	while (ifs.peek() != TASK_CONSTANTS::separator) {
		char buffer[50];
		readStringFromFile(ifs, buffer);
		User current_user;
		current_user.setUsername(buffer);
		workers.push_back(current_user);
	}
	ifs.ignore();
}
void Collaboration::removeTasksByUser(User& user) {
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size; i++) {
		Task current_task = user.getTasks().getElement(i);
		size_t tasks_size = tasks.getSize();
		for (int j = 0;j < tasks_size;j++) {
			if (strcompare(current_task.getName(), tasks[j].getName())) {
				user.updateTasks().deleteElement(i);
			}
		}
	}
}
void Collaboration::deleteCollab(User& currentUser)
{
	if (currentUser == creator) {
		name = nullptr;
		removeTasksByUser(creator);
		size_t sizeWorkers = workers.getSize();
		for (int i = 0;i < sizeWorkers;i++) {
			User current_user = workers[i];
			removeTasksByUser(current_user);
		}
	}
	else {
		throw std::logic_error("Only creator can delete collab! \n");
	}
}

size_t Collaboration::getSizeWorkers() const
{
	return workers.getSize();
}

bool Collaboration::findUser(const char* username) const
{
	if (strcompare(username, creator.getUsername()))return true;
	size_t size = workers.getSize();
	for (int i = 0;i < size;i++) {
		if (strcompare(username, workers[i].getUsername())) {
			return true;
		}
	}
	return false;
}

void Collaboration::print() const
{
	std::cout << TASK_CONSTANTS::border << '\n';
	std::cout << "Collaboration name: " << name << '\n';
	std::cout << "Collaboration id: " << id << '\n';
	std::cout << "Creator: " << creator.getUsername() << '\n';
}

size_t Collaboration::getSizeTasks() const
{
	return tasks.getSize();
}

const Task& Collaboration::getTask(int index) const
{
	return tasks[index];
}

const User& Collaboration::getUser(const char* username)
{
	if (strcompare(username, creator.getUsername()))return creator;
	size_t size = workers.getSize();
	for (int i = 0;i < size;i++) {
		if (strcompare(username, workers[i].getUsername())) {
			return workers[i];
		}
	}
	throw std::logic_error("User not found! \n");
}

void Collaboration::free()
{
	delete[] name;
	name = nullptr;
	id = 0;
	creator.deleteUser();
	workers.clear();
}

void Collaboration::copyFrom(const Collaboration& other)
{
	name = new char[strleng(other.name) + 1];
	strcopy(name, other.name);
	id = other.id;
	creator = other.creator;
	workers = other.workers;
}

void Collaboration::moveFrom(Collaboration&& other)
{
	name = other.name;
	other.name = nullptr;
	id = other.id;
	other.id = 0;
	creator = other.creator;
	other.creator.deleteUser();
	workers = other.workers;
	other.workers.clear();
}
