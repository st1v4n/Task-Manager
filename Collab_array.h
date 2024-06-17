#pragma once
#include "Collaboration.h"
class Collab_array
{
public:
	void loadFromFile();
	void saveToFile() const;
private:
	myVector<Collaboration> collabs;
};

