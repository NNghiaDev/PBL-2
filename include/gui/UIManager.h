#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <memory>
#include <string>
#include <vector>
#include "core/services/PatientService.h"
#include "core/services/DoctorService.h"
#include "core/services/QueueService.h"
#include "core/services/PharmacyService.h"
#include "core/services/MedicalRecordService.h"
#include "core/services/BillingService.h"

enum class ViewTab {
    PATIENT_MANAGEMENT,
    DOCTOR_MANAGEMENT,
    TRIAGE_QUEUE,
    EXAMINATION_RECORD,
    PHARMACY_STOCK,
    BILLING_INVOICE
};

class UIManager {
private:
    std::shared_ptr<PatientService> patientService;
    std::shared_ptr<DoctorService> doctorService;
    std::shared_ptr<QueueService> queueService;
    std::shared_ptr<PharmacyService> pharmacyService;
    std::shared_ptr<MedicalRecordService> recordService;
    std::shared_ptr<BillingService> billingService;

    ViewTab currentTab;

    // --- State Buffers for Patient Tab ---
    char patientSearchBuf[128];
    char newPatId[32];
    char newPatName[128];
    char newPatDob[32];
    int newPatGenderIdx; // 0: Nam, 1: Nu
    char newPatPhone[32];
    char newPatAddress[256];
    char newPatInsurance[64];
    int newPatBloodIdx; // 0: O, 1: A, 2: B, 3: AB
    char newPatContact[64];
    int newPatPriorityIdx; // 0: Cap cuu (1), 1: Uu tien (2), 2: Thong thuong (3)
    std::string patientStatusMsg;

    // --- State Buffers for Doctor Tab ---
    char doctorSearchBuf[128];
    char newDocId[32];
    char newDocName[128];
    char newDocDob[32];
    int newDocGenderIdx;
    char newDocPhone[32];
    char newDocAddress[256];
    char newDocSpecialty[128];
    char newDocLicense[64];
    char newDocDept[64];
    int newDocExp;
    std::string doctorStatusMsg;

    // --- State Buffers for Queue Tab ---
    char queuePatientIdBuf[32];
    std::string queueStatusMsg;
    std::string lastCalledPatientInfo;

    // --- State Buffers for Pharmacy Tab ---
    char medicineSearchBuf[128];
    char newMedId[32];
    char newMedName[128];
    char newMedUnit[32];
    double newMedPrice;
    int newMedStock;
    char newMedUsage[256];
    std::string pharmacyStatusMsg;

    // --- State Buffers for Examination Tab ---
    char examRecordId[32];
    char examPatientId[32];
    char examDoctorId[32];
    char examSymptoms[256];
    char examDiagnosis[256];
    double examConsultationFee;
    double examServiceFee;
    std::vector<PrescriptionDetail> tempPrescription;
    char selectedMedId[32];
    int selectedMedQty;
    char selectedMedDosage[128];
    std::string examStatusMsg;

    // --- State Buffers for Billing Tab ---
    char billingSearchBuf[128];
    std::string billingStatusMsg;

public:
    UIManager(std::shared_ptr<PatientService> pService,
              std::shared_ptr<DoctorService> dService,
              std::shared_ptr<QueueService> qService,
              std::shared_ptr<PharmacyService> phService,
              std::shared_ptr<MedicalRecordService> rService,
              std::shared_ptr<BillingService> bService);

    void setTab(ViewTab tab);
    ViewTab getTab() const;

    // Dear ImGui Rendering
    void renderMainUI();
    void renderNavigation();
    void renderPatientTab();
    void renderDoctorTab();
    void renderQueueTab();
    void renderExaminationTab();
    void renderPharmacyTab();
    void renderBillingTab();

    void applyDarkHospitalTheme();
};

#endif // UI_MANAGER_H
