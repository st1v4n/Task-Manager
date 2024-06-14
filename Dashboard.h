#pragma once
#include <iostream>
#include "Task.h"
#include "myVector.hpp"
#include "User.h"
class Dashboard
{
public:
	void setCurrentDate(const Date& newDate);
	const Date& getCurrentDate() const;
	void addTask(const Task& newTask);
private:
	myVector<Task> tasks;
	Date currentDate = TASK_CONSTANTS::defaultDate;
	User user;
};

