#include "Doctor.h"

Doctor::Doctor(int id,
    const std::string& login,
    const std::string& password,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& specialization)
    : User(id, login, password, firstName, lastName, UserRole::Doctor),
    specialization_(specialization)
{}

std::string Doctor::getSpecialization() const
{
    return specialization_;
}

std::string Doctor::getRoleName() const
{
    return "Lekarz";
}