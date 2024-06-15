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

size_t Dashboard::getSize() const
{
	return tasks.getSize();
}

const Task& Dashboard::getElement(int index) const
{
	return tasks[index];
}

Task& Dashboard::updateElement(int index)
{
	return tasks[index];
}

void Dashboard::deleteElement(int index)
{
	tasks.erase(index);
}
