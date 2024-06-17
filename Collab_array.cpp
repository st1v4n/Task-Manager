#include "Collab_array.h"
static const char collab_file_name[20] = "collabs.dat";
void Collab_array::loadFromFile()
{
	std::ifstream ifs(collab_file_name, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) {
		std::cout << "No collaborations! \n";
		return;
	}
	while (!ifs.eof()) {
		Collaboration newCollab;
		newCollab.load(ifs);
		collabs.push_back(newCollab);
	}
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
		collabs[i].save(ofs);
	}
}
