#include "ClinicSystem.h"

#include <algorithm>
#include <cctype>

ClinicSystem::ClinicSystem()
{
    seedData();
}

std::shared_ptr<User> ClinicSystem::login(const std::string& login, const std::string& password) const
{
    return authService_.login(login, password);
}

int ClinicSystem::registerPatient(const std::string& firstName,
                                  const std::string& lastName,
                                  const std::string& pesel,
                                  const std::string& phoneNumber)
{
    if (!isValidPatientData(firstName, lastName, pesel)) {
        return -1;
    }
    return patientManager_.addPatient(firstName, lastName, pesel, phoneNumber);
}

std::vector<Patient> ClinicSystem::searchPatientsByLastName(const std::string& lastName) const
{
    return patientManager_.findByLastName(lastName);
}

std::optional<Patient> ClinicSystem::findPatientByPesel(const std::string& pesel) const
{
    return patientManager_.findByPesel(pesel);
}

std::optional<Patient> ClinicSystem::findPatientById(int patientId) const
{
    return patientManager_.findById(patientId);
}

const std::vector<Patient>& ClinicSystem::getPatients() const
{
    return patientManager_.getAllPatients();
}

int ClinicSystem::addAppointment(int patientId, int doctorId, const std::string& dateTime)
{
    if (!patientManager_.patientExists(patientId) || !findDoctorById(doctorId).has_value() || !isValidDateText(dateTime)) {
        return -1;
    }
    return appointmentManager_.addAppointment(patientId, doctorId, dateTime);
}

bool ClinicSystem::removeAppointment(int appointmentId)
{
    return appointmentManager_.removeAppointment(appointmentId);
}

bool ClinicSystem::changeAppointmentDate(int appointmentId, const std::string& newDateTime)
{
    if (!isValidDateText(newDateTime)) {
        return false;
    }
    return appointmentManager_.changeAppointmentDate(appointmentId, newDateTime);
}

std::optional<Appointment> ClinicSystem::findAppointmentById(int appointmentId) const
{
    return appointmentManager_.findById(appointmentId);
}

std::vector<Appointment> ClinicSystem::getAppointmentsByDoctor(int doctorId) const
{
    return appointmentManager_.getAppointmentsByDoctor(doctorId);
}

std::vector<Appointment> ClinicSystem::getAppointmentsByPatient(int patientId) const
{
    return appointmentManager_.getAppointmentsByPatient(patientId);
}

const std::vector<Appointment>& ClinicSystem::getAppointments() const
{
    return appointmentManager_.getAllAppointments();
}

int ClinicSystem::createMedicalRecord(int patientId,
                                      int doctorId,
                                      const std::string& date,
                                      const std::string& diagnosis,
                                      const std::string& recommendations,
                                      const std::string& prescribedMedicines)
{
    if (!patientManager_.patientExists(patientId)
        || !findDoctorById(doctorId).has_value()
        || !isValidDateText(date)
        || diagnosis.empty()) {
        return -1;
    }

    const int recordId = nextMedicalRecordId_++;
    medicalRecords_.push_back(MedicalRecord(recordId,
                                            patientId,
                                            doctorId,
                                            date,
                                            diagnosis,
                                            recommendations,
                                            prescribedMedicines));
    return recordId;
}

std::vector<MedicalRecord> ClinicSystem::getMedicalRecordsByPatient(int patientId) const
{
    std::vector<MedicalRecord> result;
    for (const auto& record : medicalRecords_) {
        if (record.getPatientId() == patientId) {
            result.push_back(record);
        }
    }
    return result;
}

std::optional<Doctor> ClinicSystem::findDoctorById(int doctorId) const
{
    return authService_.findDoctorById(doctorId);
}

std::vector<Doctor> ClinicSystem::getDoctors() const
{
    return authService_.getDoctors();
}

void ClinicSystem::seedData()
{
    authService_.addReceptionist(Receptionist(1, "recepcja", "recepcja123", "Anna", "Recepcjonistka"));
    authService_.addDoctor(Doctor(101, "kowalska", "lek123", "Maria", "Kowalska", "internista"));
    authService_.addDoctor(Doctor(102, "nowak", "lek123", "Jan", "Nowak", "kardiolog"));
    authService_.addDoctor(Doctor(103, "zielinski", "lek123", "Pawel", "Zielinski", "pediatra"));

    const int patientId = registerPatient("Adam", "Testowy", "90010112345", "500600700");
    const int secondPatientId = registerPatient("Ewa", "Kowal", "92020212345", "600700800");
    addAppointment(patientId, 101, "2026-06-15 10:00");
    addAppointment(secondPatientId, 102, "2026-06-15 11:30");
    createMedicalRecord(patientId,
                        101,
                        "2026-06-01",
                        "Kontrola okresowa",
                        "Kontynuowac zdrowy tryb zycia",
                        "Brak");
}

bool ClinicSystem::isValidPatientData(const std::string& firstName,
                                      const std::string& lastName,
                                      const std::string& pesel) const
{
    if (firstName.empty() || lastName.empty() || pesel.size() != 11) {
        return false;
    }

    return std::all_of(pesel.begin(), pesel.end(), [](unsigned char character) {
        return std::isdigit(character);
    });
}

bool ClinicSystem::isValidDateText(const std::string& dateText) const
{
    return dateText.size() >= 10;
}
