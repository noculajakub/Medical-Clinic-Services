#ifndef MEDICAL_RECORD_H
#define MEDICAL_RECORD_H

#include <string>

/**
 * @brief Klasa reprezentująca pojedynczy wpis w historii medycznej pacjenta (kartę wizyty).
 * * Przechowuje informacje o diagnozie, zaleceniach oraz przepisanych lekach dla konkretnej wizyty.
 */
class MedicalRecord {
public:
    /**
     * @brief Konstruktor obiektu klasy MedicalRecord.
     * * @param id Unikalny identyfikator wpisu medycznego.
     * @param patientId Identyfikator pacjenta, którego dotyczy wpis.
     * @param doctorId Identyfikator lekarza wystawiającego wpis.
     * @param date Data odbycia wizyty / utworzenia wpisu.
     * @param diagnosis Postawiona diagnoza lekarska.
     * @param recommendations Zalecenia dla pacjenta.
     * @param prescribedMedicines Przepisane leki i recepty.
     */
    MedicalRecord(int id,
        int patientId,
        int doctorId,
        const std::string& date,
        const std::string& diagnosis,
        const std::string& recommendations,
        const std::string& prescribedMedicines);

    /**
     * @brief Pobiera identyfikator wpisu medycznego.
     * @return int ID wpisu.
     */
    int getId() const;

    /**
     * @brief Pobiera identyfikator pacjenta przypisanego do tego wpisu.
     * @return int ID pacjenta.
     */
    int getPatientId() const;

    /**
     * @brief Pobiera identyfikator lekarza, który utworzył wpis.
     * @return int ID lekarza.
     */
    int getDoctorId() const;

    /**
     * @brief Pobiera datę utworzenia wpisu medycznego.
     * @return std::string Data w formacie tekstowym.
     */
    std::string getDate() const;

    /**
     * @brief Pobiera treść diagnozy lekarskiej.
     * @return std::string Tekst diagnozy.
     */
    std::string getDiagnosis() const;

    /**
     * @brief Pobiera zalecenia powizytowe dla pacjenta.
     * @return std::string Tekst zaleceń.
     */
    std::string getRecommendations() const;

    /**
     * @brief Pobiera listę przepisanych leków wraz z dawkowaniem.
     * @return std::string Tekst zawierający spis leków.
     */
    std::string getPrescribedMedicines() const;

private:
    int id_;                             /**< Unikalny identyfikator wpisu. */
    int patientId_;                      /**< Identyfikator powiązanego pacjenta. */
    int doctorId_;                       /**< Identyfikator powiązanego lekarza. */
    std::string date_;                   /**< Data wizyty. */
    std::string diagnosis_;              /**< Opis diagnozy. */
    std::string recommendations_;        /**< Treść zaleceń medycznych. */
    std::string prescribedMedicines_;    /**< Spis przepisanych lekarstw. */
};

#endif