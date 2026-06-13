#ifndef USER_H
#define USER_H

#include <string>

enum class UserRole {
    Doctor,
    Receptionist
};

class User {
public:
    User(int id,
        const std::string& login,
        const std::string& password,
        const std::string& firstName,
        const std::string& lastName,
        UserRole role);
    virtual ~User() = default;

    int getId() const;
    std::string getLogin() const;
    std::string getPassword() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    UserRole getRole() const;
    virtual std::string getRoleName() const = 0;

private:
    int id_;
    std::string login_;
    std::string password_;
    std::string firstName_;
    std::string lastName_;
    UserRole role_;
};

#endif
