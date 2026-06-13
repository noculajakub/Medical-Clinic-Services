#ifndef DOCTOR_H
#define DOCTOR_H

#include "User.h"

#include <string>

/**
 * @brief Klasa reprezentująca lekarza w systemie, dziedzicząca po klasie User.
 * * Rozszerza podstawowe dane użytkownika o specjalizację medyczną.
 */
class Doctor : public User {
public:
    /**
     * @brief Konstruktor obiektu klasy Doctor.
     * * @param id Unikalny identyfikator lekarza.
     * @param login Login użytkownika do systemu.
     * @param password Hasło użytkownika.
     * @param firstName Imię lekarza.
     * @param lastName Nazwisko lekarza.
     * @param specialization Specjalizacja medyczna (np. "Kardiolog").
     */
    Doctor(int id,
        const std::string& login,
        const std::string& password,
        const std::string& firstName,
        const std::string& lastName,
        const std::string& specialization);

    /**
     * @brief Pobiera specjalizację lekarza.
     * @return std::string Ciąg znaków reprezentujący specjalizację.
     */
    std::string getSpecialization() const;

    /**
     * @brief Pobiera nazwę roli użytkownika w języku polskim.
     * @return std::string Tekst "Lekarz".
     */ 
    std::string getRoleName() const override;

private:
    std::string specialization_; /**< Specjalizacja medyczna lekarza. */
};

#endif
