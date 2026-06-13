#include "Menu.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

void localPause() { cout << "\nPress Enter to continue..."; cin.get(); }
void localShowError() { cout << "\nError: Critical operation or data files issue.\n"; }

Menu::Menu() {
    appActivities.push_back(make_unique<GentleExercise>());
    appActivities.push_back(make_unique<ArtsAndCrafts>());
    appActivities.push_back(make_unique<MusicAndSinging>());
    appActivities.push_back(make_unique<CognitiveStimulation>());
    appActivities.push_back(make_unique<ReadingAndWriting>());
    appActivities.push_back(make_unique<TherapeuticDance>());
    appActivities.push_back(make_unique<BoardGames>());
    appActivities.push_back(make_unique<SocialInteraction>());
    loggedID = ""; sessionRole = ' ';
}

bool Menu::loginProcedure() {
    string inputUser, inputPass; system(CLEAR);
    cout << "=================================================\n         Elder Care Authentication System        \n=================================================\n";
    cout << "Enter User ID (Code): "; getline(cin, inputUser);
    cout << "Enter Password: "; getline(cin, inputPass);
    if (inputUser == "A1234" && inputPass == "1234") { loggedID = "A1234"; sessionRole = 'A'; return true; }
    if (!inputUser.empty() && inputUser[0] == 'E') {
        ifstream fileReader("clients.txt", ios::in);
        string cCode, cFirst, cLast, cDOB, cAddr, cState, cCity, cZip, cPhone, cEmerg, cDate, cPass;
        while (getline(fileReader, cCode)) {
            if (cCode.empty()) continue;
            getline(fileReader, cFirst); getline(fileReader, cLast); getline(fileReader, cDOB);
            getline(fileReader, cAddr); getline(fileReader, cState); getline(fileReader, cCity);
            getline(fileReader, cZip); getline(fileReader, cPhone); getline(fileReader, cEmerg);
            getline(fileReader, cDate); getline(fileReader, cPass);
            if (cCode == inputUser && cPass == inputPass) { loggedID = cCode; sessionRole = 'E'; fileReader.close(); return true; }
        }
        fileReader.close();
    }
    if (!inputUser.empty() && inputUser[0] == 'T') {
        ifstream fileReader("employees.txt", ios::in);
        string tCode, tFirst, tLast, tDOB, tAddr, tState, tCity, tZip, tPhone, tAdmin, tRole, tPass;
        while (getline(fileReader, tCode)) {
            if (tCode.empty()) continue;
            getline(fileReader, tFirst); getline(fileReader, tLast); getline(fileReader, tDOB);
            getline(fileReader, tAddr); getline(fileReader, tState); getline(fileReader, tCity);
            getline(fileReader, tZip); getline(fileReader, tPhone); getline(fileReader, tAdmin);
            getline(fileReader, tRole); getline(fileReader, tPass);
            if (tCode == inputUser && tPass == inputPass) { loggedID = tCode; sessionRole = 'T'; fileReader.close(); return true; }
        }
        fileReader.close();
    }
    cout << "\nError: Access Denied. Invalid Code or Password.\n"; localPause(); return false;
}

void Menu::runSystem() {
    bool systemRunning = true;
    while (systemRunning) {
        loggedID = ""; sessionRole = ' '; system(CLEAR);
        cout << "=================================================\n         Elder Care Management System            \n=================================================\n";
        cout << "1. Access Portal (Login)\n2. Shutdown System\nSelect an option: ";
        string mainOption; getline(cin, mainOption);
        if (mainOption == "1") {
            if (loginProcedure()) {
                if (sessionRole == 'A') adminMenu();
                else if (sessionRole == 'E') clientMenu();
                else if (sessionRole == 'T') employeeMenu();
            }
        }
        else if (mainOption == "2") { cout << "\nShutting down system completely. Goodbye!\n"; systemRunning = false; }
        else { localShowError(); localPause(); }
    }
}

void Menu::adminMenu() {
    int option;
    do {
        system(CLEAR);
        cout << "=================================================\n   Elder Care Management System - ADMINISTRATOR  \n=================================================\n"
            << "1.  Register client\n2.  Register employee (Teacher)\n3.  Remove client\n4.  Remove employee\n"
            << "5.  Modify client\n6.  Modify employee\n7.  List all clients\n8.  List all employees\n"
            << "9.  Search client\n10. Search employee\n11. Enroll Client in Activity\n12. List Activities & Status\n13. Log Out\n"
            << "Select an option please: ";
        cin >> option; cin.ignore();
        switch (option) {
        case 1: registerClient(); break;
        case 2: registerEmployee(); break;
        case 3: removeClient(); break;
        case 4: removeEmployee(); break;
        case 5: modifyClient(); break;
        case 6: modifyEmployee(); break;
        case 7: listClients(); break;
        case 8: listEmployees(); break;
        case 9: searchClient(); break;
        case 10: searchEmployee(); break;
        case 11: enrollClient(); break;
        case 12: listActivities(); break;
        case 13: cout << "\nLogging out..." << endl; localPause(); break;
        default: localShowError(); localPause(); break;
        }
    } while (option != 13);
}

void Menu::clientMenu() {
    int option;
    do {
        system(CLEAR);
        cout << "=================================================\n      Elder Care Management System - CLIENT      \n=================================================\n"
            << "1. View My Personal Profile & Registered Classes\n2. Log Out\nSelect an option please: ";
        cin >> option; cin.ignore();
        switch (option) {
        case 1: clientOwnRecord(loggedID); break;
        case 2: cout << "\nLogging out..." << endl; localPause(); break;
        default: localShowError(); localPause(); break;
        }
    } while (option != 2);
}

void Menu::employeeMenu() {
    int option;
    do {
        system(CLEAR);
        cout << "=================================================\n     Elder Care Management System - EMPLOYEE     \n=================================================\n"
            << "1. View My Personal Profile & Teaching Assignment\n2. Log Out\nSelect an option please: ";
        cin >> option; cin.ignore();
        switch (option) {
        case 1: employeeOwnRecord(loggedID); break;
        case 2: cout << "\nLogging out..." << endl; localPause(); break;
        default: localShowError(); localPause(); break;
        }
    } while (option != 2);
}

void Menu::clientOwnRecord(const string& clientID) {
    ifstream fileReader("clients.txt", ios::in);
    if (fileReader.is_open()) {
        system(CLEAR); cout << "\t\t\t\t*** My Personal Profile ***\t\t\t\t\n\n";
        string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate);
            getline(fileReader, address); getline(fileReader, state); getline(fileReader, city);
            getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, emergencyPhoneNumber);
            getline(fileReader, currentDate); getline(fileReader, password);
            if (code == clientID) {
                Client(code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password).displayProfile();
                showClientEnrolledActivities(clientID); break;
            }
        }
        fileReader.close();
    }
    localPause();
}

void Menu::employeeOwnRecord(const string& employeeID) {
    ifstream fileReader("employees.txt", ios::in);
    if (fileReader.is_open()) {
        system(CLEAR); cout << "\t\t\t\t*** My Staff Profile ***\t\t\t\t\n\n";
        string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, idUserAdmin, idRole, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate);
            getline(fileReader, address); getline(fileReader, state); getline(fileReader, city);
            getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, idUserAdmin); getline(fileReader, idRole); getline(fileReader, password);
            if (code == employeeID) {
                Employee(code, firstName, lastName, phoneNumber, idUserAdmin, idRole, password).displayProfile();
                showEmployeeAssignedActivity(idRole); break;
            }
        }
        fileReader.close();
    }
    localPause();
}

void Menu::showClientEnrolledActivities(const string& clientID) {
    ifstream fileReader("enrollments.txt", ios::in);
    string eClient, eActivity; bool hasActivities = false;
    cout << "\n>>> Enrolled Activities and Schedules:\n";
    while (getline(fileReader, eClient)) {
        if (eClient.empty()) continue; getline(fileReader, eActivity);
        if (eClient == clientID) {
            for (const auto& activity : appActivities) {
                if (activity->getId() == eActivity) {
                    cout << "- " << *activity << "\n";
                    hasActivities = true;
                }
            }
        }
    }
    if (!hasActivities) cout << "[You are not currently enrolled in any activity]\n";
    fileReader.close();
}

void Menu::showEmployeeAssignedActivity(const string& actID) {
    cout << "\n>>> Assigned Teaching Activity Details:\n"; bool matched = false;
    for (const auto& activity : appActivities) {
        if (activity->getId() == actID) {
            cout << "Activity: " << activity->getName() << "\nDescription: " << activity->getDescription() << "\nSchedule: " << activity->getSchedule() << "\n";
            matched = true;
        }
    }
    if (!matched) cout << "[No formal teaching activity associated]\n";
}

string Menu::generateID(const string& filename, char prefix) {
    ifstream fileReader(filename, ios::in); string lastID = ""; string currentLine;
    if (!fileReader.is_open() || fileReader.peek() == ifstream::traits_type::eof()) return string(1, prefix) + "0001";
    while (getline(fileReader, currentLine)) {
        if (currentLine.empty()) continue; lastID = currentLine;
        for (int i = 0; i < 11; ++i) { string dummy; getline(fileReader, dummy); }
    }
    fileReader.close();
    if (lastID.length() < 2) return string(1, prefix) + "0001";
    try {
        int number = stoi(lastID.substr(1)); number++;
        stringstream ss; ss << prefix << setfill('0') << setw(4) << number; return ss.str();
    }
    catch (...) { return string(1, prefix) + "0001"; }
}

bool Menu::isActivityAssigned(const string& actID) {
    ifstream fileReader("employees.txt", ios::in);
    string tCode, tFirst, tLast, tDOB, tAddr, tState, tCity, tZip, tPhone, tAdmin, tRole, tPass;
    while (getline(fileReader, tCode)) {
        if (tCode.empty()) continue;
        getline(fileReader, tFirst); getline(fileReader, tLast); getline(fileReader, tDOB);
        getline(fileReader, tAddr); getline(fileReader, tState); getline(fileReader, tCity);
        getline(fileReader, tZip); getline(fileReader, tPhone); getline(fileReader, tAdmin);
        getline(fileReader, tRole); getline(fileReader, tPass);
        if (tRole == actID) { fileReader.close(); return true; }
    }
    fileReader.close(); return false;
}

int Menu::getActivityUserCount(const string& actID) {
    ifstream fileReader("enrollments.txt", ios::in); string eClient, eActivity; int count = 0;
    while (getline(fileReader, eClient)) {
        if (eClient.empty()) continue; getline(fileReader, eActivity);
        if (eActivity == actID) count++;
    }
    fileReader.close(); return count;
}

bool Menu::clientExists(const string& clientID) {
    ifstream fileReader("clients.txt", ios::in); string tempCode;
    while (getline(fileReader, tempCode)) {
        if (tempCode.empty()) continue;
        if (tempCode == clientID) { fileReader.close(); return true; }
        for (int i = 0; i < 11; ++i) { string dummy; getline(fileReader, dummy); }
    }
    fileReader.close(); return false;
}

void Menu::enrollClient() {
    system(CLEAR); cout << "\t\t\t\t*** Enroll Client in Activity ***\t\t\t\t\n\n";
    string clientCode, actChoice; cout << "Enter Client Code (e.g. E0001): "; getline(cin, clientCode);
    if (!clientExists(clientCode)) { cout << "\nError: Client not found.\n"; localPause(); return; }
    cout << "\nAvailable Activities:\n";
    for (const auto& activity : appActivities) { cout << activity->getId() << ". " << activity->getName() << " | Capacity: " << getActivityUserCount(activity->getId()) << "/20\n"; }
    cout << "\nEnter Activity ID (01-08): "; getline(cin, actChoice);
    bool validChoice = false; string chosenSchedule = "", chosenName = "";
    for (const auto& activity : appActivities) {
        if (actChoice == activity->getId()) { validChoice = true; chosenSchedule = activity->getSchedule(); chosenName = activity->getName(); }
    }
    if (!validChoice) { cout << "\nInvalid Activity ID.\n"; localPause(); return; }
    if (getActivityUserCount(actChoice) >= 20) { cout << "\nError: Capacity full.\n"; localPause(); return; }
    ifstream fileReader("enrollments.txt", ios::in); string eClient, eActivity; bool alreadyEnrolled = false, scheduleConflict = false; string conflictingName = "";
    while (getline(fileReader, eClient)) {
        if (eClient.empty()) continue; getline(fileReader, eActivity);
        if (eClient == clientCode) {
            if (eActivity == actChoice) alreadyEnrolled = true;
            for (const auto& activity : appActivities) { if (activity->getId() == eActivity && activity->getSchedule() == chosenSchedule) { scheduleConflict = true; conflictingName = activity->getName(); } }
        }
    }
    fileReader.close();
    if (alreadyEnrolled || scheduleConflict) { cout << "\n[CRITICAL ERROR]: Blocked. Already enrolled or Schedule conflict with: " << conflictingName << "\n"; localPause(); return; }
    ofstream fileOutput("enrollments.txt", ios::app);
    if (fileOutput.is_open()) { fileOutput << clientCode << endl << actChoice << endl; cout << "\nEnrolled successfully!\n"; }
    fileOutput.close(); localPause();
}

void Menu::listActivities() {
    system(CLEAR); cout << "\t\t\t\t*** System Activities & Status ***\t\t\t\t\n\n";
    for (const auto& activity : appActivities) {
        string teacherStatus = isActivityAssigned(activity->getId()) ? "Assigned" : "NO TEACHER";
        cout << "=========================================================\nActivity ID: " << activity->getId() << "\nName: " << activity->getName()
            << "\nSchedule: " << activity->getSchedule() << "\nTeacher Status: " << teacherStatus << "\nEnrolled Users: " << getActivityUserCount(activity->getId()) << " / 20\n";
    }
    cout << "=========================================================\n"; localPause();
}

void Menu::registerClient() {
    ofstream fileOutput("clients.txt", ios::app);
    if (fileOutput.is_open()) {
        string code = generateID("clients.txt", 'E'); string firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password;
        system(CLEAR); cout << "\t\t\t\t*** Register a Client ***\t\t\t\t\n\nAuto-generated Code: " << code << "\n\n";
        cout << "First name: "; getline(cin, firstName); cout << "Last name: "; getline(cin, lastName); cout << "DOB (DD/MM/YYYY): "; getline(cin, birthDate); cout << "Address: "; getline(cin, address);
        cout << "State: "; getline(cin, state); cout << "City: "; getline(cin, city); cout << "Postal code: "; getline(cin, postalCode); cout << "Phone: "; getline(cin, phoneNumber);
        cout << "Emergency phone: "; getline(cin, emergencyPhoneNumber); cout << "Reg Date: "; getline(cin, currentDate); cout << "Password: "; getline(cin, password);
        fileOutput << code << endl << firstName << endl << lastName << endl << birthDate << endl << address << endl << state << endl << city << endl << postalCode << endl << phoneNumber << endl << emergencyPhoneNumber << endl << currentDate << endl << password << endl;
        cout << "\nRegistration successful.\n";
    }
    else localShowError();
    fileOutput.close(); localPause();
}

void Menu::registerEmployee() {
    ofstream fileOutput("employees.txt", ios::app);
    if (fileOutput.is_open()) {
        string idRole; system(CLEAR); cout << "Select Activity (01-08):\n";
        for (const auto& activity : appActivities) cout << activity->getId() << ". " << activity->getName() << "\n";
        cout << "Choice: "; getline(cin, idRole);
        bool valid = false; for (const auto& activity : appActivities) if (idRole == activity->getId()) valid = true;
        if (!valid || isActivityAssigned(idRole)) { cout << "\nInvalid choice or activity already has a teacher.\n"; fileOutput.close(); localPause(); return; }
        string code = generateID("employees.txt", 'T'); string firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, password;
        cout << "\nAuto-generated Code: " << code << "\n\n";
        cout << "First name: "; getline(cin, firstName); cout << "Last name: "; getline(cin, lastName); cout << "DOB (DD/MM/YYYY): "; getline(cin, birthDate); cout << "Address: "; getline(cin, address);
        cout << "State: "; getline(cin, state); cout << "City: "; getline(cin, city); cout << "Postal code: "; getline(cin, postalCode); cout << "Phone: "; getline(cin, phoneNumber); cout << "Password: "; getline(cin, password);
        fileOutput << code << endl << firstName << endl << lastName << endl << birthDate << endl << address << endl << state << endl << city << endl << postalCode << endl << phoneNumber << endl << "A1234" << endl << idRole << endl << password << endl;
        cout << "\nTeacher registered successfully.\n";
    }
    else localShowError();
    fileOutput.close(); localPause();
}

void Menu::removeClient() {
    ifstream fileReader("clients.txt"); ofstream fileAuxiliary; bool found = false; string auxCode, response;
    if (fileReader.is_open()) {
        system(CLEAR); cout << "\t\t\t\t*** Remove a Client ***\t\t\t\t\n\n";
        if (fileReader.peek() == ifstream::traits_type::eof()) { fileReader.close(); localPause(); return; }
        fileAuxiliary.open("auxiliary.txt", ios::out); cout << "Enter code to remove: "; getline(cin, auxCode);
        string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate); getline(fileReader, address); getline(fileReader, state); getline(fileReader, city); getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, emergencyPhoneNumber); getline(fileReader, currentDate); getline(fileReader, password);
            if (auxCode == code) {
                found = true; Client(code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password).displayProfile();
                cout << "Confirm deletion (y/n)?: "; getline(cin, response);
                if (!(response == "y" || response == "Y")) { fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl << address << endl << state << endl << city << endl << postalCode << endl << phoneNumber << endl << emergencyPhoneNumber << endl << currentDate << endl << password << endl; }
            }
            else { fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl << address << endl << state << endl << city << endl << postalCode << endl << phoneNumber << endl << emergencyPhoneNumber << endl << currentDate << endl << password << endl; }
        }
        fileReader.close(); fileAuxiliary.close(); remove("clients.txt"); rename("auxiliary.txt", "clients.txt");
        if (found && (response == "y" || response == "Y")) {
            ifstream enrollReader("enrollments.txt"); ofstream enrollAux("enroll_aux.txt"); string eClient, eAct;
            while (getline(enrollReader, eClient)) { if (eClient.empty()) continue; getline(enrollReader, eAct); if (eClient != auxCode) enrollAux << eClient << endl << eAct << endl; }
            enrollReader.close(); enrollAux.close(); remove("enrollments.txt"); rename("enroll_aux.txt", "enrollments.txt"); cout << "\nClient data wiped cleanly.\n";
        }
    }
    else localShowError();
    localPause();
}

void Menu::removeEmployee() {
    ifstream fileReader("employees.txt"); ofstream fileAuxiliary; bool found = false; string auxCode, response;
    if (fileReader.is_open()) {
        system(CLEAR); if (fileReader.peek() == ifstream::traits_type::eof()) { fileReader.close(); localPause(); return; }
        fileAuxiliary.open("auxiliary.txt"); cout << "Enter employee code: "; getline(cin, auxCode);
        string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, idUserAdmin, idRole, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate); getline(fileReader, address); getline(fileReader, state); getline(fileReader, city); getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, idUserAdmin); getline(fileReader, idRole); getline(fileReader, password);
            if (auxCode == code) {
                found = true; Employee(code, firstName, lastName, phoneNumber, idUserAdmin, idRole, password).displayProfile();
                cout << "Remove (y/n)?: "; getline(cin, response);
                if (!(response == "y" || response == "Y")) { fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl << address << endl << state << endl << city << endl << postalCode << endl << phoneNumber << endl << idUserAdmin << endl << idRole << endl << password << endl; }
            }
            else { fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl << address << endl << state << endl << city << endl << postalCode << endl << phoneNumber << endl << idUserAdmin << endl << idRole << endl << password << endl; }
        }
        fileReader.close(); fileAuxiliary.close(); remove("employees.txt"); rename("auxiliary.txt", "employees.txt");
    }
    else localShowError();
    localPause();
}

void Menu::modifyClient() {
    ifstream fileReader("clients.txt"); ofstream fileAuxiliary; string auxCode;
    if (fileReader.is_open()) {
        fileAuxiliary.open("auxiliary.txt"); cout << "Enter client code to modify: "; getline(cin, auxCode);
        string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate); getline(fileReader, address); getline(fileReader, state); getline(fileReader, city); getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, emergencyPhoneNumber); getline(fileReader, currentDate); getline(fileReader, password);
            if (auxCode == code) { cout << "New First Name: "; getline(cin, firstName); cout << "New Last Name: "; getline(cin, lastName); cout << "New Password: "; getline(cin, password); }
            fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl << address << endl << state << endl << city << endl << postalCode << endl << phoneNumber << endl << emergencyPhoneNumber << endl << currentDate << endl << password << endl;
        }
        fileReader.close(); fileAuxiliary.close(); remove("clients.txt"); rename("auxiliary.txt", "clients.txt");
    }
    else localShowError();
    localPause();
}

void Menu::modifyEmployee() {
    ifstream fileReader("employees.txt"); ofstream fileAuxiliary; string auxCode;
    if (fileReader.is_open()) {
        fileAuxiliary.open("auxiliary.txt"); cout << "Enter employee code: "; getline(cin, auxCode);
        string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, idUserAdmin, idRole, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate); getline(fileReader, address); getline(fileReader, state); getline(fileReader, city); getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, idUserAdmin); getline(fileReader, idRole); getline(fileReader, password);
            if (auxCode == code) { cout << "New First Name: "; getline(cin, firstName); cout << "New Last Name: "; getline(cin, lastName); cout << "New Activity ID: "; getline(cin, idRole); cout << "New Password: "; getline(cin, password); }
            fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl << address << endl << state << endl << city << endl << postalCode << endl << phoneNumber << endl << idUserAdmin << endl << idRole << endl << password << endl;
        }
        fileReader.close(); fileAuxiliary.close(); remove("employees.txt"); rename("auxiliary.txt", "employees.txt");
    }
    else localShowError();
    localPause();
}

void Menu::listClients() {
    ifstream fileReader("clients.txt");
    if (fileReader.is_open()) {
        system(CLEAR); vector<unique_ptr<User>> users; string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate); getline(fileReader, address); getline(fileReader, state); getline(fileReader, city); getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, emergencyPhoneNumber); getline(fileReader, currentDate); getline(fileReader, password);
            users.push_back(make_unique<Client>(code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password));
        }
        fileReader.close();
        for (const auto& user : users) { user->displayProfile(); }
    }
    else localShowError();
    localPause();
}

void Menu::listEmployees() {
    ifstream fileReader("employees.txt");
    if (fileReader.is_open()) {
        system(CLEAR); vector<unique_ptr<User>> users; string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, idUserAdmin, idRole, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate); getline(fileReader, address); getline(fileReader, state); getline(fileReader, city); getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, idUserAdmin); getline(fileReader, idRole); getline(fileReader, password);
            users.push_back(make_unique<Employee>(code, firstName, lastName, phoneNumber, idUserAdmin, idRole, password));
        }
        fileReader.close();
        for (const auto& user : users) { user->displayProfile(); }
    }
    else localShowError();
    localPause();
}

void Menu::searchClient() {
    ifstream fileReader("clients.txt"); string auxCode; bool found = false;
    if (fileReader.is_open()) {
        cout << "Enter client code to search: "; getline(cin, auxCode);
        string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate); getline(fileReader, address); getline(fileReader, state); getline(fileReader, city); getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, emergencyPhoneNumber); getline(fileReader, currentDate); getline(fileReader, password);
            if (auxCode == code) { found = true; Client(code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, emergencyPhoneNumber, currentDate, password).displayProfile(); break; }
        }
        if (!found) cout << "\nNot found.\n"; fileReader.close();
    }
    else localShowError();
    localPause();
}

void Menu::searchEmployee() {
    ifstream fileReader("employees.txt"); string auxCode; bool found = false;
    if (fileReader.is_open()) {
        cout << "Enter employee code to search: "; getline(cin, auxCode);
        string code, firstName, lastName, birthDate, address, state, city, postalCode, phoneNumber, idUserAdmin, idRole, password;
        while (getline(fileReader, code)) {
            if (code.empty()) continue;
            getline(fileReader, firstName); getline(fileReader, lastName); getline(fileReader, birthDate); getline(fileReader, address); getline(fileReader, state); getline(fileReader, city); getline(fileReader, postalCode); getline(fileReader, phoneNumber); getline(fileReader, idUserAdmin); getline(fileReader, idRole); getline(fileReader, password);
            if (auxCode == code) { found = true; Employee(code, firstName, lastName, phoneNumber, idUserAdmin, idRole, password).displayProfile(); break; }
        }
        if (!found) cout << "\nNot found.\n"; fileReader.close();
    }
    else localShowError();
    localPause();
}