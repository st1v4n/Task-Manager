#include "AllCommands.h"
int id = 1;
void RegisterCommand::execute(User& user) const
{
	//our register command will add to data.dat only the username and password of each user
	//their info (tasks) will be saved to different files according to their usernames
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
		//user_symbol is a special symbol defined by me to set a border between each user, so we can make the reading much easier
		ofs.write((const char*)&user_symbol, sizeof(char));
		ofs.write(username, strleng(username) + 1);
		ofs.write(password, strleng(password) + 1);
	}
	catch (std::exception& ex) {
		//if we had an invalid input in username or password
		std::cout << ex.what() << '\n';
		ofs.clear();
		return;
	}
	ofs.clear();
	ofs.close();
}
static void readData(char*& dest, std::ifstream& fs) {
	//all of this functions could be in other files, sorry
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
	while (symbol != date_separator && symbol != TASK_CONSTANTS::separator) {
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
Status stringToStatus(const char* str)
{
	//in the files we will actually save the status as a string and we have to parse it to Status type
	if (strcompare(str, "ON_HOLD"))return Status::ON_HOLD;
	else if (strcompare(str, "IN_PROCESS"))return Status::IN_PROCESS;
	else if (strcompare(str, "DONE"))return Status::DONE;
	else if (strcompare(str, "OVERDUE"))return Status::OVERDUE;
	return Status::ON_HOLD;
}
void LoginCommand::getInfo(User& user) const
{
	//every user will have a specific file for themselves
	//in that file we will save their tasks (all of them)
	char* fileName = strconcat(user.getUsername(), ".dat");
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) {
		std::cout << "No user data available! \n";
		delete[] fileName;
		return;
	}
	//we will call the array of tasks 'dashboard', because at first i didnt understand the rules and made a class Dashboard
	//the Dashboard from the rules is actually a part of all tasks (from a specific date)
	Dashboard dashboard;
	while (!ifs.eof()) {
		//kinda Introduction to Programming logic here, maybe I could create a new file to hide it better
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
	user.setTasks(dashboard);
	ifs.clear();
	ifs.close();
	delete[] fileName;
}
void LoginCommand::execute(User& user) const
{
	//login USERNAME PASSWORD
	//we search in the file data.dat for the username and password that were input
	//if we cannot find them, it means the user doesnt have a profile yet
	//but if we manage to find them, we load their Tasks
	//if they dont have any tasks, we will output a message
	std::ifstream ifs(dataFileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open())throw std::logic_error("Cannot open file!");
	char username[50];
	std::cin >> username;
	char password[50];
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
	//if we dont have such account yet
	throw std::logic_error("No such account in existance!");
}
static bool isDate(const char* data) {
	//checking if the input string is in date format DAY-MONTH-YEAR
	//we do that because the due_date is Optional
	int count = 0;
	while (*data) {
		if ((*data) == date_separator)count++;
		else if ((*data) < '0' || (*data) > '9')return false;
		data++;
	}
	return count == 2; // if we had the date_separator symbol 2 times
}
void AddTaskCommand::execute(User& user) const
{
	try {
		//add-task is a function that could skip the input of due_date
		//thats why we have to check the different scenarios of input
		//it creates a new task and inserts it into the tasks vector of the current user
		Task task;
		char name[256];
		std::cin >> name;
		char date[50];
		std::cin >> date;
		//because the due_date is optional
		if (!isDate(date)) {
			task.setDescription(date);
		}
		else {
			Date dateFormat = stringToDate(date);
			task.setDueDate(dateFormat);
			char description[256];
			std::cin >> description;
			task.setDescription(description);
		}
		task.setId(id);
		id++;
		task.setName(name);
		size_t size = user.getTasks().getSize();
		for (int i = 0;i < size;i++) {
			//checking if there are 2 tasks with the same name, because that is not allowed
			if (strcompare(user.getTasks().getElement(i).getName(), name)) {
				throw std::logic_error("Task already exists!");
			}
		}
		if (task.getDueDate() < user.getTasks().getCurrentDate())task.setStatus(Status::OVERDUE);
		user.updateTasks().addTask(task);
		std::cout << "Task added successfully! \n";
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
}

void ListTasksCommand::execute(User& user) const
{
	//this will print all the available tasks at the moment, but we have another function that prints only the Dashboard
	user.printAllTasks(std::cout);
}

void UpdateTaskNameCommand::execute(User& user) const
{
	int id;
	std::cin >> id;
	char name[50];
	std::cin >> name;
	if (!name) return;
	size_t taskSize = user.getTasks().getSize();
	for (int i = 0;i < taskSize;i++) {
		if (user.getTasks().getElement(i).getId() == id) {
			user.updateTasks().updateElement(i).setName(name);
			std::cout << "Updating task was successful! \n";
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}

void UpdateTaskDescriptionCommand::execute(User& user) const
{
	int id;
	std::cin >> id;
	char description[256];
	std::cin >> description;
	if (!description) return;
	size_t taskSize = user.getTasks().getSize();
	for (int i = 0;i < taskSize;i++) {
		if (user.getTasks().getElement(i).getId() == id) {
			user.updateTasks().updateElement(i).setDescription(description);
			std::cout << "Updating task was successful! \n";
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}

void StartTaskCommand::execute(User& user) const
{
	int id;
	std::cin >> id;
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).getId() == id) {
			user.updateTasks().updateElement(i).setStatus(Status::IN_PROCESS);
			std::cout << "Your task status has been set to IN_PROCESS! \n";
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}

