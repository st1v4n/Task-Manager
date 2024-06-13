//Project OOP
//Task Manager
//Author: Stivan Aleksandrov 3MI0600301
//Software Engineering, group 3 , course 1

//I am not going to use ctime or iomanip
#include <iostream>
#include "Task.h"
int main()
{
    Date currentDate(13, 05, 2027);
    Date date(17, 05, 2027);
    Task task(123, "homework", date, Status::IN_PROCESS, "Simple solutions");
    task.print(std::cout, currentDate);
}


