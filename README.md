# Eldercare-cpp

# Project Description
Managing an elder care center is a complex task that requires careful management of records, staff, and recreational activities. 

This project is the Elder Care Management System, a console-based application designed to simulate and manage the daily operations of a nursing home. The program handles local databases to register clients (patients), assign employees (teachers/caregivers), and enroll users in various therapeutic activities.

The system features a secure authentication portal where administrators, employees, and clients can log in using their unique ID and password. Each user has a personalized menu that allows them to perform specific actions and queries based on their role.

With this project, I aim to solve a problem using all the concepts from the Object-Oriented Programming (OOP) course.

Like in a real simulation, every action has effects: signing up a resident for an activity uses limited spots, and serving weekly meals reduces the inventory. The goal is to make the center’s management better through a program that helps with administration.

# Sistem Operation
* **Security:** Access is restricted through a credential-based login system. The program verifies IDs and passwords to open the corresponding menus.
* **User-friendly:** The program is easy to use. Residents and staff can be registered, modified, searched, and deleted. The system uses polymorphism to handle different user types, facilitating data search and viewing.
* **Activity Scheduling:** Activities have a maximum capacity. The system also validates availability and verifies that there are no scheduling conflicts before enrolling a resident or assigning a teacher.

# OOP concepts
For this project, I applied what we learned in class like this:

* **Inheritance and Abstraction:** My User class is the parent class (abstract). Client and Employee are the child classes; this way I recycle code like the name or ID and only add the specific details for each one.
* **Polymorphism:** I use it in the listClients() and listEmployees() functions. I save everyone in a vector using pointers of the parent class (User) and call displayProfile() so each user knows how to print the data.
* **Operator Overloading:** In Activity.h, I modified the << operator to teach cout how to directly print all the information of a class or activity quickly.
* **Exceptions:** I created a error called FileOpenException. If the program can't find or open the .txt text files, it throws this exception and the try...catch prevents the program from crashing.

# Memory Management (Rule of Zero)
To handle memory, I decided to use the **Rule of Zero**. Instead of using the old manual pointers that can cause memory leaks, I used:
1. **std::vecto** for the lists.
2. **std::unique_ptr** to handle users safely.
3. **std::string** for texts.

Since all of this cleans itself from memory when it's no longer in use, my classes don't need complicated constructors or destructors. I only added empty virtual destructors (virtual ~User() {}) in the parent classes just to be safe.
  
# UML Class Diagram
<img width="1920" height="1080" alt="Copia de Copia de Pizarra online diagrama UML minimalista degradado naranja brillante amarillo pastel blanco" src="https://github.com/user-attachments/assets/df170c1e-a86c-4f11-b042-e19ef706142b" />

# Project Structure

**Main.cpp**
It is the main file that handles everything. It checks if the .txt files (our database) already exist; if they don't, it creates them. After that, it opens the Menu so the program starts running.


**User.h** 
Here the type of user and the data required from them are defined. I made a parent class called User (with the ID, name, and password), and from there I created two child classes: Client (the residents) and Employee (the teachers). Inheritance is used here.

**Activity.h**
Here the data for the workshops provided by the nursing home is stored. Each activity has its ID, description, and schedule. The << operator is also used to print the class information to the console.

**Menu.h**
Here all the functions that are used are declared (register, delete, search, log in), and a list is created where the activities are saved. I also defined my custom error (FileOpenException) here.

**Menu.cpp**
In this file:
* The information is opened, read, and saved into the .txt files.
* I use polymorphism to go through my list of users and print their profiles, regardless of whether they are clients or employees.
* Validations are made so people cannot enroll in a workshop if it is already full or if their schedules conflict.

# How to Run the Program & Expected Output
Upon starting the system, you will be greeted by the Main Menu with two options:
1. **Access Portal (Login):** Takes you to the user verification screen.
2. **Shutdown System:** Safely exits the application.
   <img width="787" height="202" alt="image" src="https://github.com/user-attachments/assets/3beffa9c-08ed-46c0-8101-0775964a6e4f" />

The system features 3 different access levels (Admin, Employee, and Client), each handled by a unique ID and password. The system uses specific ID prefixes to identify roles and grant permissions:
* **A** for **Administrators** (Full system access to modify data).
* **T** for **Teachers/Employees** (Read-only access to their profile and classes).
* **E** for **Clients** (Read-only access to their profile and enrolled activities).
  <img width="786" height="206" alt="image" src="https://github.com/user-attachments/assets/be17af64-318d-44b8-b1a8-2db095c9ced6" />

Here is how you can test each visibility level and the expected output:

# 1. Administrator Level
Use the following master credentials to access the Admin portal:
* **ID:** A1234
* **Password:** 1234

**Expected Output / Capabilities:**
The Admin menu will display 13 options, providing full management control over the system:
1. **Register client:** Adds a new client (the system auto-generates their ID).
2. **Register employee (Teacher):** Adds a new teacher and assigns them to a specific class.
3. **Remove client:** Deletes a client by searching their ID.
4. **Remove employee:** Deletes a teacher by searching their ID.
5. **Modify client:** Searches for a client by ID to update their personal data.
6. **Modify employee:** Searches for a teacher by ID to update their personal data.
7. **List all clients:** Displays the profile info of all clients (passwords remain hidden for security).
8. **List all employees:** Displays the profile info of all teachers (passwords remain hidden).
9. **Search client:** Pulls up a specific client's data using their ID.
10. **Search employee:** Pulls up a specific teacher's data and the class they teach.
11. **Enroll Client in Activity:** Registers a client into a class (the system enforces a strict 20-person capacity limit).
12. **List Activities & Status:** Displays details for each class and how many people are currently enrolled.
13. **Log Out:** Returns to the main home screen.
<img width="732" height="452" alt="image" src="https://github.com/user-attachments/assets/1b05ae1e-944b-4bbf-b759-f6b17f1cae9e" />

---

# 2. Client Level
To test the client view, use any of the following pre-registered database accounts:
* **ID:** E0001 | **Password:** juanito18
* **ID:** E0002 | **Password:** elena51
* **ID:** E0003 | **Password:** roberto44

**Expected Output / Capabilities:**
1. **View My Personal Profile & Registered Classes:** Displays the client's personal details and a list of the activities they are enrolled in.
2. **Log Out:** Returns to the main home screen.
<img width="907" height="265" alt="image" src="https://github.com/user-attachments/assets/92b9ec56-8718-453d-8754-f3d95f377c64" />
<img width="1171" height="415" alt="image" src="https://github.com/user-attachments/assets/ed36439a-6e39-4c91-a08a-cbcbbe6e18b1" />

---

# 3. Employee (Teacher) Level
To test the employee view, use any of the following pre-registered database accounts:
* **ID:** T0001 | **Password:** profeRica
* **ID:** T0002 | **Password:** laura90
<img width="816" height="177" alt="image" src="https://github.com/user-attachments/assets/758a148e-81e1-47e3-9aed-1c04c7488bfe" />
<img width="1007" height="395" alt="image" src="https://github.com/user-attachments/assets/1b63aade-5e9f-4fc6-a1ac-0db7261ea566" />


**Expected Output / Capabilities:**
1. **View My Personal Profile & Assigned Class:** Displays the teacher's personal details and the specific activity they are assigned to teach.
2. **Log Out:** Returns to the main home screen.
   
