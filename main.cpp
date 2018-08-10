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
    /*
    if (argc == 4){
        cout<<argv[0]<<" "<<argv[1]<<" "<<argv[2]<<" "<<argv[3]<<endl;
    }
    else{
        cout<<argc<<endl;
    }
     */
    addBBToArr("bbList.txt");
    populateClasses("report.csv");
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
            case 4:{//Show those with enough classes
                printEnoughClasses();
            }
                break;
            case 5:{//Update class counts
                int spar, reg, swat;
                string temp;
                cout<<"New number of SWATs: ";
                getline(cin, temp);
                swat = stoi(temp);
                cout<<"New number of regular classes: ";
                getline(cin, temp);
                reg = stoi(temp);
                cout<<"New number of sparring classes: ";
                getline(cin, temp);
                spar = stoi(temp);
                updateClassReq(swat, reg, spar);
            }
                break;
            case 6:{//Exit
                quit = true;
                cout<<"Goodbye!"<<endl;
            }
                break;
            case 7:{//Admin access
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
                    const char *correct_password = "password";
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
                        case 1:{//Bug log
                            getInfo();
                            printBugLog("buglog.txt");
                        }
                            break;
                        case 2:{//b1143 - RESOLVED
                            bool going;//Update to correct counts
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
                        case 3:{//Exit Admin Access
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
