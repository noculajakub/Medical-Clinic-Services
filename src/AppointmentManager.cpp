#include "AppointmentManager.h"

#include <algorithm>

int AppointmentManager::addAppointment(int patientId, int doctorId, const std::string& dateTime)
{
    if (hasDoctorConflict(doctorId, dateTime)) {
        return -1;
    }

    const int appointmentId = nextAppointmentId_++;
    appointments_.push_back(Appointment(appointmentId, patientId, doctorId, dateTime));
    return appointmentId;
}

bool AppointmentManager::removeAppointment(int appointmentId)
{
    const auto oldSize = appointments_.size();
    appointments_.erase(std::remove_if(appointments_.begin(), appointments_.end(),
        [appointmentId](const Appointment& item) {
            return item.getId() == appointmentId;
        }),
        appointments_.end());
    return appointments_.size() != oldSize;
}

bool AppointmentManager::changeAppointmentDate(int appointmentId, const std::string& newDateTime)
{
    auto appointment = std::find_if(appointments_.begin(), appointments_.end(),
        [appointmentId](const Appointment& item) {
            return item.getId() == appointmentId;
        });
    if (appointment == appointments_.end()) {
        return false;
    }

    if (hasDoctorConflictExcluding(appointment->getDoctorId(), newDateTime, appointmentId)) {
        return false;
    }

    appointment->setDateTime(newDateTime);
    return true;
}

bool AppointmentManager::hasDoctorConflict(int doctorId, const std::string& dateTime) const
{
    return hasDoctorConflictExcluding(doctorId, dateTime, -1);
}

bool AppointmentManager::hasDoctorConflictExcluding(int doctorId,
    const std::string& dateTime,
    int ignoredAppointmentId) const
{
    return std::any_of(appointments_.begin(), appointments_.end(),
        [doctorId, &dateTime, ignoredAppointmentId](const Appointment& item) {
            return item.getId() != ignoredAppointmentId
                && item.getDoctorId() == doctorId
                && item.getDateTime() == dateTime;
        });
}

std::optional<Appointment> AppointmentManager::findById(int appointmentId) const
{
    const auto appointment = std::find_if(appointments_.begin(), appointments_.end(),
        [appointmentId](const Appointment& item) {
            return item.getId() == appointmentId;
        });
    if (appointment == appointments_.end()) {
        return std::nullopt;
    }
    return *appointment;
}

std::vector<Appointment> AppointmentManager::getAppointmentsByDoctor(int doctorId) const
{
    std::vector<Appointment> result;
    for (const auto& appointment : appointments_) {
        if (appointment.getDoctorId() == doctorId) {
            result.push_back(appointment);
        }
    }
    return result;
}

std::vector<Appointment> AppointmentManager::getAppointmentsByPatient(int patientId) const
{
    std::vector<Appointment> result;
    for (const auto& appointment : appointments_) {
        if (appointment.getPatientId() == patientId) {
            result.push_back(appointment);
        }
    }
    return result;
}

const std::vector<Appointment>& AppointmentManager::getAllAppointments() const
{
    return appointments_;
}
