#include <iostream>
#include <string>

class TestRunner {
public:
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            ++passed_;
            std::cout << "[OK] " << testName << "\n";
        }
        else {
            ++failed_;
            std::cout << "[FAIL] " << testName << "\n";
        }
    }

    int result() const {
        std::cout << "\nPassed: " << passed_ << ", failed: " << failed_ << "\n";
        return failed_ == 0 ? 0 : 1;
    }

private:
    int passed_{ 0 };
    int failed_{ 0 };
};

void testLogin(TestRunner& runner) {
    ClinicSystem system;
    runner.assertTrue(system.login("recepcja", "recepcja123") != nullptr, "logowanie poprawnymi danymi");
    runner.assertTrue(system.login("recepcja", "bledne") == nullptr, "odrzucenie blednego hasla");
}

void testAddingAppointment(TestRunner& runner) {
    ClinicSystem system;
    const int patientId = system.registerPatient("Jan", "Wizyta", "83010112345", "111222333");
    const int appointmentId = system.addAppointment(patientId, 101, "2026-06-20 10:00");

    runner.assertTrue(appointmentId > 0, "dodawanie wizyty");
    runner.assertTrue(!system.getAppointmentsByPatient(patientId).empty(), "wyswietlanie wizyt pacjenta");
}

void testChangingAppointmentDate(TestRunner& runner) {
    ClinicSystem system;
    const int patientId = system.registerPatient("Jan", "Zmiana", "86010112345", "333");
    const int appointmentId = system.addAppointment(patientId, 101, "2026-06-22 09:00");

    const bool changed = system.changeAppointmentDate(appointmentId, "2026-06-22 12:00");

    runner.assertTrue(changed, "zmiana terminu wizyty");
    runner.assertTrue(system.findAppointmentById(appointmentId)->getDateTime() == "2026-06-22 12:00", "wizyta ma nowy termin");
}

int main() {
    TestRunner runner;
    testLogin(runner);
    testAddingAppointment(runner);
    testChangingAppointmentDate(runner);

    return runner.result();
}