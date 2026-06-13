#ifndef CLINIC_SYSTEM_H
#define CLINIC_SYSTEM_H

#include "AppointmentManager.h"
#include "AuthService.h"
#include "MedicalRecord.h"
#include "PatientManager.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

class ClinicSystem {
public:
    ClinicSystem();

    std::shared_ptr<User> login(const std::string& login, const std::string& password) const;

    int registerPatient(const std::string& firstName,
                        const std::string& lastName,
                        const std::string& pesel,
                        const std::string& phoneNumber);
    std::vector<Patient> searchPatientsByLastName(const std::string& lastName) const;
    std::optional<Patient> findPatientByPesel(const std::string& pesel) const;
    std::optional<Patient> findPatientById(int patientId) const;
    const std::vector<Patient>& getPatients() const;

    int addAppointment(int patientId, int doctorId, const std::string& dateTime);
    bool removeAppointment(int appointmentId);
    bool changeAppointmentDate(int appointmentId, const std::string& newDateTime);
    std::optional<Appointment> findAppointmentById(int appointmentId) const;
    std::vector<Appointment> getAppointmentsByDoctor(int doctorId) const;
    std::vector<Appointment> getAppointmentsByPatient(int patientId) const;
    const std::vector<Appointment>& getAppointments() const;

    int createMedicalRecord(int patientId,
                            int doctorId,
                            const std::string& date,
                            const std::string& diagnosis,
                            const std::string& recommendations,
                            const std::string& prescribedMedicines);
    std::vector<MedicalRecord> getMedicalRecordsByPatient(int patientId) const;

    std::optional<Doctor> findDoctorById(int doctorId) const;
    std::vector<Doctor> getDoctors() const;

private:
    AuthService authService_;
    PatientManager patientManager_;
    AppointmentManager appointmentManager_;
    std::vector<MedicalRecord> medicalRecords_;
    int nextMedicalRecordId_{1};

    void seedData();
    bool isValidPatientData(const std::string& firstName,
                            const std::string& lastName,
                            const std::string& pesel) const;
    bool isValidDateText(const std::string& dateText) const;
};

#endif
