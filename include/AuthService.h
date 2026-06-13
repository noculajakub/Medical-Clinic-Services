#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include "Doctor.h"
#include "Receptionist.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

class AuthService {
public:
    void addDoctor(const Doctor& doctor);
    void addReceptionist(const Receptionist& receptionist);

    std::shared_ptr<User> login(const std::string& login, const std::string& password) const;
    std::optional<Doctor> findDoctorById(int doctorId) const;
    std::vector<Doctor> getDoctors() const;

private:
    std::vector<std::shared_ptr<User>> users_;
};

#endif
