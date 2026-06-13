#ifndef APPOINTMENT_MANAGER_H
#define APPOINTMENT_MANAGER_H

#include "Appointment.h"

#include <optional>
#include <string>
#include <vector>

class AppointmentManager {
public:
    int addAppointment(int patientId, int doctorId, const std::string& dateTime);
    bool removeAppointment(int appointmentId);
    bool changeAppointmentDate(int appointmentId, const std::string& newDateTime);
    bool hasDoctorConflict(int doctorId, const std::string& dateTime) const;
    bool hasDoctorConflictExcluding(int doctorId, const std::string& dateTime, int ignoredAppointmentId) const;

    std::optional<Appointment> findById(int appointmentId) const;
    std::vector<Appointment> getAppointmentsByDoctor(int doctorId) const;
    std::vector<Appointment> getAppointmentsByPatient(int patientId) const;
    const std::vector<Appointment>& getAllAppointments() const;

private:
    std::vector<Appointment> appointments_;
    int nextAppointmentId_{ 1 };
};

#endif
