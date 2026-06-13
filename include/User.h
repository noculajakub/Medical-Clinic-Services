#ifndef USER_H
#define USER_H

#include <string>

/**
 * @brief Definiuje dostępne role użytkowników w systemie.
 * Wykorzystywane do weryfikacji uprawnień i rzutowania typów.
 */

enum class UserRole {
    Doctor,
    Receptionist
};

/**
 * @brief Abstrakcyjna klasa bazowa dla wszystkich użytkowników systemu.
 * Przechowuje wspólne dane logowania, dane osobowe oraz rolę.
 */

class User {
public:
/**
* @brief Inicjalizuje podstawowe dane użytkownika.
*/
    User(int id,
        const std::string& login,
        const std::string& password,
        const std::string& firstName,
        const std::string& lastName,
        UserRole role);

    /**
         * @brief Wirtualny destruktor.
         * Niezbędny dla poprawnego zwalniania pamięci obiektów klas pochodnych (polimorfizm).
         */
    virtual ~User() = default;

    int getId() const;
    std::string getLogin() const;
    std::string getPassword() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    UserRole getRole() const;
    /**
       * @brief Zwraca tekstową nazwę roli użytkownika.
       * Metoda czysto wirtualna - czyni klasę User klasą abstrakcyjną.
       * Każda klasa pochodna (np. Doctor) musi dostarczyć własną implementację tej metody.
       * * @return std::string Nazwa roli (np. "Lekarz", "Recepcja").
       */
    virtual std::string getRoleName() const = 0;

private:
    int id_;
    std::string login_;
    std::string password_;
    std::string firstName_;
    std::string lastName_;
    UserRole role_;
};

#endif
