#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <memory>

class Activity
{
public:
	Activity() = default;
	Activity(int id, std::string name, int durationMinutes, std::string description = {})
		: id(id), name(std::move(name)), durationMinutes(durationMinutes), description(std::move(description)) {}

	// Regla del Cero: no definimos destructores ni operadores especiales

	int getId() const noexcept { return id; }
	const std::string& getName() const noexcept { return name; }
	int getDuration() const noexcept { return durationMinutes; }
	const std::string& getDescription() const noexcept { return description; }

	virtual std::string typeName() const = 0;
	virtual std::unique_ptr<Activity> clone() const = 0;

private:
	int id{0};
	std::string name;
	int durationMinutes{0};
	std::string description;
};

// Ocho actividades derivadas
class Meeting : public Activity
{
public:
	using Activity::Activity;
	std::string typeName() const override { return "Meeting"; }
	std::unique_ptr<Activity> clone() const override { return std::make_unique<Meeting>(*this); }
};

class Coding : public Activity
{
public:
	using Activity::Activity;
	std::string typeName() const override { return "Coding"; }
	std::unique_ptr<Activity> clone() const override { return std::make_unique<Coding>(*this); }
};

class Design : public Activity
{
public:
	using Activity::Activity;
	std::string typeName() const override { return "Design"; }
	std::unique_ptr<Activity> clone() const override { return std::make_unique<Design>(*this); }
};

class Testing : public Activity
{
public:
	using Activity::Activity;
	std::string typeName() const override { return "Testing"; }
	std::unique_ptr<Activity> clone() const override { return std::make_unique<Testing>(*this); }
};

class Review : public Activity
{
public:
	using Activity::Activity;
	std::string typeName() const override { return "Review"; }
	std::unique_ptr<Activity> clone() const override { return std::make_unique<Review>(*this); }
};

class Training : public Activity
{
public:
	using Activity::Activity;
	std::string typeName() const override { return "Training"; }
	std::unique_ptr<Activity> clone() const override { return std::make_unique<Training>(*this); }
};

class Research : public Activity
{
public:
	using Activity::Activity;
	std::string typeName() const override { return "Research"; }
	std::unique_ptr<Activity> clone() const override { return std::make_unique<Research>(*this); }
};

class Deployment : public Activity
{
public:
	using Activity::Activity;
	std::string typeName() const override { return "Deployment"; }
	std::unique_ptr<Activity> clone() const override { return std::make_unique<Deployment>(*this); }
};

#endif // ACTIVITY_H
