# Eldercare-cpp

Running a senior care center is difficult because it needs careful management of staff, health, and food. This project simulates the daily work of a nursing home, where the manager must balance the well-being of residents with the supplies and workers available.

Like in a real simulation, every action has effects: signing up a resident for an activity uses limited spots, and serving weekly meals reduces the inventory. The goal is to make the center’s management better through a program that helps with administration.
# Sistem Operation
* Security: Access is restricted by a credential system.
* Population Management: Residents and staff can be registered. The system uses polymorphism to search and remove records by name or ID, making searches easier.
* Nutrition Logistics: The system shows which food supplies are available.
* Activity Schedule: Activities have a maximum capacity. The system checks availability before assigning a resident, ensuring staff capacity is not exceeded.
* Automatic Persistence: When the system closes, all changes to inventory, new registrations, and removals are saved in text files, working as a local database.
# UML Class Diagram
<img width="1920" height="1080" alt="UML Class Diagram" src="https://github.com/user-attachments/assets/9a393ff8-5632-434c-81d7-255f34285f83" />
