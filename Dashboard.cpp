#include "Dashboard.h"

void Dashboard::setCurrentDate(const Date& newDate)
{
	currentDate = newDate;
}

const Date& Dashboard::getCurrentDate() const
{
	return currentDate;
}

void Dashboard::addTask(const Task& newTask)
{
	tasks.push_back(newTask);
}
