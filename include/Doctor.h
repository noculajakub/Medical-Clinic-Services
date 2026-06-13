#ifndef DOCTOR_H
#define DOCTOR_H

#include "User.h"

#include <string>

class Doctor : public User {
public:
    Doctor(int id,
        const std::string& login,
        const std::string& password,
        const std::string& firstName,
        const std::string& lastName,
        const std::string& specialization);

    std::string getSpecialization() const;
    std::string getRoleName() const override;

private:
    std::string specialization_;
};

#endif
