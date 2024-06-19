#include "Collab_array.h"
static const char collab_file_name[20] = "collabs.dat";
static const char eof_symbol = '$';
void Collab_array::loadFromFile()
{
	std::ifstream ifs(collab_file_name, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) {
		std::cout << "No collaborations! \n";
		return;
	}
	//for some reason the eof bit does not seem to work and completely destroys my file
	//so i will save a new special symbol that indicates the end of the file!!!!
	while (ifs.peek()!= eof_symbol) {
		Collaboration newCollab;
		newCollab.load(ifs);
		collabs.push_back(newCollab);
	}
	ifs.clear();
	ifs.close();
}
void Collab_array::saveToFile() const
{
	std::ofstream ofs(collab_file_name, std::ios::binary | std::ios::out);
	if (!ofs.is_open()) {
		std::cout << "Failed to save collabs! \n";
		return;
	}
	size_t size = collabs.getSize();
	for (int i = 0;i < size;i++) {
		if (collabs[i].getName() != nullptr) {
			collabs[i].save(ofs);
			ofs.write((const char*)&TASK_CONSTANTS::separator, sizeof(char));
		}
	}
	ofs.write((const char*)&eof_symbol, sizeof(char));
	ofs.clear();
	ofs.close();
}

void Collab_array::addCollab(const Collaboration& new_collab)
{
	collabs.push_back(new_collab);
}

void Collab_array::removeCollab(const char* name, User& currentUser)
{
	size_t size = collabs.getSize();
	for (int i = 0;i < size;i++) {
		if (strcompare(collabs[i].getName(), name)) {
			collabs[i].deleteCollab(currentUser);
			return;
		}
	}
	throw std::logic_error("Collab not found!");
}

size_t Collab_array::getSize() const
{
	return collabs.getSize();
}

const Collaboration& Collab_array::getCollab(int index) const
{
	return collabs[index];
}

Collaboration& Collab_array::findCollab(const char* collabName)
{
	size_t size = collabs.getSize();
	for (int i = 0;i < size;i++) {
		if (strcompare(collabName, collabs[i].getName())) {
			return collabs[i];
		}
	}
	throw std::logic_error("Collaboration doesnt exist! \n");
}
