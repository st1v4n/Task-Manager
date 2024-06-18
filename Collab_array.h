#pragma once
#include "Collaboration.h"
class Collab_array
{
public:
	void loadFromFile();
	void saveToFile() const;
	void addCollab(const Collaboration& new_collab);
	void removeCollab(const char* name, User& currentUser);
private:
	myVector<Collaboration> collabs;
};

