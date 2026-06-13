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

void testCreatingMedicalRecord(TestRunner& runner)
{
    ClinicSystem system;
    const int patientId = system.registerPatient("Jan", "Dokument", "87010112345", "444");

    const int recordId = system.createMedicalRecord(patientId,
        101,
        "2026-06-23",
        "Grypa",
        "Odpoczynek",
        "Paracetamol");

    runner.assertTrue(recordId > 0, "tworzenie dokumentacji medycznej");
    runner.assertTrue(system.getMedicalRecordsByPatient(patientId).size() == 1,
        "pobranie dokumentacji medycznej pacjenta");
}

int main() {
    TestRunner runner;
    testCreatingMedicalRecord(runner);

    return runner.result();
}