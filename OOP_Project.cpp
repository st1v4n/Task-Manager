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
#include "Factory.h"
int main()
{
    User user;
    while (true) {
        try {
            char buff[30];
            std::cin >> buff;
            Command* command = factory(buff);
            if (command != nullptr) {
                command->execute(user);
                delete command;
            }
            else {
                std::cout << "Invalid command! \n";
            }
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
}


