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
                printEnoughClasses();
            }
                break;
            case 5:{
                quit = true;
                cout<<"Goodbye!"<<endl;
            }
                break;
            case 6:{
                cout<<"Username: ";
                string userInput;
                getline(cin, userInput);
                bool worked = checkUserName(userInput);
                while (!worked){//b3166 - RESOLVED
                    cout<<"Username not recognized, try again."<<endl;
                    string secondAttempt;
                    getline(cin, secondAttempt);
                    cout<<"Username: ";
                    worked = checkUserName(secondAttempt);
                }
                bool correctPass = false;
                int passAttempt = 0;
                while (!correctPass){
                    const char *correct_password = "rootUser";
                    string password = getpass("Password: ",true); // Show asterisks
                    if (password == correct_password){
                        correctPass = true;
                    }
                    if ((password != correct_password) && (passAttempt < 4)){//b1166 - RESOLVED
                        cout <<"Incorrect password."<<endl;
                        passAttempt++;
                        cout<<"You have "<<4 - passAttempt<<" attempts remaining."<<endl;//b2166 - RESOLVED
                    }
                    if (passAttempt > 3){
                        worked = false;
                        quit = true;
                        correctPass = true;
                        cout<<"Too many attempts. Exiting program with error code 3."<<endl;
                    }
                }
                while (worked && correctPass){
                    getSecondaryMenu();
                    cout<<"Enter an option: ";
                    string userin;
                    getline(cin, userin);
                    int intuserin = stoi(userin);
                    switch (intuserin) {
                        case 1:{
                            getInfo();
                        }
                            break;
                        case 2:{//b1143 - RESOLVED
                            bool going;
                            cout<<"Enter the student's name: ";
                            string newName;
                            getline(cin, newName);
                            going = findPerson(newName);
                            if (going){
                                findStudent(newName);
                            }
                            else{
                                cout<<"Student not found."<<endl;
                            }
                        }
                            break;
                        case 3:{
                            worked = false;
                            cout<<"Exiting."<<endl;
                        }
                            break;
                        default:{
                            cout<<"User input not recognized."<<endl;
                        }
                            break;
                    }
                }
            }
                break;
            default:{
                cout<<"User input not recognized."<<endl;
            }
                break;
        }
    }
}

