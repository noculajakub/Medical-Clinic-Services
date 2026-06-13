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

std::shared_ptr<User> AuthService::login(const std::string& login, const std::string& password) const
{
    for (const auto& user : users_) {
        if (user->getLogin() == login && user->getPassword() == password) {
            return user;
        }
    }
    return nullptr;
}

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
