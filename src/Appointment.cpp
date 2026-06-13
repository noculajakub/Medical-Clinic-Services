#include "Appointment.h"

/**
 * @brief Konstruktor klasy Appointment.
 * Inicjalizuje nowy obiekt wizyty z podanymi parametrami przy użyciu listy inicjalizacyjnej.
 * * @param id Unikalny identyfikator wizyty.
 * @param patientId Identyfikator pacjenta przypisanego do wizyty.
 * @param doctorId Identyfikator lekarza prowadzącego wizytę.
 * @param dateTime Data i godzina wizyty w formacie tekstowym (np. "YYYY-MM-DD HH:MM").
 */

Appointment::Appointment(int id, int patientId, int doctorId, const std::string& dateTime)
    : id_(id),
    patientId_(patientId),
    doctorId_(doctorId),
    dateTime_(dateTime)
{}

int Appointment::getId() const
{
    return id_;
}

int Appointment::getPatientId() const
{
    return patientId_;
}

int Appointment::getDoctorId() const
{
    return doctorId_;
}

std::string Appointment::getDateTime() const
{
    return dateTime_;
}

/**
 * @brief Aktualizuje datę i godzinę wizyty.
 * Używane przy zmianie terminu rezerwacji.
 * * @param dateTime Nowa data i czas wizyty w formacie tekstowym.
 */

void Appointment::setDateTime(const std::string& dateTime)
{
    dateTime_ = dateTime;
}
