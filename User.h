#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>
#include "Activity.h"

class User
{
public:
	User() = default;
	User(int id, std::string name) : id(id), name(std::move(name)) {}

	// Regla del Cero: no definimos dtor ni operadores

	virtual ~User() = default;

	int getId() const noexcept { return id; }
	const std::string& getName() const noexcept { return name; }

	virtual std::string role() const = 0;

	void addActivity(const Activity& act) { activities.push_back(act.clone()); }
	const std::vector<std::unique_ptr<Activity>>& getActivities() const noexcept { return activities; }

protected:
	int id{0};
	std::string name;
	std::vector<std::unique_ptr<Activity>> activities;
};

class Client : public User
{
public:
	using User::User;
	std::string role() const override { return "Client"; }
};

class Employee : public User
{
public:
	using User::User;
	std::string role() const override { return "Employee"; }
};

#endif // USER_H
