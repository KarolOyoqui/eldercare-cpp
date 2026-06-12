#include "Menu.h"
#include <fstream>

void checkFiles() {
    //If the file doesn't exist, it creates it; if it exists, it simply opens it. Finally, it closes to prevent memory lack.
    std::ofstream fileClients("clients.txt", std::ios::app); fileClients.close();
    std::ofstream fileEmployees("employees.txt", std::ios::app); fileEmployees.close();
    std::ofstream fileEnrollments("enrollments.txt", std::ios::app); fileEnrollments.close();
}

int main() {
    checkFiles(); //We verify that the .txt files are available
    Menu app; //We call Menu (Menu.h) and create an object called "app"
    app.runSystem();//The app object executes runSystem()
    return 0;
}
