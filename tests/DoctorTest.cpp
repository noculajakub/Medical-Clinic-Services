#include "ClinicSystem.h"
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

void testDoctorDoubleBookingBlock(TestRunner& runner)
{
    ClinicSystem system;
    const int firstPatientId = system.registerPatient("Ala", "Pierwsza", "84010112345", "111");
    const int secondPatientId = system.registerPatient("Ola", "Druga", "85010112345", "222");

    const int firstAppointmentId = system.addAppointment(firstPatientId, 101, "2026-06-21 09:00");
    const int secondAppointmentId = system.addAppointment(secondPatientId, 101, "2026-06-21 09:00");

    runner.assertTrue(firstAppointmentId > 0, "pierwsza wizyta lekarza w terminie");
    runner.assertTrue(secondAppointmentId == -1, "blokada podwojnej wizyty u lekarza");
}

int main() {
    TestRunner runner;
    testDoctorDoubleBookingBlock(runner);

    return runner.result();
}