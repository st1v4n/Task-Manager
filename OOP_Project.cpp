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
#include "Collab_Command.h"
#include "Factory_collab.h"
#include "Collab_array.h"
int main()
{
    //because we are not using ctime and iomanip, we will need a way to know the current date of the users
    User user;
    std::cout << "Enter your current Date (Format: DAY-MONTH-YEAR): ";
    char buff[100];
    std::cin >> buff;
    Date currentDate;
    //if the input date is invalid, we will have a default one set (01-01-01)
    try {
        currentDate = stringToDate(buff);
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << "Your date will be set to 01-01-01 \n";
    }
    //we have both constant and non-constant way to get the tasks of the user
    user.updateTasks().setCurrentDate(currentDate);
    std::cout << "Your current Account : GUEST \n Register or login in order to save your tasks! \n";
    Collab_array collaborations;
    collaborations.loadFromFile();
    while (true) {
        try {
            std::cout << "> ";
            char buff[30];
            std::cin >> buff;
            Command* command = factory(buff);
            Collab_Command* collab_command = factory_collab(buff);
            if (command != nullptr) {
                command->execute(user);
                //because if it was a login command, it creates a new dashboard, who has another current date set (by default)
                user.updateTasks().setCurrentDate(currentDate);
                delete command;
            }
            else if (collab_command != nullptr) {
                collab_command->execute(collaborations, user);
                user.updateTasks().setCurrentDate(currentDate);
                delete collab_command;
            }
            else {
                std::cout << "Invalid command! \n";
            }
        }
        catch (std::runtime_error& run_error) {
            std::cout << run_error.what() << std::endl;
            break;
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    collaborations.saveToFile();
}


