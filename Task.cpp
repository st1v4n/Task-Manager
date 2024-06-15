#include "Task.h"

void Task::free()
{
	id = 0;
	delete[] name;
	name = nullptr;
	delete[] description;
	description = nullptr;
}

void Task::copyFrom(const Task& other)
{
	id = other.id;
	name = new char[strleng(other.name) + 1];
	strcopy(name, other.name);
	due_date = other.due_date;
	status = other.status;
	description = new char[strleng(other.description) + 1];
	strcopy(description, other.description);
}

void Task::moveFrom(Task&& other)
{
	this->id = other.id;
	other.id = 0;
	this->name = new char[strleng(other.name) + 1];
	strcopy(name, other.name);
	other.name = nullptr;
	this->due_date = other.due_date;
	this->status = other.status;
	other.status = Status::ON_HOLD;
	this->description = new char[strleng(other.description) + 1];
	strcopy(description, other.description);
	other.description = nullptr;
}

Task::Task(const Task& other)
{
	copyFrom(other);
}

Task& Task::operator=(const Task& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Task::Task(Task&& other) noexcept
{
	moveFrom(std::move(other));
}

Task& Task::operator=(Task&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Task::~Task() noexcept
{
	free();
}

Task::Task(int id, const char* name, const Date& due_date, Status status, const char* description)
{
	setId(id);
	setName(name);
	setDueDate(due_date);
	setStatus(status);
	setDescription(description);
}

int Task::getId() const
{
	return id;
}

const char* Task::getName() const
{
	return name;
}

const Date& Task::getDueDate() const
{
	return due_date.getValue();
}

Status Task::getStatus() const
{
	return status;
}

char* Task::convertStatusToString() const
{
	char* buff = nullptr;
	int statusValue = (int)status;
	switch (statusValue) {
	case (int)Status::ON_HOLD:buff = new char[strleng("ON_HOLD") + 1];strcopy(buff, "ON_HOLD");break;
	case (int)Status::IN_PROCESS:buff = new char[strleng("IN_PROCESS") + 1];strcopy(buff, "IN_PROCESS");break;
	case (int)Status::DONE:buff = new char[strleng("DONE") + 1];strcopy(buff, "DONE");break;
	case (int)Status::OVERDUE:buff = new char[strleng("OVERDUE") + 1];strcopy(buff, "OVERDUE");break;
	default: throw std::out_of_range("Unknown Status!");
	}
	return buff;
}

const char* Task::getDescription() const
{
	return description;
}

void Task::setId(int id)
{
	if (id < 0)throw std::out_of_range("Only positive id allowed!");
	this->id = id;
}

void Task::setName(const char* name)
{
	if (!name)throw std::logic_error("Nullptr not allowed!");
	this->name = new char[strleng(name) + 1];
	strcopy(this->name, name);
}

void Task::setDueDate(const Date& date)
{
	due_date.setValue(date);
}

void Task::setStatus(Status status)
{
	this->status = status;
}

void Task::setDescription(const char* description)
{
	if (!description)throw std::logic_error("Nullptr not allowed!");
	this->description = new char[strleng(description) + 1];
	strcopy(this->description, description);
}

void Task::print(std::ostream& os, const Date& currentDate) const
{
	bool is_duedate_set = due_date.isValueSet();
	os << TASK_CONSTANTS::border << '\n';
	os << "ID: " << id << '\n';
	os << "Name: " << name << '\n';
	if (is_duedate_set) {
		os << "Due_date: " << due_date.getValue() << '\n';
	}
	char* statusString = convertStatusToString();
	os << "Status: " << statusString << '\n';
	delete[] statusString;
	os << "Description: " << description << '\n';
	if (is_duedate_set) {
		os << "Remaining days: " << currentDate.getRemainingDays(due_date.getValue()) << '\n';
	}
	os << TASK_CONSTANTS::border << '\n';
}

