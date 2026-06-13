#ifndef APPOINTMENT_MANAGER_H
#define APPOINTMENT_MANAGER_H

#include "Appointment.h"

#include <optional>
#include <string>
#include <vector>

/**
 * @brief Moduł zarządzający rezerwacjami wizyt oraz harmonogramem dostępności lekarzy.
 */

class AppointmentManager {
public:

    /**
     * @brief Tworzy nową wizytę. Zwraca wygenerowane ID lub -1, jeśli termin jest już zajęty.
     */
    int addAppointment(int patientId, int doctorId, const std::string& dateTime);
    bool removeAppointment(int appointmentId);

    /**
     * @brief Zmienia termin istniejącej wizyty, pilnując, aby nowy termin nie powodował konfliktów.
     */
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
