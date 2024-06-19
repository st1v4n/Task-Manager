#pragma once
#include <iostream>
#include "User.h"
#include "Task.h"
class Collaboration
{
public:
	Collaboration() = default;
	Collaboration(const Collaboration& other);
	Collaboration(Collaboration&& other) noexcept;
	Collaboration& operator=(const Collaboration& other);
	Collaboration& operator=(Collaboration&& other) noexcept;
	~Collaboration() noexcept;
	void setName(const char* name);
	void setId(int id);
	void setCreator(const User& creator);
	void addWorker(const User& worker);
	const char* getName()const;
	int getId()const;
	const User& getCreator()const;
	const User& getWorker(int index)const;
	void save(std::ofstream& ofs) const;
	void load(std::ifstream& ifs);
	void deleteCollab(User& currentUser);
	size_t getSizeWorkers() const;
	bool findUser(const char* username) const;
	void print() const;
	size_t getSizeTasks() const;
	const Task& getTask(int index) const;
private:
	char* name = nullptr;
	int id = 0;
	User creator;
	myVector<User> workers;
	myVector<Task> tasks;
	void free();
	void copyFrom(const Collaboration& other);
	void moveFrom(Collaboration&& other);
	void removeTasksByUser(User& user);
};

