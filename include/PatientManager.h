#ifndef PATIENT_MANAGER_H
#define PATIENT_MANAGER_H

#include "Patient.h"

#include <optional>
#include <string>
#include <vector>

class PatientManager {
public:
    int addPatient(const std::string& firstName,
                   const std::string& lastName,
                   const std::string& pesel,
                   const std::string& phoneNumber);

    bool patientExists(int patientId) const;
    bool isPeselAvailable(const std::string& pesel) const;
    std::optional<Patient> findById(int patientId) const;
    std::optional<Patient> findByPesel(const std::string& pesel) const;
    std::vector<Patient> findByLastName(const std::string& lastName) const;
    const std::vector<Patient>& getAllPatients() const;

private:
    std::vector<Patient> patients_;
    int nextPatientId_{1};
};

#endif
