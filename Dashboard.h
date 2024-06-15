#pragma once
#include <iostream>
#include "Task.h"
#include "myVector.hpp"
class Dashboard
{
public:
	void setCurrentDate(const Date& newDate);
	const Date& getCurrentDate() const;
	void addTask(const Task& newTask);
	size_t getSize() const;
	const Task& getElement(int index) const;
private:
	myVector<Task> tasks;
	Date currentDate = TASK_CONSTANTS::defaultDate;
};

