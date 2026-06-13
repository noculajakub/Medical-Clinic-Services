#include "Patient.h"

Patient::Patient(int id,
                 const std::string& firstName,
                 const std::string& lastName,
                 const std::string& pesel,
                 const std::string& phoneNumber)
    : id_(id),
      firstName_(firstName),
      lastName_(lastName),
      pesel_(pesel),
      phoneNumber_(phoneNumber)
{
}

int Patient::getId() const
{
    return id_;
}

std::string Patient::getFirstName() const
{
    return firstName_;
}

std::string Patient::getLastName() const
{
    return lastName_;
}

std::string Patient::getFullName() const
{
    return firstName_ + " " + lastName_;
}

std::string Patient::getPesel() const
{
    return pesel_;
}

std::string Patient::getPhoneNumber() const
{
    return phoneNumber_;
}
