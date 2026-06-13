#include "AppointmentManager.h"

#include <algorithm>

/**
 * @brief Dodaje nową rezerwację wizyty do systemu.
 * Przed dodaniem sprawdza, czy lekarz nie ma już zaplanowanej wizyty w podanym terminie.
 * * @param patientId ID pacjenta, dla którego rezerwowana jest wizyta.
 * @param doctorId ID lekarza, do którego przypisana jest wizyta.
 * @param dateTime Data i godzina wizyty w formacie tekstowym.
 * @return int Zwraca wygenerowane ID nowej wizyty lub -1, jeśli termin koliduje z inną wizytą lekarza.
 */

int AppointmentManager::addAppointment(int patientId, int doctorId, const std::string& dateTime)
{
    if (hasDoctorConflict(doctorId, dateTime)) {
        return -1;
    }

    const int appointmentId = nextAppointmentId_++;
    appointments_.push_back(Appointment(appointmentId, patientId, doctorId, dateTime));
    return appointmentId;
}


/**
 * @brief Usuwa wizytę z systemu na podstawie jej identyfikatora.
 * Wykorzystuje idiom erase-remove do bezpiecznego usunięcia elementu z wektora.
 * * @param appointmentId ID wizyty, która ma zostać anulowana/usunięta.
 * @return true Jeśli wizyta została znaleziona i pomyślnie usunięta.
 * @return false Jeśli wizyta o podanym ID nie istnieje w systemie.
 */

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

/**
 * @brief Zmienia termin istniejącej wizyty.
 * Sprawdza również, czy nowy termin nie powoduje konfliktu w harmonogramie lekarza
 * (z pominięciem obecnie edytowanej wizyty).
 * * @param appointmentId ID wizyty do zmiany terminu.
 * @param newDateTime Nowa data i godzina rezerwacji.
 * @return true Jeśli zmiana terminu zakończyła się sukcesem.
 * @return false Jeśli wizyta nie istnieje lub nowy termin jest już zajęty przez tego samego lekarza.
 */

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
