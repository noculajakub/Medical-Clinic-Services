#include "Appointment.h"

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

void Appointment::setDateTime(const std::string& dateTime)
{
    dateTime_ = dateTime;
}
