//Project OOP
//Task Manager
//Author: Stivan Aleksandrov 3MI0600301
//Software Engineering, group 3 , course 1

//I am not going to use ctime or iomanip
#include <iostream>
#include <fstream>
#include "Task.h"
#include "User.h"
#include "Command.h"
#include "AllCommands.h"
int main()
{
    User user;
    try {
        Command* com = new LoginCommand;
        com->execute(user);
        delete com;
    }
    catch (std::exception& ex) {
        std::cout << ex.what();
    }
}


