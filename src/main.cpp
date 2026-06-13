#include "ClinicSystem.h"
#include "ConsoleApp.h"

int main()
{
    ClinicSystem clinicSystem;
    ConsoleApp consoleApp(clinicSystem);
    consoleApp.run();
    return 0;
}
