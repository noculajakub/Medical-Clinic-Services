#include "ClinicSystem.h"

#include <iostream>
#include <string>

class TestRunner {
public:
    void assertTrue(bool condition, const std::string& testName)
    {
        if (condition) {
            ++passed_;
            std::cout << "[OK] " << testName << "\n";
        } else {
            ++failed_;
            std::cout << "[FAIL] " << testName << "\n";
        }
    }

    int result() const
    {
        std::cout << "\nPassed: " << passed_ << ", failed: " << failed_ << "\n";
        return failed_ == 0 ? 0 : 1;
    }

private:
    int passed_{0};
    int failed_{0};
};

void testAddingPatient(TestRunner& runner)
{
    ClinicSystem system;

    const int patientId = system.registerPatient("Jan", "Kowal", "81010112345", "123123123");

    runner.assertTrue(patientId > 0, "dodawanie pacjenta");
    runner.assertTrue(system.findPatientByPesel("81010112345").has_value(), "wyszukiwanie pacjenta po PESEL");
    runner.assertTrue(!system.searchPatientsByLastName("Kowal").empty(), "wyszukiwanie pacjenta po nazwisku");
    runner.assertTrue(system.registerPatient("Jan", "Kowal", "81010112345", "123123123") == -1,
                      "blokada duplikatu PESEL");
}

int main()
{
    TestRunner runner;
    testAddingPatient(runner);
    return runner.result();
}
