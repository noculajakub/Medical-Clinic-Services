#include "AuthService.h"

#include <memory>

void AuthService::addDoctor(const Doctor& doctor)
{
    users_.push_back(std::make_shared<Doctor>(doctor));
}

void AuthService::addReceptionist(const Receptionist& receptionist)
{
    users_.push_back(std::make_shared<Receptionist>(receptionist));
}

/**
 * @brief Weryfikuje podane dane uwierzytelniające.
 * Zwraca inteligentny wskaźnik na zalogowanego użytkownika lub nullptr przy błędnych danych.
 */

std::shared_ptr<User> AuthService::login(const std::string& login, const std::string& password) const
{
    for (const auto& user : users_) {
        if (user->getLogin() == login && user->getPassword() == password) {
            return user;
        }
    }
    return nullptr;
}

/**
 * @brief Wyszukuje lekarza po ID.
 * Używa std::dynamic_pointer_cast do bezpiecznego, polimorficznego rzutowania z klasy bazowej User na klasę Doctor.
 */

std::optional<Doctor> AuthService::findDoctorById(int doctorId) const
{
    for (const auto& user : users_) {
        if (user->getRole() == UserRole::Doctor && user->getId() == doctorId) {
            return *std::dynamic_pointer_cast<Doctor>(user);
        }
    }
    return std::nullopt;
}

std::vector<Doctor> AuthService::getDoctors() const
{
    std::vector<Doctor> doctors;
    for (const auto& user : users_) {
        if (user->getRole() == UserRole::Doctor) {
            doctors.push_back(*std::dynamic_pointer_cast<Doctor>(user));
        }
    }
    return doctors;
}
