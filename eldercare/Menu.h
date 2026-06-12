#pragma once
#ifndef MENU_H
#define MENU_H

#include "Activity.h"
#include "User.h"
#include <memory>
#include <string>

class Menu {
private:
    std::unique_ptr<Activity> appActivities[8];
    std::string loggedID;
    char sessionRole;

    std::string generateID(const std::string& filename, char prefix);
    bool isActivityAssigned(const std::string& actID);
    int getActivityUserCount(const std::string& actID);
    bool clientExists(const std::string& clientID);
    bool loginProcedure();
    void showClientEnrolledActivities(const std::string& clientID);
    void showEmployeeAssignedActivity(const std::string& actID);

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