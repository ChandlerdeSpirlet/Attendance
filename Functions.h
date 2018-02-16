//
//  Functions.h
//  Attendance
//
//  Created by Chandler de Spirlet on 11/20/17.
//  Copyright © 2017 Chandler de Spirlet. All rights reserved.
//

#ifndef Functions_h
#define Functions_h
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

struct Student {//Create struct object for each student
    string name;
    int swatCount;
    int regularClassCount;
    int sparringClassCount;
    bool shortOnSwat;
    bool shortOnRegular;
    bool shortOnSparring;
};


string version = "1.8.1";
string releaseNotes = "Introduces a feature to adjust the number of classes required.";
string releaseDate = "16 February 2018";
string userName = "admin";

int swatNum = 16;
int sparNum = 10;
int regNum = 10;

bool checkUserName(string input){
    if (input == userName){
        return true;
    }
    return false;
}

void printMenu(){
    cout<<"======Black Belt Class Counts======"<<endl;
    cout<<"1: Print all black belts and class counts."<<endl;
    cout<<"2: Search by name."<<endl;
    cout<<"3. Show only black belts without enough classes."<<endl;
    cout<<"4. Show only black belts with enough classes."<<endl;
    cout<<"5. Change the number of classes required."<<endl;
    cout<<"6. Quit."<<endl;
}

vector<Student> bbList = {};//vector where struct is stored

void dumpStudents(bool checkStatus) {
    for (Student student : bbList) {
        cout << student.name << endl;
        cout << "\tSWAT:     " << student.swatCount;
        if (checkStatus && student.swatCount < swatNum) {
            cout << " *** " << (swatNum - student.swatCount) << " SWAT classes needed.";
        }
        cout << endl;
        cout << "\tRegular:  " << student.regularClassCount;
        if (checkStatus && student.regularClassCount < regNum) {
            cout << " *** " << (regNum - student.regularClassCount) << " Regular classes needed.";
        }
        cout << endl;
        cout << "\tSparring: " << student.sparringClassCount;
        if (checkStatus && student.sparringClassCount < sparNum) {
            cout << " *** " << (sparNum - student.sparringClassCount) << " Sparring classes needed.";
        }
        cout << endl;
    }
}

bool isEOL(char chr) { return(chr == '\r' || chr == '\n'); }

void initStudent(Student &student, const string &name) {
    student.name = name;
    student.name.erase(remove_if(student.name.begin(), student.name.end(), isEOL), student.name.end());
    student.regularClassCount = 0;
    student.swatCount = 0;
    student.sparringClassCount = 0;
    student.shortOnRegular = true;
    student.shortOnSparring = true;
    student.shortOnSwat = true;
}

void addBBToArr(){//Input for list of black belts. Works as expected.
    //cout<<"Enter the filename with the black belt names including the file type: ";
    string bbFileName = "bbList.txt";
    //string bbFileName;
    //getline(cin, bbFileName);
    string studentName;
    string line;
    ifstream inFile;
    inFile.open(bbFileName);
    if (inFile.is_open()){
        while (getline(inFile, line)){
            stringstream ss(line);
            getline(ss, studentName, '\n');
            Student student;
            initStudent(student, studentName);
            bbList.push_back(student);
        }
        inFile.close();
    }
    else{
        cout<<"Error 1: file unable to open."<<endl;
    }
}

void updateClassBool(Student &student){
    if (student.swatCount >= swatNum){
        student.shortOnSwat = false;
    }
    if (student.sparringClassCount >= sparNum){
        student.shortOnSparring = false;
    }
    if (student.regularClassCount >= regNum){
        student.shortOnRegular = false;
    }
}

void addClassHelper(Student &student, string &classType){//Checks to see what class type is being processed. Does not work as expected.
    classType.erase(remove(classType.begin(), classType.end(), ' '), classType.end());//Remove spaces for better comparison
    classType.erase(remove_if(classType.begin(), classType.end(), isEOL), classType.end());//Remove spaces for better comparison
    if (classType == "SWAT"){//checking class type
        //cout << "Add Class: " << classType << " to " << student.name << endl;
        student.swatCount++;//increment class count by one
    }
    else if ((classType == "Lvl3/Cond/BB/2ndSparring") ||
             (classType == "Lvl3/Cond/BBSparring") ||
             (classType == "Level3/Cond/BBSparring") ||
             (classType == "BlackBelt/2ndDegreeSparring") ||
             (classType == "Level3/ConditionalSparring") ||
             (classType == "Level2sparring") ||
             (classType == "Women'sSparringClinic")) {
        //cout << "Add Class: " << classType << " to " << student.name << endl;
        student.sparringClassCount++;
    }
    else if ((classType == "BlackBelt/2ndDegree") ||
             (classType == "Level1") ||
             (classType == "Level2") ||
             (classType == "Level1/Level2") ||
             (classType == "Level3/Conditional") ||
             (classType == "ConditionalBlackBelt") ||
             (classType == "Level2Exclusive") ||
             (classType == "Exclusive2/3") ||
             (classType == "Basic")){
        //cout << "Add Class: " << classType << " to " << student.name << endl;
        student.regularClassCount++;
    }
    else {
        cout << "Class: " << classType << " not handled." << endl;
    }
    updateClassBool(student);
}

string constructName(string first, string last){//Changes name to allow for comparison in class file. Works as expected.
    string final;
    last.erase(remove(last.begin(), last.end(), '\"'),last.end());
    first.erase(remove(first.begin(), first.end(), '\"'), first.end());
    final = last + "," + first;
    return final;
}

void populateClasses(){//Processing file with names and class types
    //cout<<"Enter the filename with the black belt visits including the class type: ";
    string classFileName = "report.csv";
    //string classFileName;
    //getline(cin, classFileName);
    string line;
    string studentNameFirst;
    string studentNameLast;
    string finalName;
    string lastName;
    string classType;
    ifstream inFile;
    inFile.open(classFileName);
    if(inFile.is_open()){
        while (getline(inFile, line)){
            stringstream ss(line);
            getline(ss, studentNameLast, ',');
            getline(ss, studentNameFirst, ',');
            finalName = constructName(studentNameFirst, studentNameLast);//constructs name.
            //            for (Student student : bbList) { // Readonly???
            for (auto it = bbList.begin(); it != bbList.end(); ++it) {
                Student &student = *it;
                
                if (finalName != lastName) {
                    lastName = finalName;
                    // cout << student.name << ": vs: " << finalName << endl;
                }
                if (student.name == finalName){//If value in vector is equal to name in class list
                    getline(ss, classType);
                    addClassHelper(student, classType);//increment class count according to class type
                }
            }
        }
        inFile.close();
    }
    else{
        cout<<"Error 2: file unable to open."<<endl;
    }
}

void printEnoughClasses(){
    for (Student student : bbList){
        if ((student.shortOnSparring == false) && (student.shortOnRegular == false) && (student.shortOnSwat == false)){
            cout << student.name << endl;
            cout<<"\tSWAT:     "<<student.swatCount<<endl;
            cout<<"\tRegular:  "<<student.regularClassCount;
            cout<<endl;
            cout<<"\tSparring: "<<student.sparringClassCount;
            cout<<endl;
        }
    }
}

void printDeficientClasses(){
    for (Student student : bbList){
        if ((student.shortOnSparring == true) || (student.shortOnRegular == true) || (student.shortOnSwat == true)){
            cout << student.name << endl;
            if (student.swatCount >= swatNum){
                cout<<"\tSWAT:     "<<student.swatCount<<endl;
            }
            else{
                cout << "\tSWAT:     " << student.swatCount;
                cout << " *** " << (swatNum - student.swatCount) << " SWAT classes needed.";
                cout << endl;
            }
            if (student.regularClassCount >= regNum){
                cout<<"\tRegular:  "<<student.regularClassCount;
                cout<<endl;
            }
            else{
                cout << "\tRegular:  " << student.regularClassCount;
                cout << " *** " << (regNum - student.regularClassCount) << " Regular classes needed.";
                cout << endl;
            }
            if (student.sparringClassCount >= sparNum){
                cout<<"\tSparring: "<<student.sparringClassCount;
                cout<<endl;
            }
            else{
                cout << "\tSparring: " << student.sparringClassCount;
                cout << " *** " << (sparNum - student.sparringClassCount) << " Sparring classes needed.";
                cout << endl;
            }
        }
    }
}

void findStudent(string name){
    for (Student x : bbList){
        if (x.name == name){
            cout << x.name << endl;
            cout << "\tSWAT:     " << x.swatCount<<endl;
            cout << "\tRegular:  " << x.regularClassCount<<endl;
            cout << "\tSparring: " << x.sparringClassCount<<endl;
        }
    }
}

int getch() {
    int ch;
    struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

string getpass(const char *prompt, bool show_asterisk=true)
{
    const char BACKSPACE=127;
    const char RETURN=10;
    string password;
    unsigned char ch=0;
    cout <<prompt<<endl;
    while((ch=getch())!=RETURN)
    {
        if(ch==BACKSPACE)
        {
            if(password.length()!=0)
            {
                if(show_asterisk){
                    cout <<"\b \b";
                }
                password.resize(password.length()-1);
            }
        }
        else
        {
            password+=ch;
            if(show_asterisk){
                cout <<'*';
            }
        }
    }
    cout<<endl;
    return password;
}

void getSecondaryMenu(){
    cout<<"1. View program info."<<endl;
    cout<<"2. Edit student counts."<<endl;
    cout<<"3. Quit."<<endl;
}

void printBugLog(){
    cout<<"ID - Status - Description"<<endl;
    cout<<"========================="<<endl;
    string bugList = "buglog.txt";
    string ID;
    string status;
    string description;
    string line;
    ifstream inFile;
    inFile.open(bugList);
    if (inFile.is_open()){
        while (getline(inFile, line)){
            stringstream ss(line);
            getline(ss, ID, ',');
            getline(ss, status, ',');
            getline(ss, description, ',');
            cout<<ID<<" - "<<status<<" - "<<description<<endl;
        }
        inFile.close();
    }
    else{
        cout<<"Error 4: file unable to open."<<endl;
    }
}

void getInfo(){
    cout<<"Version: "<<version<<endl;
    cout<<"Release notes: "<<releaseNotes<<endl;
    cout<<"Release date: "<<releaseDate<<endl;
    printBugLog();
}

Student* updateStudent(Student *temp){
    Student *tmp;
    tmp->swatCount = swatNum;
    tmp->regularClassCount = regNum;
    tmp->sparringClassCount = sparNum;
    tmp->shortOnSwat = false;
    tmp->shortOnSparring = false;
    tmp->shortOnRegular = false;
    temp = tmp;
    return temp;
}

bool findPerson(string name){
    Student *temp;
    bool worked = false;
    for (Student x : bbList){
        if (name == x.name){
            temp = &x;
            temp = updateStudent(temp);
            worked = true;
        }
    }
    return worked;
}
void updateNewClass(Student *student){
    if (student->swatCount >= swatNum){
        student->shortOnSwat = false;
    }
    if (student->sparringClassCount >= sparNum){
        student->shortOnSparring = false;
    }
    if (student->regularClassCount >= regNum){
        student->shortOnRegular = false;
    }
}

void updateClassReq(int swat, int reg, int spar){//b1176 - UNRESOLVED
    swatNum = swat;
    regNum = reg;
    sparNum = spar;
    for (Student x : bbList){
        updateNewClass(&x);
    }
    cout<<"Class count requirements have been successfully updated."<<endl;
}

#endif /* Functions_h */

