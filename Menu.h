#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>
#include <string>
#include "User.h"

class Menu
{
public:
	Menu() = default;
	~Menu() = default;

	void run();

	// para tests y manipulación
	void addUser(std::unique_ptr<User> user);
	const std::vector<std::unique_ptr<User>>& getUsers() const noexcept;

private:
	std::vector<std::unique_ptr<User>> users;

	void showMain();
	void createSampleData();
	void listUsers() const;
	void userMenu(User& user);
	void addActivityToUser(User& user);
	int readInt(const std::string& prompt) const;
	std::string readLine(const std::string& prompt) const;
};

#endif // MENU_H
