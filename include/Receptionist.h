#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "User.h"

#include <string>

class Receptionist : public User {
public:
    Receptionist(int id,
                 const std::string& login,
                 const std::string& password,
                 const std::string& firstName,
                 const std::string& lastName);

    std::string getRoleName() const override;
};

#endif
