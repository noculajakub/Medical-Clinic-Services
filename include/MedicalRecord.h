#ifndef MEDICAL_RECORD_H
#define MEDICAL_RECORD_H

#include <string>

class MedicalRecord {
public:
    MedicalRecord(int id,
        int patientId,
        int doctorId,
        const std::string& date,
        const std::string& diagnosis,
        const std::string& recommendations,
        const std::string& prescribedMedicines);

    int getId() const;
    int getPatientId() const;
    int getDoctorId() const;
    std::string getDate() const;
    std::string getDiagnosis() const;
    std::string getRecommendations() const;
    std::string getPrescribedMedicines() const;

private:
    int id_;
    int patientId_;
    int doctorId_;
    std::string date_;
    std::string diagnosis_;
    std::string recommendations_;
    std::string prescribedMedicines_;
};

#endif