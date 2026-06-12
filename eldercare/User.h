#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User {
protected:
    std::string code;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string password;
public:
    User(const std::string& c, const std::string& fn, const std::string& ln, const std::string& ph, const std::string& pass)
        : code(c), firstName(fn), lastName(ln), phoneNumber(ph), password(pass) {
    }
    virtual ~User() {}
    virtual void displayProfile() const = 0;
    std::string getCode() const { return code; }
    std::string getPassword() const { return password; }
    std::string getFullName() const { return firstName + " " + lastName; }
};

class Client : public User {
private:
    std::string birthDate;
    std::string address;
    std::string state;
    std::string city;
    std::string postalCode;
    std::string emergencyPhoneNumber;
    std::string currentDate;
public:
    Client(const std::string& c, const std::string& fn, const std::string& ln, const std::string& bd, const std::string& addr,
        const std::string& st, const std::string& ct, const std::string& pc, const std::string& ph, const std::string& eph,
        const std::string& cd, const std::string& pass)
        : User(c, fn, ln, ph, pass), birthDate(bd), address(addr), state(st), city(ct), postalCode(pc), emergencyPhoneNumber(eph), currentDate(cd) {
    }

    void displayProfile() const override {
        std::cout << "=========================================================" << std::endl;
        std::cout << "Code: " << code << std::endl;
        std::cout << "Full Name: " << firstName << " " << lastName << std::endl;
        std::cout << "Date of Birth: " << birthDate << std::endl;
        std::cout << "Address: " << address << ", " << city << ", " << state << " (Postal Code: " << postalCode << ")" << std::endl;
        std::cout << "Phone Number: " << phoneNumber << std::endl;
        std::cout << "Emergency Contact: " << emergencyPhoneNumber << std::endl;
        std::cout << "Registration Date: " << currentDate << std::endl;
        std::cout << "=========================================================" << std::endl;
    }
};

class Employee : public User {
private:
    std::string idUserAdmin;
    std::string idRole;
public:
    Employee(const std::string& c, const std::string& fn, const std::string& ln, const std::string& ph,
        const std::string& admin, const std::string& role, const std::string& pass)
        : User(c, fn, ln, ph, pass), idUserAdmin(admin), idRole(role) {
    }

    void displayProfile() const override {
        std::cout << "=========================================================" << std::endl;
        std::cout << "Code: " << code << std::endl;
        std::cout << "Full Name: " << firstName << " " << lastName << std::endl;
        std::cout << "Phone Number: " << phoneNumber << std::endl;
        std::cout << "Admin ID: " << idUserAdmin << std::endl;
        std::cout << "Teaching Activity ID: " << idRole << std::endl;
        std::cout << "=========================================================" << std::endl;
    }
    std::string getIdRole() const { return idRole; }
};

#endif