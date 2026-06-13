#include "MedicalRecord.h"

/**
 * @brief Definicja konstruktora klasy MedicalRecord.
 * @details Inicjalizuje wszystkie prywatne pola klasy dotyczące karty wizyty pacjenta,
 * takie jak identyfikatory, data, diagnoza, zalecenia oraz lista przepisanych leków.
 * @param id Unikalny identyfikator wpisu medycznego.
 * @param patientId Identyfikator pacjenta, którego dotyczy ten wpis.
 * @param doctorId Identyfikator lekarza wystawiającego dokumentację.
 * @param date Data odbycia wizyty lub sporządzenia wpisu.
 * @param diagnosis Postawiona diagnoza lekarska.
 * @param recommendations Zalecenia powizytowe dla pacjenta.
 * @param prescribedMedicines Przepisane leki wraz z ich dawkowaniem.
 */
MedicalRecord::MedicalRecord(int id,
    int patientId,
    int doctorId,
    const std::string& date,
    const std::string& diagnosis,
    const std::string& recommendations,
    const std::string& prescribedMedicines)
    : id_(id),
    patientId_(patientId),
    doctorId_(doctorId),
    date_(date),
    diagnosis_(diagnosis),
    recommendations_(recommendations),
    prescribedMedicines_(prescribedMedicines)
{}

/**
 * @brief Pobiera identyfikator wpisu medycznego.
 * @return int ID wpisu.
 */
int MedicalRecord::getId() const
{
    return id_;
}

/**
 * @brief Pobiera identyfikator pacjenta przypisanego do tego wpisu.
 * @return int ID pacjenta.
 */
int MedicalRecord::getPatientId() const
{
    return patientId_;
}

/**
 * @brief Pobiera identyfikator lekarza, który utworzył wpis.
 * @return int ID lekarza.
 */
int MedicalRecord::getDoctorId() const
{
    return doctorId_;
}

/**
 * @brief Pobiera datę utworzenia wpisu medycznego.
 * @return std::string Data w formacie tekstowym.
 */
std::string MedicalRecord::getDate() const
{
    return date_;
}

/**
 * @brief Pobiera treść diagnozy lekarskiej.
 * @return std::string Tekst diagnozy.
 */
std::string MedicalRecord::getDiagnosis() const
{
    return diagnosis_;
}

/**
 * @brief Pobiera zalecenia powizytowe dla pacjenta.
 * @return std::string Tekst zaleceń.
 */
std::string MedicalRecord::getRecommendations() const
{
    return recommendations_;
}

/**
 * @brief Pobiera listę przepisanych leków wraz z dawkowaniem.
 * @return std::string Tekst zawierający spis leków.
 */
std::string MedicalRecord::getPrescribedMedicines() const
{
    return prescribedMedicines_;
}
