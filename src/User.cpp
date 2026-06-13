#include "User.h"

/**
 * @brief Konstruktor klasy bazowej User.
 * Inicjalizuje podstawowe dane użytkownika systemu (wspólne dla lekarzy i recepcji).
 */

User::User(int id,
    const std::string& login,
    const std::string& password,
    const std::string& firstName,
    const std::string& lastName,
    UserRole role)
    : id_(id),
    login_(login),
    password_(password),
    firstName_(firstName),
    lastName_(lastName),
    role_(role)
{}

int User::getId() const
{
    return id_;
}

std::string User::getLogin() const
{
    return login_;
}

std::string User::getPassword() const
{
    return password_;
}

std::string User::getFirstName() const
{
    return firstName_;
}

std::string User::getLastName() const
{
    return lastName_;
}
/**
 * @brief Zwraca pełne imię i nazwisko w jednym ciągu znaków.
 */
std::string User::getFullName() const
{
    return firstName_ + " " + lastName_;
}

UserRole User::getRole() const
{
    return role_;
}
