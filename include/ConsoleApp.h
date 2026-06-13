#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include "ClinicSystem.h"

#include <memory>
#include <string>
#include <vector>

class ConsoleApp {
public:
    explicit ConsoleApp(ClinicSystem& clinicSystem);
    void run();

private:
    ClinicSystem& clinicSystem_;
    std::shared_ptr<User> currentUser_;

    void loginScreen();
    void receptionistMenu();
    void doctorMenu();

    void registerPatient();
    void searchPatient();
    void addAppointment();
    void removeAppointment();
    void changeAppointmentDate();
    void showAllDoctorsSchedule();
    void showOwnSchedule();
    void showPatientAppointments();
    void showPatientMedicalRecords();
    void createMedicalRecord();

    void printHeader(const std::string& title) const;
    void printMenu(const std::string& title, const std::vector<std::string>& options) const;
    void printPatients(const std::vector<Patient>& patients) const;
    void printDoctors(const std::vector<Doctor>& doctors) const;
    void printAppointments(const std::vector<Appointment>& appointments) const;
    void printMedicalRecords(const std::vector<MedicalRecord>& records) const;
    void printMessage(const std::string& message) const;

    int readInt(const std::string& prompt) const;
    int readMenuOption(int minValue, int maxValue) const;
    std::string readLine(const std::string& prompt) const;
    std::string readRequiredLine(const std::string& prompt) const;
    bool confirm(const std::string& prompt) const;
    void clearScreen() const;
    void waitForEnter() const;
};

#endif
