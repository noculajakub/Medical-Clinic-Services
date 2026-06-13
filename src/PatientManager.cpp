#include "PatientManager.h"

#include <algorithm>

int PatientManager::addPatient(const std::string& firstName,
                               const std::string& lastName,
                               const std::string& pesel,
                               const std::string& phoneNumber)
{
    if (!isPeselAvailable(pesel)) {
        return -1;
    }

    const int patientId = nextPatientId_++;
    patients_.push_back(Patient(patientId, firstName, lastName, pesel, phoneNumber));
    return patientId;
}

bool PatientManager::patientExists(int patientId) const
{
    return findById(patientId).has_value();
}

bool PatientManager::isPeselAvailable(const std::string& pesel) const
{
    return !findByPesel(pesel).has_value();
}

std::optional<Patient> PatientManager::findById(int patientId) const
{
    const auto patient = std::find_if(patients_.begin(), patients_.end(),
                                      [patientId](const Patient& item) {
                                          return item.getId() == patientId;
                                      });
    if (patient == patients_.end()) {
        return std::nullopt;
    }
    return *patient;
}

std::optional<Patient> PatientManager::findByPesel(const std::string& pesel) const
{
    const auto patient = std::find_if(patients_.begin(), patients_.end(),
                                      [&pesel](const Patient& item) {
                                          return item.getPesel() == pesel;
                                      });
    if (patient == patients_.end()) {
        return std::nullopt;
    }
    return *patient;
}

std::vector<Patient> PatientManager::findByLastName(const std::string& lastName) const
{
    std::vector<Patient> result;
    for (const auto& patient : patients_) {
        if (patient.getLastName() == lastName) {
            result.push_back(patient);
        }
    }
    return result;
}

const std::vector<Patient>& PatientManager::getAllPatients() const
{
    return patients_;
}
