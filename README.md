# Eldercare-cpp

## Project Description
Managing an elder care center is a complex task that requires careful management of records, staff, and recreational activities. 

This project is the Elder Care Management System, a console-based application designed to simulate and manage the daily operations of a nursing home. The program handles local databases to register clients (patients), assign employees (teachers/caregivers), and enroll users in various therapeutic activities.

The system features a secure authentication portal where administrators, employees, and clients can log in using their unique ID and password. Each user has a personalized menu that allows them to perform specific actions and queries based on their role.

With this project, I aim to solve a problem using all the concepts from the Object-Oriented Programming (OOP) course.

Like in a real simulation, every action has effects: signing up a resident for an activity uses limited spots, and serving weekly meals reduces the inventory. The goal is to make the center’s management better through a program that helps with administration.

# Sistem Operation
* Security: Access is restricted by a credential system.
* Population Management: Residents and staff can be registered. The system uses polymorphism to search and remove records by name or ID, making searches easier.
* Nutrition Logistics: The system shows which food supplies are available.
* Activity Schedule: Activities have a maximum capacity. The system checks availability before assigning a resident, ensuring staff capacity is not exceeded.
* Automatic Persistence: When the system closes, all changes to inventory, new registrations, and removals are saved in text files, working as a local database.
# UML Class Diagram
<img width="1920" height="1080" alt="UML Class Diagram" src="https://github.com/user-attachments/assets/9a393ff8-5632-434c-81d7-255f34285f83" />
