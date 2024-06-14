#include "AllCommands.h"

void RegisterCommand::execute(User& user) const
{
	std::ofstream ofs(dataFileName, std::ios::binary | std::ios::out | std::ios::app);
	if(!ofs.is_open())throw std::logic_error("Cannot open file!");
	char username[50];
	std::cout << "Enter username: " << '\n' << '>';
	std::cin >> username;
	char password[50];
	std::cout << "Enter password: " << '\n' << '>';
	std::cin >> password;
	try {
		User newUser(username, password);
		user = newUser;
		ofs.write((const char*)&user_symbol, sizeof(char));
		ofs.write(username, strleng(username) + 1);
		ofs.write(password, strleng(password) + 1);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
		ofs.clear();
		return;
	}
	ofs.clear();
	ofs.close();
}
static void readData(char*& dest, std::ifstream& fs) {
	char buff[50]{ '\0' };
	int count = 0;
	char symbol;
	fs.read((char*)&symbol, sizeof(char));
	while (symbol) {
		if (fs.eof())return;
		buff[count++] = symbol;
		fs.read((char*)&symbol, sizeof(char));
	}
	dest = new char[strleng(buff) + 1];
	strcopy(dest, buff);
}
void LoginCommand::execute(User& user) const
{
	std::ifstream ifs(dataFileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open())throw std::logic_error("Cannot open file!");
	char username[50];
	std::cout << "Enter username: " << '\n' << '>';
	std::cin >> username;
	char password[50];
	std::cout << "Enter password: " << '\n' << '>';
	std::cin >> password;
	char symbol;
	while (!ifs.eof()) {
		ifs.read((char*)&symbol, sizeof(char));
		if (symbol == user_symbol) {
			char* potential_username = nullptr;
			readData(potential_username, ifs);
			if (strcompare(username, potential_username)) {
				char* potential_password = nullptr;
				readData(potential_password, ifs);
				if (strcompare(password, potential_password)) {
					std::cout << "Successful login!" << '\n';
					User newUser(username, password);
					user = newUser;
					delete[] potential_password;
					delete[] potential_username;
					return;
				}
				delete[] potential_password;
			}
			delete[] potential_username;
		}
	}
	//continue
	ifs.clear();
	ifs.close();
	throw std::logic_error("No such account in existance!");
}
