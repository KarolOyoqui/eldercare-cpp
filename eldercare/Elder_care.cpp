#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

// Clear screen setup depending on the operating system
#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#error "System could not clear the screen."
#endif

using namespace std;

class Menu
{
private:
    string code; // Variable used to handle the ID/Code of records
    string firstName;
    string lastName;
    string birthDate;
    string address;
    string state;
    string city;
    string postalCode;
    string phoneNumber;
    string emergencyPhoneNumber;
    string currentDate;
    string idUserAdmin;
    string idRole;

public:
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
    void mainMenu();
    void displayRecord(string cod);
    void displayEmployeeRecord(string cod);
};

// Global / Auxiliary function declarations
void pause();
void showError();
void checkFiles();

int main()
{
    checkFiles(); // Creates files if they do not exist
    Menu app;
    app.mainMenu();
    return 0;
}

void Menu::mainMenu()
{
    int option;
    do
    {
        system(CLEAR);
        cout << "=================================================" << endl;
        cout << "         Elder Care Management System            " << endl;
        cout << "=================================================" << endl;
        cout << "1.  Register client" << endl;
        cout << "2.  Register employee" << endl;
        cout << "3.  Remove client" << endl;
        cout << "4.  Remove employee" << endl;
        cout << "5.  Modify client" << endl;
        cout << "6.  Modify employee" << endl;
        cout << "7.  List all clients" << endl;
        cout << "8.  List all employees" << endl;
        cout << "9.  Search client" << endl;
        cout << "10. Search employee" << endl;
        cout << "11. Exit" << endl;
        cout << "Select an option please: ";
        cin >> option;
        cin.ignore(); // Clears the buffer to avoid skipping subsequent getlines

        switch (option)
        {
        case 1:
            registerClient();
            break;
        case 2:
            registerEmployee();
            break;
        case 3:
            removeClient();
            break;
        case 4:
            removeEmployee();
            break;
        case 5:
            modifyClient();
            break;
        case 6:
            modifyEmployee();
            break;
        case 7:
            listClients();
            break;
        case 8:
            listEmployees();
            break;
        case 9:
            searchClient();
            break;
        case 10:
            searchEmployee();
            break;
        case 11:
            cout << "Exiting the system..." << endl;
            break;
        default:
            showError();
            pause();
            break;
        }
    } while (option != 11);
}

void Menu::registerClient()
{
    ofstream fileOutput;
    ifstream fileInputCheck;
    string auxCode;
    bool isDuplicate = false;

    fileOutput.open("clients.txt", ios::app);
    fileInputCheck.open("clients.txt", ios::in);

    if (fileOutput.is_open() && fileInputCheck.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Register a Client ***\t\t\t\t\n\n";
        cout << "Enter the client code: ";
        getline(cin, auxCode);

        if (auxCode == "") {
            do {
                cout << "Invalid client code! Please try again: ";
                getline(cin, auxCode);
            } while (auxCode == "");
        }

        // Loop to prevent duplicate codes
        do {
            fileInputCheck.seekg(0, ios::beg);
            isDuplicate = false;
            while (getline(fileInputCheck, code))
            {
                getline(fileInputCheck, firstName);
                getline(fileInputCheck, lastName);
                getline(fileInputCheck, birthDate);
                getline(fileInputCheck, address);
                getline(fileInputCheck, state);
                getline(fileInputCheck, city);
                getline(fileInputCheck, postalCode);
                getline(fileInputCheck, phoneNumber);
                getline(fileInputCheck, emergencyPhoneNumber);
                getline(fileInputCheck, currentDate);

                if (code == auxCode)
                {
                    isDuplicate = true;
                    cout << "\n\nA client with this code already exists!\n\n";
                    cout << "The associated client is: " << firstName << " " << lastName << "\n\n";
                    cout << "Enter a valid code: ";
                    getline(cin, auxCode);

                    if (auxCode == "") {
                        do {
                            cout << "\nInvalid code! Please try again: ";
                            getline(cin, auxCode);
                        } while (auxCode == "");
                    }
                    break;
                }
            }
        } while (isDuplicate == true);

        code = auxCode;
        system(CLEAR);
        cout << "\t\t\t\t*** Register a Client ***\t\t\t\t\n\n";
        cout << "Client Code: " << code << "\n\n";

        cout << "Enter client's first name: "; getline(cin, firstName);
        cout << "Enter client's last name: "; getline(cin, lastName);
        cout << "Enter date of birth (DD/MM/YYYY): "; getline(cin, birthDate);
        cout << "Enter address/domicile: "; getline(cin, address);
        cout << "Enter State: "; getline(cin, state);
        cout << "Enter City: "; getline(cin, city);
        cout << "Enter postal code: "; getline(cin, postalCode);
        cout << "Enter phone number: "; getline(cin, phoneNumber);
        cout << "Enter emergency phone number: "; getline(cin, emergencyPhoneNumber);
        cout << "Enter registration date (DD/MM/YYYY): "; getline(cin, currentDate);

        // Structured writing into the text file
        fileOutput << code << endl << firstName << endl << lastName << endl << birthDate << endl
            << address << endl << state << endl << city << endl << postalCode << endl
            << phoneNumber << endl << emergencyPhoneNumber << endl << currentDate << endl;

        cout << "\nRegistration completed successfully.\n\n";
    }
    else
    {
        showError();
    }

    fileOutput.close();
    fileInputCheck.close();
    pause();
}

void Menu::registerEmployee()
{
    ofstream fileOutput;
    ifstream fileInputCheck;
    string auxCode;
    bool isDuplicate = false;

    fileOutput.open("employees.txt", ios::app);
    fileInputCheck.open("employees.txt", ios::in);

    if (fileOutput.is_open() && fileInputCheck.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Register an Employee ***\t\t\t\t\n\n";
        cout << "Enter the employee code: ";
        getline(cin, auxCode);

        if (auxCode == "") {
            do {
                cout << "Invalid code! Please try again: ";
                getline(cin, auxCode);
            } while (auxCode == "");
        }

        do {
            fileInputCheck.seekg(0, ios::beg);
            isDuplicate = false;
            while (getline(fileInputCheck, code))
            {
                getline(fileInputCheck, firstName);
                getline(fileInputCheck, lastName);
                getline(fileInputCheck, birthDate);
                getline(fileInputCheck, address);
                getline(fileInputCheck, state);
                getline(fileInputCheck, city);
                getline(fileInputCheck, postalCode);
                getline(fileInputCheck, phoneNumber);
                getline(fileInputCheck, idUserAdmin);
                getline(fileInputCheck, idRole);

                if (code == auxCode)
                {
                    isDuplicate = true;
                    cout << "\n\nAn employee with this code already exists!\n\n";
                    cout << "The associated employee is: " << firstName << " " << lastName << "\n\n";
                    cout << "Enter a valid code: ";
                    getline(cin, auxCode);
                    if (auxCode == "") {
                        do {
                            cout << "\nInvalid code! Please try again: ";
                            getline(cin, auxCode);
                        } while (auxCode == "");
                    }
                    break;
                }
            }
        } while (isDuplicate == true);

        code = auxCode;
        system(CLEAR);
        cout << "\t\t\t\t*** Register an Employee ***\t\t\t\t\n\n";
        cout << "Employee Code: " << code << "\n\n";

        cout << "Enter employee's first name: "; getline(cin, firstName);
        cout << "Enter employee's last name: "; getline(cin, lastName);
        cout << "Enter date of birth (DD/MM/YYYY): "; getline(cin, birthDate);
        cout << "Enter address/domicile: "; getline(cin, address);
        cout << "Enter State: "; getline(cin, state);
        cout << "Enter City: "; getline(cin, city);
        cout << "Enter postal code: "; getline(cin, postalCode);
        cout << "Enter phone number: "; getline(cin, phoneNumber);
        cout << "Enter Admin/Manager ID in charge: "; getline(cin, idUserAdmin);
        cout << "Enter assigned Role ID: "; getline(cin, idRole);

        fileOutput << code << endl << firstName << endl << lastName << endl << birthDate << endl
            << address << endl << state << endl << city << endl << postalCode << endl
            << phoneNumber << endl << idUserAdmin << endl << idRole << endl;

        cout << "\nRegistration completed successfully.\n\n";
    }
    else
    {
        showError();
    }

    fileOutput.close();
    fileInputCheck.close();
    pause();
}

void Menu::removeClient()
{
    ifstream fileReader;
    ofstream fileAuxiliary;
    bool found = false;
    string auxCode, response;

    fileReader.open("clients.txt", ios::in);
    if (fileReader.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Remove a Client ***\t\t\t\t\n\n";

        // Check if the file is empty
        if (fileReader.peek() == ifstream::traits_type::eof()) {
            cout << "No clients currently registered in the system.\n";
            fileReader.close();
            pause();
            return;
        }

        fileAuxiliary.open("auxiliary.txt", ios::out);
        cout << "Enter the code of the client you wish to remove: ";
        getline(cin, auxCode);

        while (getline(fileReader, code))
        {
            getline(fileReader, firstName);
            getline(fileReader, lastName);
            getline(fileReader, birthDate);
            getline(fileReader, address);
            getline(fileReader, state);
            getline(fileReader, city);
            getline(fileReader, postalCode);
            getline(fileReader, phoneNumber);
            getline(fileReader, emergencyPhoneNumber);
            getline(fileReader, currentDate);

            if (auxCode == code)
            {
                found = true;
                cout << "\n\nRecord Found!\n\n";
                displayRecord(code);
                cout << "Are you sure you want to remove this client (y/n)?: ";
                getline(cin, response);

                if (response == "y" || response == "Y" || response == "yes" || response == "YES") {
                    cout << "\nThe client has been successfully removed.\n";
                }
                else {
                    cout << "\nOperation canceled. Client retained.\n";
                    fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl
                        << address << endl << state << endl << city << endl << postalCode << endl
                        << phoneNumber << endl << emergencyPhoneNumber << endl << currentDate << endl;
                }
            }
            else
            {
                fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl
                    << address << endl << state << endl << city << endl << postalCode << endl
                    << phoneNumber << endl << emergencyPhoneNumber << endl << currentDate << endl;
            }
        }

        fileReader.close();
        fileAuxiliary.close();

        // Cast to (void) to ignore the return value and prevent C6031 warnings
        (void)remove("clients.txt");
        (void)rename("auxiliary.txt", "clients.txt");

        if (!found) {
            cout << "\nCould not find client code: " << auxCode << "\n";
        }
    }
    else
    {
        showError();
    }
    pause();
}

void Menu::removeEmployee()
{
    ifstream fileReader;
    ofstream fileAuxiliary;
    bool found = false;
    string auxCode, response;

    fileReader.open("employees.txt", ios::in);
    if (fileReader.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Remove an Employee ***\t\t\t\t\n\n";

        if (fileReader.peek() == ifstream::traits_type::eof()) {
            cout << "No employees currently registered in the system.\n";
            fileReader.close();
            pause();
            return;
        }

        fileAuxiliary.open("auxiliary.txt", ios::out);
        cout << "Enter the code of the employee you wish to remove: ";
        getline(cin, auxCode);

        while (getline(fileReader, code))
        {
            getline(fileReader, firstName);
            getline(fileReader, lastName);
            getline(fileReader, birthDate);
            getline(fileReader, address);
            getline(fileReader, state);
            getline(fileReader, city);
            getline(fileReader, postalCode);
            getline(fileReader, phoneNumber);
            getline(fileReader, idUserAdmin);
            getline(fileReader, idRole);

            if (auxCode == code)
            {
                found = true;
                cout << "\n\nRecord Found!\n\n";
                displayEmployeeRecord(code);
                cout << "Are you sure you want to remove this employee (y/n)?: ";
                getline(cin, response);

                if (response == "y" || response == "Y" || response == "yes" || response == "YES") {
                    cout << "\nThe employee has been successfully removed.\n";
                }
                else {
                    cout << "\nOperation canceled. Employee retained.\n";
                    fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl
                        << address << endl << state << endl << city << endl << postalCode << endl
                        << phoneNumber << endl << idUserAdmin << endl << idRole << endl;
                }
            }
            else
            {
                fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl
                    << address << endl << state << endl << city << endl << postalCode << endl
                    << phoneNumber << endl << idUserAdmin << endl << idRole << endl;
            }
        }

        fileReader.close();
        fileAuxiliary.close();

        // Cast to (void) to ignore the return value and prevent C6031 warnings
        (void)remove("employees.txt");
        (void)rename("auxiliary.txt", "employees.txt");

        if (!found) {
            cout << "\nCould not find employee code: " << auxCode << "\n";
        }
    }
    else
    {
        showError();
    }
    pause();
}

void Menu::modifyClient()
{
    ifstream fileReader;
    ofstream fileAuxiliary;
    bool found = false;
    string auxCode;

    fileReader.open("clients.txt", ios::in);
    if (fileReader.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Modify Client ***\t\t\t\t\n\n";

        if (fileReader.peek() == ifstream::traits_type::eof()) {
            cout << "No clients registered to modify.\n";
            fileReader.close();
            pause();
            return;
        }

        fileAuxiliary.open("auxiliary.txt", ios::out);
        cout << "Enter the code of the client you wish to modify: ";
        getline(cin, auxCode);

        while (getline(fileReader, code))
        {
            getline(fileReader, firstName);
            getline(fileReader, lastName);
            getline(fileReader, birthDate);
            getline(fileReader, address);
            getline(fileReader, state);
            getline(fileReader, city);
            getline(fileReader, postalCode);
            getline(fileReader, phoneNumber);
            getline(fileReader, emergencyPhoneNumber);
            getline(fileReader, currentDate);

            if (auxCode == code)
            {
                found = true;
                cout << "\n--- Current Data ---\n";
                displayRecord(code);
                cout << "\n--- Enter New Data ---\n";
                cout << "New First Name: "; getline(cin, firstName);
                cout << "New Last Name: "; getline(cin, lastName);
                cout << "New Date of Birth: "; getline(cin, birthDate);
                cout << "New Address: "; getline(cin, address);
                cout << "New State: "; getline(cin, state);
                cout << "New City: "; getline(cin, city);
                cout << "New Postal Code: "; getline(cin, postalCode);
                cout << "New Phone Number: "; getline(cin, phoneNumber);
                cout << "New Emergency Phone Number: "; getline(cin, emergencyPhoneNumber);
                cout << "New Registration Date: "; getline(cin, currentDate);
                cout << "\nRecord modified successfully!\n";
            }

            fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl
                << address << endl << state << endl << city << endl << postalCode << endl
                << phoneNumber << endl << emergencyPhoneNumber << endl << currentDate << endl;
        }

        fileReader.close();
        fileAuxiliary.close();

        // Cast to (void) to ignore the return value and prevent C6031 warnings
        (void)remove("clients.txt");
        (void)rename("auxiliary.txt", "clients.txt");

        if (!found) {
            cout << "\nNo client found with code: " << auxCode << "\n";
        }
    }
    else
    {
        showError();
    }
    pause();
}

void Menu::modifyEmployee()
{
    ifstream fileReader;
    ofstream fileAuxiliary;
    bool found = false;
    string auxCode;

    fileReader.open("employees.txt", ios::in);
    if (fileReader.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Modify Employee ***\t\t\t\t\n\n";

        if (fileReader.peek() == ifstream::traits_type::eof()) {
            cout << "No employees registered to modify.\n";
            fileReader.close();
            pause();
            return;
        }

        fileAuxiliary.open("auxiliary.txt", ios::out);
        cout << "Enter the code of the employee you wish to modify: ";
        getline(cin, auxCode);

        while (getline(fileReader, code))
        {
            getline(fileReader, firstName);
            getline(fileReader, lastName);
            getline(fileReader, birthDate);
            getline(fileReader, address);
            getline(fileReader, state);
            getline(fileReader, city);
            getline(fileReader, postalCode);
            getline(fileReader, phoneNumber);
            getline(fileReader, idUserAdmin);
            getline(fileReader, idRole);

            if (auxCode == code)
            {
                found = true;
                cout << "\n--- Current Data ---\n";
                displayEmployeeRecord(code);
                cout << "\n--- Enter New Data ---\n";
                cout << "New First Name: "; getline(cin, firstName);
                cout << "New Last Name: "; getline(cin, lastName);
                cout << "New Date of Birth: "; getline(cin, birthDate);
                cout << "New Address: "; getline(cin, address);
                cout << "New State: "; getline(cin, state);
                cout << "New City: "; getline(cin, city);
                cout << "New Postal Code: "; getline(cin, postalCode);
                cout << "New Phone Number: "; getline(cin, phoneNumber);
                cout << "New Admin/Manager ID: "; getline(cin, idUserAdmin);
                cout << "New Role ID: "; getline(cin, idRole);
                cout << "\nRecord modified successfully!\n";
            }

            fileAuxiliary << code << endl << firstName << endl << lastName << endl << birthDate << endl
                << address << endl << state << endl << city << endl << postalCode << endl
                << phoneNumber << endl << idUserAdmin << endl << idRole << endl;
        }

        fileReader.close();
        fileAuxiliary.close();

        // Cast to (void) to ignore the return value and prevent C6031 warnings
        (void)remove("employees.txt");
        (void)rename("auxiliary.txt", "employees.txt");

        if (!found) {
            cout << "\nNo employee found with code: " << auxCode << "\n";
        }
    }
    else
    {
        showError();
    }
    pause();
}

void Menu::listClients()
{
    ifstream fileReader;
    fileReader.open("clients.txt", ios::in);

    if (fileReader.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** List of Registered Clients ***\t\t\t\t\n\n";

        if (fileReader.peek() == ifstream::traits_type::eof()) {
            cout << "There are currently no clients in the database.\n";
        }
        else {
            while (getline(fileReader, code))
            {
                getline(fileReader, firstName);
                getline(fileReader, lastName);
                getline(fileReader, birthDate);
                getline(fileReader, address);
                getline(fileReader, state);
                getline(fileReader, city);
                getline(fileReader, postalCode);
                getline(fileReader, phoneNumber);
                getline(fileReader, emergencyPhoneNumber);
                getline(fileReader, currentDate);

                displayRecord(code);
            }
        }
        fileReader.close();
    }
    else
    {
        showError();
    }
    pause();
}

void Menu::listEmployees()
{
    ifstream fileReader;
    fileReader.open("employees.txt", ios::in);

    if (fileReader.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** List of Registered Employees ***\t\t\t\t\n\n";

        if (fileReader.peek() == ifstream::traits_type::eof()) {
            cout << "There are currently no employees in the database.\n";
        }
        else {
            while (getline(fileReader, code))
            {
                getline(fileReader, firstName);
                getline(fileReader, lastName);
                getline(fileReader, birthDate);
                getline(fileReader, address);
                getline(fileReader, state);
                getline(fileReader, city);
                getline(fileReader, postalCode);
                getline(fileReader, phoneNumber);
                getline(fileReader, idUserAdmin);
                getline(fileReader, idRole);

                displayEmployeeRecord(code);
            }
        }
        fileReader.close();
    }
    else
    {
        showError();
    }
    pause();
}

void Menu::searchClient()
{
    ifstream fileReader;
    string auxCode;
    bool found = false;

    fileReader.open("clients.txt", ios::in);
    if (fileReader.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Search for a Client ***\t\t\t\t\n\n";
        cout << "Enter the client code to search: ";
        getline(cin, auxCode);

        while (getline(fileReader, code))
        {
            getline(fileReader, firstName);
            getline(fileReader, lastName);
            getline(fileReader, birthDate);
            getline(fileReader, address);
            getline(fileReader, state);
            getline(fileReader, city);
            getline(fileReader, postalCode);
            getline(fileReader, phoneNumber);
            getline(fileReader, emergencyPhoneNumber);
            getline(fileReader, currentDate);

            if (auxCode == code)
            {
                found = true;
                system(CLEAR);
                cout << "\t\t\t\t*** Client Found ***\t\t\t\t\n\n";
                displayRecord(code);
                break;
            }
        }
        if (!found) {
            cout << "\nNo client found with code: " << auxCode << "\n";
        }
        fileReader.close();
    }
    else
    {
        showError();
    }
    pause();
}

void Menu::searchEmployee()
{
    ifstream fileReader;
    string auxCode;
    bool found = false;

    fileReader.open("employees.txt", ios::in);
    if (fileReader.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Search for an Employee ***\t\t\t\t\n\n";
        cout << "Enter the employee code to search: ";
        getline(cin, auxCode);

        while (getline(fileReader, code))
        {
            getline(fileReader, firstName);
            getline(fileReader, lastName);
            getline(fileReader, birthDate);
            getline(fileReader, address);
            getline(fileReader, state);
            getline(fileReader, city);
            getline(fileReader, postalCode);
            getline(fileReader, phoneNumber);
            getline(fileReader, idUserAdmin);
            getline(fileReader, idRole);

            if (auxCode == code)
            {
                found = true;
                system(CLEAR);
                cout << "\t\t\t\t*** Employee Found ***\t\t\t\t\n\n";
                displayEmployeeRecord(code);
                break;
            }
        }
        if (!found) {
            cout << "\nNo employee found with code: " << auxCode << "\n";
        }
        fileReader.close();
    }
    else
    {
        showError();
    }
    pause();
}

void Menu::displayRecord(string cod)
{
    cout << "=========================================================" << endl;
    cout << "Code: " << cod << endl;
    cout << "Full Name: " << firstName << " " << lastName << endl;
    cout << "Date of Birth: " << birthDate << endl;
    cout << "Address: " << address << ", " << city << ", " << state << " (Postal Code: " << postalCode << ")" << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Emergency Contact: " << emergencyPhoneNumber << endl;
    cout << "Registration Date: " << currentDate << endl;
    cout << "=========================================================" << endl;
}

void Menu::displayEmployeeRecord(string cod)
{
    cout << "=========================================================" << endl;
    cout << "Code: " << cod << endl;
    cout << "Full Name: " << firstName << " " << lastName << endl;
    cout << "Date of Birth: " << birthDate << endl;
    cout << "Address: " << address << ", " << city << ", " << state << " (Postal Code: " << postalCode << ")" << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Admin ID: " << idUserAdmin << endl;
    cout << "Role ID: " << idRole << endl;
    cout << "=========================================================" << endl;
}

// Global auxiliary function implementations
void pause()
{
    cout << "\nPress Enter to continue...";
    cin.get();
}

void showError()
{
    cout << "\nError: Invalid operation or issue with the data files.\n";
}

void checkFiles()
{
    // This function ensures data files physically exist so that initial readings do not fail
    ofstream fileClients("clients.txt", ios::app);
    fileClients.close();

    ofstream fileEmployees("employees.txt", ios::app);
    fileEmployees.close();
}