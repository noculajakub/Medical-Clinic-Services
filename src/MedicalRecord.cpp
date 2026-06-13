#include "MedicalRecord.h"

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

int MedicalRecord::getId() const
{
    return id_;
}

int MedicalRecord::getPatientId() const
{
    return patientId_;
}

int MedicalRecord::getDoctorId() const
{
    return doctorId_;
}

std::string MedicalRecord::getDate() const
{
    return date_;
}

std::string MedicalRecord::getDiagnosis() const
{
    return diagnosis_;
}

std::string MedicalRecord::getRecommendations() const
{
    return recommendations_;
}

std::string MedicalRecord::getPrescribedMedicines() const
{
    return prescribedMedicines_;
}
