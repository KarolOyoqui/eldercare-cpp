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
