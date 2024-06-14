#pragma once
#include <iostream>
#include "Date.h"
#include "Optional.hpp"
#include "StringFunctions.h"
namespace TASK_CONSTANTS {
	const Date defaultDate(1, 1, 1);
	const char border[23] = "*--------------------*";
	//we will need a symbol to know if a task has a Due_date set (when we serialize to file)
	const char special_date_symbol = '#';
	const char separator = ' ';
}
enum class Status {
	ON_HOLD,
	IN_PROCESS,
	DONE,
	OVERDUE
};
class Task
{
public:
	Task() = default;
	Task(const Task& other);
	Task& operator=(const Task& other);
	Task(Task&& other) noexcept;
	Task& operator=(Task&& other) noexcept;
	~Task() noexcept;
	Task(int id, const char* name, const Date& due_date, Status status, const char* description);
	int getId() const;
	const char* getName() const;
	const Date& getDueDate() const;
	Status getStatus() const;
	char* convertStatusToString() const;
	const char* getDescription() const;
	void setId(int id);
	void setName(const char* name);
	void setDueDate(const Date& date);
	void setStatus(Status status);
	void setDescription(const char* description);
	//print function can work with different output streams
	void print(std::ostream& os, const Date& currentDate) const;
private:
	int id = 0;
	char* name = nullptr;
	Optional<Date> due_date;
	Status status = Status::ON_HOLD;
	char* description = nullptr;
	void free();
	void copyFrom(const Task& other);
	void moveFrom(Task&& other);
};

