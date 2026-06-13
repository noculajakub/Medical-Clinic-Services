#include "ConsoleApp.h"

#include <iomanip>
#include <iostream>
#include <limits>

namespace {
    constexpr int kWidth = 96;

    std::string line(char character = '-')
    {
        return std::string(kWidth, character);
    }
}

ConsoleApp::ConsoleApp(ClinicSystem& clinicSystem)
    : clinicSystem_(clinicSystem)
{}

void ConsoleApp::run()
{
    bool running = true;
    while (running) {
        loginScreen();
        if (!currentUser_) {
            running = false;
        }
        else if (currentUser_->getRole() == UserRole::Receptionist) {
            receptionistMenu();
        }
        else {
            doctorMenu();
        }
    }
}

void ConsoleApp::loginScreen()
{
    currentUser_.reset();

    while (!currentUser_) {
        clearScreen();
        printHeader("LOGOWANIE DO SYSTEMU PRZYCHODNI");
        std::cout << "Konta testowe:\n"
            << "  Recepcja: login recepcja, haslo recepcja123\n"
            << "  Lekarz:   login kowalska, haslo lek123\n"
            << "  Lekarz:   login nowak, haslo lek123\n"
            << "\nWpisz 0 jako login, aby zamknac program.\n";

        const std::string login = readRequiredLine("Login: ");
        if (login == "0") {
            return;
        }

        const std::string password = readRequiredLine("Haslo: ");
        currentUser_ = clinicSystem_.login(login, password);

        if (!currentUser_) {
            printMessage("Niepoprawny login lub haslo.");
        }
    }
}

void ConsoleApp::receptionistMenu()
{
    bool loggedIn = true;
    while (loggedIn) {
        clearScreen();
        printMenu("PANEL RECEPCJI - " + currentUser_->getFullName(),
            { "1. Rejestracja nowego pacjenta",
             "2. Wyszukiwanie pacjenta po PESEL lub nazwisku",
             "3. Dodawanie wizyty",
             "4. Usuwanie wizyty",
             "5. Zmiana daty wizyty",
             "6. Wglad do terminarza lekarzy",
             "7. Wizyty danego pacjenta",
             "8. Wglad do dokumentacji medycznej pacjenta",
             "0. Wyloguj" });

        switch (readMenuOption(0, 8)) {
        case 1:
            registerPatient();
            break;
        case 2:
            searchPatient();
            break;
        case 3:
            addAppointment();
            break;
        case 4:
            removeAppointment();
            break;
        case 5:
            changeAppointmentDate();
            break;
        case 6:
            showAllDoctorsSchedule();
            break;
        case 7:
            showPatientAppointments();
            break;
        case 8:
            showPatientMedicalRecords();
            break;
        case 0:
            loggedIn = false;
            currentUser_.reset();
            break;
        }
    }
}

void ConsoleApp::doctorMenu()
{
    bool loggedIn = true;
    while (loggedIn) {
        clearScreen();
        printMenu("PANEL LEKARZA - " + currentUser_->getFullName(),
            { "1. Wglad do wlasnego terminarza",
             "2. Wyszukiwanie pacjenta po PESEL lub nazwisku",
             "3. Wizyty danego pacjenta",
             "4. Wglad do dokumentacji medycznej pacjenta",
             "5. Tworzenie dokumentacji medycznej pacjenta",
             "0. Wyloguj" });

        switch (readMenuOption(0, 5)) {
        case 1:
            showOwnSchedule();
            break;
        case 2:
            searchPatient();
            break;
        case 3:
            showPatientAppointments();
            break;
        case 4:
            showPatientMedicalRecords();
            break;
        case 5:
            createMedicalRecord();
            break;
        case 0:
            loggedIn = false;
            currentUser_.reset();
            break;
        }
    }
}

void ConsoleApp::registerPatient()
{
    clearScreen();
    printHeader("REJESTRACJA NOWEGO PACJENTA");

    const std::string firstName = readRequiredLine("Imie: ");
    const std::string lastName = readRequiredLine("Nazwisko: ");
    const std::string pesel = readRequiredLine("PESEL, 11 cyfr: ");
    const std::string phoneNumber = readLine("Telefon: ");

    const int patientId = clinicSystem_.registerPatient(firstName, lastName, pesel, phoneNumber);
    if (patientId == -1) {
        printMessage("Nie dodano pacjenta. Sprawdz dane lub unikalnosc numeru PESEL.");
        return;
    }

    printMessage("Dodano pacjenta. ID pacjenta: " + std::to_string(patientId));
}

void ConsoleApp::searchPatient()
{
    clearScreen();
    printMenu("WYSZUKIWANIE PACJENTA",
        { "1. Szukaj po PESEL",
         "2. Szukaj po nazwisku",
         "0. Powrot" });

    const int option = readMenuOption(0, 2);
    if (option == 0) {
        return;
    }

    if (option == 1) {
        const std::string pesel = readRequiredLine("PESEL: ");
        const auto patient = clinicSystem_.findPatientByPesel(pesel);
        if (!patient) {
            printMessage("Nie znaleziono pacjenta.");
            return;
        }
        printPatients({ *patient });
    }
    else {
        const std::string lastName = readRequiredLine("Nazwisko: ");
        printPatients(clinicSystem_.searchPatientsByLastName(lastName));
    }

    waitForEnter();
}

void ConsoleApp::addAppointment()
{
    clearScreen();
    printHeader("DODAWANIE WIZYTY");
    printPatients(clinicSystem_.getPatients());
    const int patientId = readInt("ID pacjenta: ");

    printDoctors(clinicSystem_.getDoctors());
    const int doctorId = readInt("ID lekarza: ");
    const std::string dateTime = readRequiredLine("Termin (np. 2026-06-15 12:30): ");

    const int appointmentId = clinicSystem_.addAppointment(patientId, doctorId, dateTime);
    if (appointmentId == -1) {
        printMessage("Nie dodano wizyty. Sprawdz dane albo konflikt terminu lekarza.");
        return;
    }

    printMessage("Dodano wizyte. ID wizyty: " + std::to_string(appointmentId));
}

void ConsoleApp::removeAppointment()
{
    clearScreen();
    printHeader("USUWANIE WIZYTY");
    printAppointments(clinicSystem_.getAppointments());

    const int appointmentId = readInt("ID wizyty: ");
    if (!clinicSystem_.findAppointmentById(appointmentId)) {
        printMessage("Nie znaleziono wizyty.");
        return;
    }

    if (!confirm("Czy na pewno usunac wizyte?")) {
        printMessage("Anulowano.");
        return;
    }

    clinicSystem_.removeAppointment(appointmentId);
    printMessage("Usunieto wizyte.");
}

void ConsoleApp::changeAppointmentDate()
{
    clearScreen();
    printHeader("ZMIANA DATY WIZYTY");
    printAppointments(clinicSystem_.getAppointments());

    const int appointmentId = readInt("ID wizyty: ");
    const std::string newDateTime = readRequiredLine("Nowy termin: ");
    if (clinicSystem_.changeAppointmentDate(appointmentId, newDateTime)) {
        printMessage("Zmieniono termin wizyty.");
        return;
    }

    printMessage("Nie zmieniono terminu. Wizyta nie istnieje albo lekarz ma juz wizyte w tym terminie.");
}

void ConsoleApp::showAllDoctorsSchedule()
{
    clearScreen();
    printHeader("TERMINARZE LEKARZY");
    for (const auto& doctor : clinicSystem_.getDoctors()) {
        std::cout << "\nLekarz: " << doctor.getFullName()
            << " (" << doctor.getSpecialization() << ")\n";
        printAppointments(clinicSystem_.getAppointmentsByDoctor(doctor.getId()));
    }
    waitForEnter();
}

void ConsoleApp::showOwnSchedule()
{
    clearScreen();
    printHeader("MOJ TERMINARZ");
    printAppointments(clinicSystem_.getAppointmentsByDoctor(currentUser_->getId()));
    waitForEnter();
}

void ConsoleApp::showPatientAppointments()
{
    clearScreen();
    printHeader("WIZYTY PACJENTA");
    printPatients(clinicSystem_.getPatients());

    const int patientId = readInt("ID pacjenta: ");
    if (!clinicSystem_.findPatientById(patientId)) {
        printMessage("Nie znaleziono pacjenta.");
        return;
    }

    printAppointments(clinicSystem_.getAppointmentsByPatient(patientId));
    waitForEnter();
}

void ConsoleApp::showPatientMedicalRecords()
{
    clearScreen();
    printHeader("DOKUMENTACJA MEDYCZNA PACJENTA");
    printPatients(clinicSystem_.getPatients());

    const int patientId = readInt("ID pacjenta: ");
    if (!clinicSystem_.findPatientById(patientId)) {
        printMessage("Nie znaleziono pacjenta.");
        return;
    }

    printMedicalRecords(clinicSystem_.getMedicalRecordsByPatient(patientId));
    waitForEnter();
}

void ConsoleApp::createMedicalRecord()
{
    clearScreen();
    printHeader("TWORZENIE DOKUMENTACJI MEDYCZNEJ");
    printPatients(clinicSystem_.getPatients());

    const int patientId = readInt("ID pacjenta: ");
    const int doctorId = currentUser_->getId();
    const std::string date = readRequiredLine("Data wpisu: ");
    const std::string diagnosis = readRequiredLine("Diagnoza: ");
    const std::string recommendations = readLine("Zalecenia: ");
    const std::string medicines = readLine("Przepisane leki: ");

    const int recordId = clinicSystem_.createMedicalRecord(patientId,
        doctorId,
        date,
        diagnosis,
        recommendations,
        medicines);
    if (recordId == -1) {
        printMessage("Nie utworzono dokumentacji. Sprawdz pacjenta i wymagane pola.");
        return;
    }

    printMessage("Utworzono wpis dokumentacji. ID wpisu: " + std::to_string(recordId));
}

void ConsoleApp::printHeader(const std::string& title) const
{
    std::cout << line('=') << "\n"
        << title << "\n"
        << line('=') << "\n";
}

void ConsoleApp::printMenu(const std::string& title, const std::vector<std::string>& options) const
{
    printHeader(title);
    for (const auto& option : options) {
        std::cout << option << "\n";
    }
}

void ConsoleApp::printPatients(const std::vector<Patient>& patients) const
{
    std::cout << "\nPacjenci\n" << line() << "\n";
    if (patients.empty()) {
        std::cout << "Brak danych.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(28) << "Imie i nazwisko"
        << std::setw(16) << "PESEL"
        << "Telefon\n"
        << line() << "\n";

    for (const auto& patient : patients) {
        std::cout << std::left
            << std::setw(6) << patient.getId()
            << std::setw(28) << patient.getFullName()
            << std::setw(16) << patient.getPesel()
            << patient.getPhoneNumber() << "\n";
    }
}

void ConsoleApp::printDoctors(const std::vector<Doctor>& doctors) const
{
    std::cout << "\nLekarze\n" << line() << "\n";
    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(28) << "Imie i nazwisko"
        << "Specjalizacja\n"
        << line() << "\n";

    for (const auto& doctor : doctors) {
        std::cout << std::left
            << std::setw(6) << doctor.getId()
            << std::setw(28) << doctor.getFullName()
            << doctor.getSpecialization() << "\n";
    }
}

void ConsoleApp::printAppointments(const std::vector<Appointment>& appointments) const
{
    std::cout << "\nWizyty\n" << line() << "\n";
    if (appointments.empty()) {
        std::cout << "Brak wizyt.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(20) << "Termin"
        << std::setw(28) << "Pacjent"
        << "Lekarz\n"
        << line() << "\n";

    for (const auto& appointment : appointments) {
        const auto patient = clinicSystem_.findPatientById(appointment.getPatientId());
        const auto doctor = clinicSystem_.findDoctorById(appointment.getDoctorId());
        std::cout << std::left
            << std::setw(6) << appointment.getId()
            << std::setw(20) << appointment.getDateTime()
            << std::setw(28) << (patient ? patient->getFullName() : "nieznany")
            << (doctor ? doctor->getFullName() : "nieznany") << "\n";
    }
}

void ConsoleApp::printMedicalRecords(const std::vector<MedicalRecord>& records) const
{
    std::cout << "\nDokumentacja\n" << line() << "\n";
    if (records.empty()) {
        std::cout << "Brak dokumentacji.\n";
        return;
    }

    for (const auto& record : records) {
        const auto doctor = clinicSystem_.findDoctorById(record.getDoctorId());
        std::cout << "ID: " << record.getId() << "\n"
            << "Data: " << record.getDate() << "\n"
            << "Lekarz: " << (doctor ? doctor->getFullName() : "nieznany") << "\n"
            << "Diagnoza: " << record.getDiagnosis() << "\n"
            << "Zalecenia: " << record.getRecommendations() << "\n"
            << "Leki: " << record.getPrescribedMedicines() << "\n"
            << line() << "\n";
    }
}

void ConsoleApp::printMessage(const std::string& message) const
{
    std::cout << "\n" << line() << "\n"
        << message << "\n"
        << line() << "\n";
    waitForEnter();
}

int ConsoleApp::readInt(const std::string& prompt) const
{
    int value{};
    while (true) {
        std::cout << "\n" << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Podaj liczbe.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int ConsoleApp::readMenuOption(int minValue, int maxValue) const
{
    while (true) {
        const int option = readInt("Wybor: ");
        if (option >= minValue && option <= maxValue) {
            return option;
        }
        std::cout << "Wybierz opcje z zakresu " << minValue << "-" << maxValue << ".\n";
    }
}

std::string ConsoleApp::readLine(const std::string& prompt) const
{
    std::string value;
    std::cout << "\n" << prompt;
    std::getline(std::cin, value);
    return value;
}

std::string ConsoleApp::readRequiredLine(const std::string& prompt) const
{
    while (true) {
        const std::string value = readLine(prompt);
        if (!value.empty()) {
            return value;
        }
        std::cout << "Pole jest wymagane.\n";
    }
}

bool ConsoleApp::confirm(const std::string& prompt) const
{
    while (true) {
        const std::string answer = readRequiredLine(prompt + " (t/n): ");
        if (answer == "t" || answer == "T") {
            return true;
        }
        if (answer == "n" || answer == "N") {
            return false;
        }
        std::cout << "Wpisz t albo n.\n";
    }
}

void ConsoleApp::clearScreen() const
{
    std::cout << "\033[2J\033[H";
}

void ConsoleApp::waitForEnter() const
{
    std::cout << "\nNacisnij Enter, aby kontynuowac...";
    std::cin.get();
}
