#include "Doctor.h"

/**
 * @brief Definicja konstruktora klasy Doctor.
 * * Inicjalizuje klasę bazową User, ustawiając rolę użytkownika na UserRole::Doctor,
 * oraz przypisuje specjalizację lekarską do pola prywatnego.
 * * @param id Unikalny identyfikator lekarza.
 * @param login Login użytkownika do systemu.
 * @param password Hasło użytkownika.
 * @param firstName Imię lekarza.
 * @param lastName Nazwisko lekarza.
 * @param specialization Specjalizacja medyczna.
 */
Doctor::Doctor(int id,
    const std::string& login,
    const std::string& password,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& specialization)
    : User(id, login, password, firstName, lastName, UserRole::Doctor),
    specialization_(specialization)
{}

/**
 * @brief Zwraca zapisaną specjalizację lekarza.
 * @return std::string Specjalizacja medyczna (np. "Kardiolog").
 */
std::string Doctor::getSpecialization() const
{
    return specialization_;
}

/**
 * @brief Zwraca tekstową nazwę roli użytkownika.
 * @return std::string Stała wartość tekstowa "Lekarz".
 */
std::string Doctor::getRoleName() const
{
    return "Lekarz";
}