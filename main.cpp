//
//  main.cpp
//  Attendance
//
//  Created by Chandler de Spirlet on 11/20/17.
//  Copyright © 2017 Chandler de Spirlet. All rights reserved.
//

#include <iostream>
#include "Functions.h"


int main(int argc, const char * argv[]) {
    addBBToArr();
    populateClasses();
    bool quit = false;
    while (!quit){
        printMenu();
        cout<<"Enter an option: ";
        string userIn;
        getline(cin, userIn);
        int intUserIn = stoi(userIn);
        switch (intUserIn) {
            case 1:{//Print all students and their class counts
                dumpStudents(true);
            }
                break;
            case 2:{//Search by name
                cout<<"Enter student's name as LastName, FirstName: ";
                string bb;
                getline(cin, bb);
                findStudent(bb);
            }
                break;
            case 3:{//Show only those with defficient classes
                printDeficientClasses();
            }
                break;
            case 4:{
                quit = true;
                cout<<"Goodbye!"<<endl;
            }
                break;
            default:{
                cout<<"User input not recognized."<<endl;
            }
                break;
        }
    }
    // printOutBlackBeltClasses();
    // printDeficientClasses();
    // return 0;
}
