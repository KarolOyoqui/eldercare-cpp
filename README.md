# Eldercare-cpp

## Project Description
Managing an elder care center is a complex task that requires careful management of records, staff, and recreational activities. 

This project is the Elder Care Management System, a console-based application designed to simulate and manage the daily operations of a nursing home. The program handles local databases to register clients (patients), assign employees (teachers/caregivers), and enroll users in various therapeutic activities.

The system features a secure authentication portal where administrators, employees, and clients can log in using their unique ID and password. Each user has a personalized menu that allows them to perform specific actions and queries based on their role.

With this project, I aim to solve a problem using all the concepts from the Object-Oriented Programming (OOP) course.

Like in a real simulation, every action has effects: signing up a resident for an activity uses limited spots, and serving weekly meals reduces the inventory. The goal is to make the center’s management better through a program that helps with administration.

# Sistem Operation
* **Security:** Access is restricted through a credential-based login system. The program verifies IDs and passwords to open the corresponding menus.
* **User-friendly:** The program is easy to use. Residents and staff can be registered, modified, searched, and deleted. The system uses polymorphism to handle different user types, facilitating data search and viewing.
* **Activity Scheduling:** Activities have a maximum capacity. The system also validates availability and verifies that there are no scheduling conflicts before enrolling a resident or assigning a teacher.

# UML Class Diagram
<img width="1920" height="1080" alt="UML Class Diagram" src="https://github.com/user-attachments/assets/9a393ff8-5632-434c-81d7-255f34285f83" />
