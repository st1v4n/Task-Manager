//this will be the longest file because it containts all the available commands
//another solution could be each of the commands having a different file
#include "AllCommands.h"
int globalId = 1;
void RegisterCommand::execute(User& user) const
{
	//our register command will add to data.dat only the username and password of each user
	//their info (tasks) will be saved to different files according to their usernames
	globalId = 1;
	std::ofstream ofs(dataFileName, std::ios::binary | std::ios::out | std::ios::app);
	if(!ofs.is_open())throw std::logic_error("Cannot open file!");
	char username[50];
	std::cin >> username;
	char password[50];
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
	std::cout << "Registered successfully! \n";
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
	int count = 0;
	ifs.read((char*)&symbol, sizeof(char));
	while (symbol != date_separator && symbol != TASK_CONSTANTS::separator) {
		data[count++] = symbol;
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
	while (ifs.peek() != eof_symbol) {
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
			Date date = getDateFromFile(ifs);
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
		globalId++;
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
	//trimming the string, removing the symbol ' '
	while ((*data) == ' ')data++;
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
			std::cin.getline(description,256);
			task.setDescription(description);
			if (task.getDueDate() < user.getTasks().getCurrentDate())task.setStatus(Status::OVERDUE);
		}
		task.setId(globalId);
		globalId++;
		task.setName(name);
		size_t size = user.getTasks().getSize();
		for (int i = 0;i < size;i++) {
			//checking if there are 2 tasks with the same name, because that is not allowed
			if (strcompare(user.getTasks().getElement(i).getName(), name) && user.getTasks().getElement(i).getDueDate() == task.getDueDate()) {
				throw std::logic_error("Task already exists!");
			}
		}
		user.updateTasks().addTask(task);
		std::cout << "Task added successfully! \n";
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
}

void UpdateTaskNameCommand::execute(User& user) const
{
	//inserting the id and name, of course checking if the name is valid
	//both update-task commands will inherit the class UpdateTaskCommand, because they work similarly
	int id;
	std::cin >> id;
	char name[50];
	std::cin >> name;
	if (!name) return;
	size_t taskSize = user.getTasks().getSize();
	for (int i = 0;i < taskSize;i++) {
		if (user.getTasks().getElement(i).getId() == id) {
			//if we manage to find that specific id, we set the name, else we just output a good response
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
	//setting the status to IN_PROCESS
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

void RemoveTaskDashboardCommand::execute(User& user) const
{
	//we have a special bool variable in every task that indicates whether the task has been added to a dashboard
	int id;
	std::cin >> id;
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).getId() == id) {
			user.updateTasks().updateElement(i).setAdded(false);
			std::cout << "Removed from the dashboard successfully! \n";
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}

void AddTaskDashboardCommand::execute(User& user) const
{
	int id;
	std::cin >> id;
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).getId() == id && user.getTasks().getElement(i).getStatus()!=Status::OVERDUE) {
			user.updateTasks().updateElement(i).setAdded(true);
			std::cout << "Added to the dashboard successfully! \n";
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}

void DeleteTaskCommand::execute(User& user) const
{
	//since the tasks are stored in a myVector class, deleting will be simple, because we just erase that element at certain index
	int id;
	std::cin >> id;
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).getId() == id) {
			user.updateTasks().deleteElement(i);
			std::cout << "Deleted successfully! \n";
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}
static void getByName(User& user, const char* name) {
	//maybe in the class
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (strcompare(user.getTasks().getElement(i).getName(),name)) {
			user.getTasks().getElement(i).print(std::cout, user.getTasks().getCurrentDate());
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}
static bool isNumber(const char* buff) {
	//maybe in the stringFunctions file
	if (!buff)return false;
	while (*buff) {
		if ((*buff) < '0' || (*buff) > '9') {
			return false;
		}
		buff++;
	}
	return true;
}
void GetTaskCommand::execute(User& user) const
{
	char buff[50];
    std::cin >> buff;
	//we can get this command with id or name
	//we have to check if the data that was input is an id
	//if it contains atleast one symbol that is not from [0 to 9], then its not a id for sure 
	if (!isNumber(buff)) {
		getByName(user, buff);
		return;
	}
	int id = stringToInt(buff);
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).getId() == id) {
			user.getTasks().getElement(i).print(std::cout,user.getTasks().getCurrentDate());
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}

void ListTasksCommand::executeWithDate(User& user, const Date& input_date) const
{
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).isDueDateSet() && user.getTasks().getElement(i).getDueDate() == input_date) {
			user.getTasks().getElement(i).print(std::cout, user.getTasks().getCurrentDate());
		}
	}
}

void ListTasksCommand::execute(User& user) const
{
	//we have two functions of list-task
	//if the user inputs a date, we will execute the date one
	char buff[20];
	std::cin.getline(buff,20);
	if (buff != nullptr && !strcompare(buff, "")) {
		if (isDate(buff)) {
			Date input_date = stringToDate(buff);
			executeWithDate(user, input_date);
			return;
		}
		else {
			std::cout << "Invalid input! \n";
			return;
		}
	}
	//this will print all the available tasks at the moment, but we have another function that prints only the Dashboard
	user.printAllTasks(std::cout);
}

void ListCompletedTasksCommand::execute(User& user) const
{
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).getStatus() == Status::DONE) {
			user.getTasks().getElement(i).print(std::cout, user.getTasks().getCurrentDate());
		}
	}
}

void ListDashboardCommand::execute(User& user) const
{
	//this will print all the tasks that were either added to the dashboard or have the same due_date as the current date
	Date current_date = user.getTasks().getCurrentDate();
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).getDueDate() == current_date || user.getTasks().getElement(i).isAddedToDashboard()) {
			user.getTasks().getElement(i).print(std::cout, user.getTasks().getCurrentDate());
		}
	}
}

void FinishTaskCommand::execute(User& user) const
{
	//setting the status to DONE
	int id;
	std::cin >> id;
	size_t size = user.getTasks().getSize();
	for (int i = 0;i < size;i++) {
		if (user.getTasks().getElement(i).getId() == id) {
			user.updateTasks().updateElement(i).setStatus(Status::DONE);
			std::cout << "Your task status has been set to DONE! \n";
			return;
		}
	}
	std::cout << "Couldnt find that task! \n";
}

void LogoutTaskCommand::save(User& user) const
{
	size_t size = user.getTasks().getSize();
	if (size != 0) {
		char* fileName = strconcat(user.getUsername(), ".dat");
		std::ofstream ofs(fileName, std::ios::binary | std::ios::out);
		if (!ofs.is_open()) {
			std::cout << "Cannot open file for writing! \n";
			return;
		}
		for (int i = 0;i < size;i++) {
			Task current_task = user.getTasks().getElement(i);
			int id = current_task.getId();
			ofs.write((const char*)&id, sizeof(int));
			ofs.write((const char*)&TASK_CONSTANTS::separator, sizeof(char));
			int lenName = strleng(current_task.getName());
			ofs.write(current_task.getName(), lenName + 1);
			ofs.write((const char*)&TASK_CONSTANTS::separator, sizeof(char));
			if (current_task.isDueDateSet()) {
				ofs.write((const char*)&TASK_CONSTANTS::special_date_symbol, sizeof(char));
				char* date = dateToString(current_task.getDueDate());
				size_t size = strleng(date);
				ofs.write(date, size); // we will need no '\0' at the end 
				delete[] date;
			}
			ofs.write((const char*)&TASK_CONSTANTS::separator, sizeof(char));
			char* status = current_task.convertStatusToString();
			size_t sizeStatus = strleng(status);
			ofs.write(status, sizeStatus + 1);
			delete[] status;
			ofs.write((const char*)&TASK_CONSTANTS::separator, sizeof(char));
			ofs.write(current_task.getDescription(), strleng(current_task.getDescription()) + 1);
			ofs.write((const char*)&TASK_CONSTANTS::separator, sizeof(char));
			if (i == size - 1) {
				ofs.write((const char*)&eof_symbol, sizeof(char));
			}
		}

		delete[] fileName;
		ofs.clear();
		ofs.close();
	}
}

void LogoutTaskCommand::execute(User& user) const
{
	save(user);
	user.deleteUser();
	std::cout << "Logged out successfully! \n";
	std::cout << "Your current Account : GUEST \n Register or login in order to save your tasks! \n";
}

void ExitCommand::execute(User& user) const
{
	if (user.getUsername() != nullptr) {
		LogoutTaskCommand logout;
		logout.execute(user);
	}
	throw std::runtime_error("Exiting from the program!");
}
