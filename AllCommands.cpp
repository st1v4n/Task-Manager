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
static int parseStringToInt(char* data, std::ifstream& ifs) {
	char symbol;
	ifs.read((char*)&symbol, sizeof(char));
	while (symbol != date_separator) {
		(*data) = symbol;
		ifs.read((char*)&symbol, sizeof(char));
	}
	int dataInt = stringToInt(data);
	return dataInt;
}
static Date& getDateFromFile(std::ifstream& ifs) {
	char day[3]{'\0'};
	char month[3]{ '\0' };
	char year[5]{ '\0' };
	int dayInt = parseStringToInt(day, ifs);
	int monthInt = parseStringToInt(month, ifs);
	int yearInt = parseStringToInt(year, ifs);
	Date date(dayInt, monthInt, yearInt);
	return date;
}
void LoginCommand::getInfo(User& user) const
{
	//every user will have a specific file for themselves
	//in that file we will save their dashboard
	char* fileName = strconcat(user.getUsername(), ".dat");
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) {
		std::cout << "No user data available! \n";
		delete[] fileName;
		return;
	}
	Dashboard dashboard;
	while (!ifs.eof()) {
		Task task;
		int id;
		ifs.read((char*)&id, sizeof(int));
		ifs.ignore(); // for the separator
		task.setId(id);
		char name[256];
		readStringFromFile(ifs, name);
		ifs.ignore();
		task.setName(name);
		char symbol;
		ifs.read((char*)&symbol, sizeof(char));
		if (symbol == TASK_CONSTANTS::special_date_symbol) {
			ifs.ignore();
			Date date = getDateFromFile(ifs);
			ifs.ignore();
			task.setDueDate(date);
		}
		char status[20];
		readStringFromFile(ifs, status);
		Status stat = stringToStatus(status);
		ifs.ignore();
		task.setStatus(stat);
		char description[256];
		readStringFromFile(ifs, description);
		ifs.ignore();
		task.setDescription(description);
		dashboard.addTask(task);
	}
	user.setDashboard(dashboard);
	ifs.clear();
	ifs.close();
	delete[] fileName;
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
					ifs.clear();
					ifs.close();
					getInfo(user);
					return;
				}
				delete[] potential_password;
			}
			delete[] potential_username;
		}
	}
	ifs.clear();
	ifs.close();
	throw std::logic_error("No such account in existance!");
}
