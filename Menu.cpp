#include "Menu.h"
#include "Activity.h"
#include <iostream>
#include <limits>

void Menu::run()
{
	createSampleData();

	while (true) {
		showMain();
		int choice = readInt("Seleccione opción: ");
		switch (choice) {
			case 1:
				listUsers();
				break;
			case 2: {
				std::string name = readLine("Nombre del cliente: ");
				addUser(std::make_unique<Client>(static_cast<int>(users.size()) + 1, name));
				std::cout << "Cliente creado.\n";
				break;
			}
			case 3: {
				std::string name = readLine("Nombre del empleado: ");
				addUser(std::make_unique<Employee>(static_cast<int>(users.size()) + 1, name));
				std::cout << "Empleado creado.\n";
				break;
			}
			case 4: {
				int id = readInt("ID de usuario: ");
				bool found = false;
				for (auto& u : users) {
					if (u->getId() == id) { userMenu(*u); found = true; break; }
				}
				if (!found) std::cout << "Usuario no encontrado.\n";
				break;
			}
			case 0:
				std::cout << "Saliendo...\n";
				return;
			default:
				std::cout << "Opción inválida.\n";
		}
	}
}

void Menu::addUser(std::unique_ptr<User> user)
{
	users.push_back(std::move(user));
}

const std::vector<std::unique_ptr<User>>& Menu::getUsers() const noexcept { return users; }

void Menu::showMain()
{
	std::cout << "\n=== Menú Principal ===\n";
	std::cout << "1) Listar usuarios\n";
	std::cout << "2) Crear cliente\n";
	std::cout << "3) Crear empleado\n";
	std::cout << "4) Seleccionar usuario por ID\n";
	std::cout << "0) Salir\n";
}

void Menu::createSampleData()
{
	auto c = std::make_unique<Client>(1, "ACME Corp");
	c->addActivity(Meeting(1, "Kickoff", 60, "Reunión inicial"));
	addUser(std::move(c));

	auto e = std::make_unique<Employee>(2, "Alice");
	e->addActivity(Coding(2, "Implement feature X", 180, "Programa principal"));
	addUser(std::move(e));
}

void Menu::listUsers() const
{
	std::cout << "\nUsuarios:\n";
	for (const auto& u : users) {
		std::cout << "ID: " << u->getId() << " | " << u->getName() << " (" << u->role() << ")\n";
		for (const auto& a : u->getActivities()) {
			std::cout << "   - [" << a->getId() << "] " << a->getName() << " (" << a->typeName() << ") "
					  << a->getDuration() << "m" << " - " << a->getDescription() << "\n";
		}
	}
}

void Menu::userMenu(User& user)
{
	std::cout << "\nUsuario: " << user.getName() << " (" << user.role() << ")\n";
	std::cout << "1) Listar actividades\n";
	std::cout << "2) Añadir actividad\n";
	std::cout << "0) Volver\n";
	int choice = readInt("Seleccione: ");
	switch (choice) {
		case 1:
			for (const auto& a : user.getActivities()) {
				std::cout << " - " << a->getName() << " (" << a->typeName() << ") " << a->getDuration() << "m\n";
			}
			break;
		case 2:
			addActivityToUser(user);
			break;
		case 0:
		default:
			break;
	}
}

void Menu::addActivityToUser(User& user)
{
	std::cout << "Tipos: 1=Meeting 2=Coding 3=Design 4=Testing 5=Review 6=Training 7=Research 8=Deployment\n";
	int t = readInt("Tipo: ");
	std::string name = readLine("Nombre actividad: ");
	int dur = readInt("Duración (min): ");
	std::string desc = readLine("Descripción: ");
	int id = static_cast<int>(user.getActivities().size()) + 1;
	switch (t) {
		case 1: user.addActivity(Meeting(id, name, dur, desc)); break;
		case 2: user.addActivity(Coding(id, name, dur, desc)); break;
		case 3: user.addActivity(Design(id, name, dur, desc)); break;
		case 4: user.addActivity(Testing(id, name, dur, desc)); break;
		case 5: user.addActivity(Review(id, name, dur, desc)); break;
		case 6: user.addActivity(Training(id, name, dur, desc)); break;
		case 7: user.addActivity(Research(id, name, dur, desc)); break;
		case 8: user.addActivity(Deployment(id, name, dur, desc)); break;
		default: std::cout << "Tipo inválido\n"; break;
	}
}

int Menu::readInt(const std::string& prompt) const
{
	while (true) {
		std::cout << prompt;
		int v{};
		if (std::cin >> v) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return v;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Entrada inválida. Intente de nuevo.\n";
	}
}

std::string Menu::readLine(const std::string& prompt) const
{
	std::cout << prompt;
	std::string s;
	std::getline(std::cin, s);
	return s;
}
