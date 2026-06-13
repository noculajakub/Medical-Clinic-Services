#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
public:
    Appointment(int id, int patientId, int doctorId, const std::string& dateTime);

    int getId() const;
    int getPatientId() const;
    int getDoctorId() const;
    std::string getDateTime() const;
    void setDateTime(const std::string& dateTime);

private:
    int id_;
    int patientId_;
    int doctorId_;
    std::string dateTime_;
};

#endif
