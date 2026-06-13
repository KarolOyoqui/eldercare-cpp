#pragma once
#ifndef MENU_H
#define MENU_H
#include <vector>

#include "Activity.h"
#include "User.h"
#include <memory>
#include <string>

class Menu {
private:
    std::unique_ptr<Activity> appActivities[8]; //Arrangement of the intelligent pointers of the asylum activities
    std::string loggedID; //Save the login code
    char sessionRole; //Save the role letter (A,E,C)

    std::string generateID(const std::string& filename, char prefix); // Read the.txt files and calculate the following ID (0001 to 0002)
    bool isActivityAssigned(const std::string& actID); // Check if a class already has a teacher
    int getActivityUserCount(const std::string& actID); // Count how many grandparents are enrolled in a class
    bool clientExists(const std::string& clientID); // //Verify that the code exists
    bool loginProcedure(); //Code and password screen
    void showClientEnrolledActivities(const std::string& clientID); //Shows the class the user is in
    void showEmployeeAssignedActivity(const std::string& actID); //Show what kind of class the teacher teaches.

public:
    Menu();
    void registerClient();
    void registerEmployee();
    void removeClient();
    void removeEmployee();
    void modifyClient();
    void modifyEmployee();
    void listClients();
    void listEmployees();
    void searchClient();
    void searchEmployee();
    void enrollClient();
    void listActivities();
    void clientOwnRecord(const std::string& clientID);
    void employeeOwnRecord(const std::string& employeeID);
    void runSystem();
    void adminMenu();
    void clientMenu();
    void employeeMenu();
};

#endif