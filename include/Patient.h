#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient {
public:
    Patient(int id,
            const std::string& firstName,
            const std::string& lastName,
            const std::string& pesel,
            const std::string& phoneNumber);

    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    std::string getPesel() const;
    std::string getPhoneNumber() const;

private:
    int id_;
    std::string firstName_;
    std::string lastName_;
    std::string pesel_;
    std::string phoneNumber_;
};

#endif
