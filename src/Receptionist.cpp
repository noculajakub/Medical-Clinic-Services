#include "Receptionist.h"

Receptionist::Receptionist(int id,
                           const std::string& login,
                           const std::string& password,
                           const std::string& firstName,
                           const std::string& lastName)
    : User(id, login, password, firstName, lastName, UserRole::Receptionist)
{
}

std::string Receptionist::getRoleName() const
{
    return "Recepcja";
}
