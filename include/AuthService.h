#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include "Doctor.h"
#include "Receptionist.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

/**
 * @brief Serwis zarządzający autoryzacją oraz bazą użytkowników w systemie.
 */

class AuthService {
public:
    void addDoctor(const Doctor& doctor);
    void addReceptionist(const Receptionist& receptionist);
    /**
         * @brief Zwraca wskaźnik na zalogowanego użytkownika lub nullptr przy błędnych danych.
         */
    std::shared_ptr<User> login(const std::string& login, const std::string& password) const;
    std::optional<Doctor> findDoctorById(int doctorId) const;
    std::vector<Doctor> getDoctors() const;

private:
    /**
     * @brief Polimorficzna lista wszystkich użytkowników systemu (lekarzy i recepcji).
     */
    std::vector<std::shared_ptr<User>> users_;
};

#endif
