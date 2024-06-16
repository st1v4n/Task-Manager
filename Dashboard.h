#pragma once
#include <iostream>
#include "Task.h"
#include "myVector.hpp"
class Dashboard
{
public:
	//this commands will mainly affect the myVector of tasks, because it has similar commands, whose execution is easy
	void setCurrentDate(const Date& newDate);
	const Date& getCurrentDate() const;
	void addTask(const Task& newTask);
	size_t getSize() const;
	const Task& getElement(int index) const;
	Task& updateElement(int index);
	void deleteElement(int index);
private:
	//each dashboard is a wrapper class for a myVector of tasks and a current Date, which helps future calculations
	myVector<Task> tasks;
	Date currentDate = TASK_CONSTANTS::defaultDate;
};

