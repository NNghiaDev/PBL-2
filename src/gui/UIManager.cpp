#include "gui/UIManager.h"
#include "imgui.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>

UIManager::UIManager(std::shared_ptr<PatientService> pService,
                     std::shared_ptr<DoctorService> dService,
                     std::shared_ptr<QueueService> qService,
                     std::shared_ptr<PharmacyService> phService,
                     std::shared_ptr<MedicalRecordService> rService,
                     std::shared_ptr<BillingService> bService)
    : patientService(pService),
      doctorService(dService),
      queueService(qService),
      pharmacyService(phService),
      recordService(rService),
      billingService(bService),
      currentTab(ViewTab::PATIENT_MANAGEMENT) {

    // Initialize string buffers
    std::memset(patientSearchBuf, 0, sizeof(patientSearchBuf));
    std::memset(newPatId, 0, sizeof(newPatId));
    if (patientService) {
        std::string nextPatId = patientService->generateNextPatientId();
        std::strncpy(newPatId, nextPatId.c_str(), sizeof(newPatId));
    }
    std::memset(newPatName, 0, sizeof(newPatName));
    std::memset(newPatDob, 0, sizeof(newPatDob));
    newPatGenderIdx = 0;
    std::memset(newPatPhone, 0, sizeof(newPatPhone));
    std::memset(newPatAddress, 0, sizeof(newPatAddress));
    std::memset(newPatInsurance, 0, sizeof(newPatInsurance));
    newPatBloodIdx = 0;
    std::memset(newPatContact, 0, sizeof(newPatContact));
    newPatPriorityIdx = 2; // Default: Thong thuong (3)

    std::memset(doctorSearchBuf, 0, sizeof(doctorSearchBuf));
    std::memset(newDocId, 0, sizeof(newDocId));
    std::memset(newDocName, 0, sizeof(newDocName));
    std::memset(newDocDob, 0, sizeof(newDocDob));
    newDocGenderIdx = 0;
    std::memset(newDocPhone, 0, sizeof(newDocPhone));
    std::memset(newDocAddress, 0, sizeof(newDocAddress));
    std::memset(newDocSpecialty, 0, sizeof(newDocSpecialty));
    std::memset(newDocLicense, 0, sizeof(newDocLicense));
    std::memset(newDocDept, 0, sizeof(newDocDept));
    newDocExp = 5;

    std::memset(queuePatientIdBuf, 0, sizeof(queuePatientIdBuf));

    std::memset(medicineSearchBuf, 0, sizeof(medicineSearchBuf));
    std::memset(newMedId, 0, sizeof(newMedId));
    std::memset(newMedName, 0, sizeof(newMedName));
    std::memset(newMedUnit, 0, sizeof(newMedUnit));
    newMedPrice = 10000.0;
    newMedStock = 100;
    std::memset(newMedUsage, 0, sizeof(newMedUsage));

    std::memset(examRecordId, 0, sizeof(examRecordId));
    if (recordService) {
        std::string nextRecId = recordService->generateNextRecordId();
        std::strncpy(examRecordId, nextRecId.c_str(), sizeof(examRecordId));
    }
    std::memset(examPatientId, 0, sizeof(examPatientId));
    std::memset(examDoctorId, 0, sizeof(examDoctorId));
    std::memset(examSymptoms, 0, sizeof(examSymptoms));
    std::memset(examDiagnosis, 0, sizeof(examDiagnosis));
    examConsultationFee = 150000.0;
    examServiceFee = 50000.0;
    std::memset(selectedMedId, 0, sizeof(selectedMedId));
    selectedMedQty = 1;
    std::memset(selectedMedDosage, 0, sizeof(selectedMedDosage));

    std::memset(billingSearchBuf, 0, sizeof(billingSearchBuf));
}

void UIManager::setTab(ViewTab tab) {
    currentTab = tab;
}

ViewTab UIManager::getTab() const {
    return currentTab;
}

void UIManager::applyDarkHospitalTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;
    style.ChildRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text]                  = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.15f, 0.17f, 0.22f, 1.00f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.14f, 0.16f, 0.20f, 0.98f);
    colors[ImGuiCol_Border]                = ImVec4(0.24f, 0.28f, 0.36f, 0.60f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.24f, 0.30f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.26f, 0.32f, 0.40f, 1.00f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.30f, 0.36f, 0.46f, 1.00f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.14f, 0.28f, 0.38f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.16f, 0.42f, 0.58f, 1.00f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.20f, 0.52f, 0.72f, 1.00f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.12f, 0.35f, 0.50f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.18f, 0.38f, 0.52f, 0.80f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.22f, 0.48f, 0.66f, 0.80f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.16f, 0.34f, 0.48f, 1.00f);
    colors[ImGuiCol_Tab]                   = ImVec4(0.16f, 0.22f, 0.30f, 0.86f);
    colors[ImGuiCol_TabHovered]            = ImVec4(0.24f, 0.46f, 0.64f, 0.80f);
    colors[ImGuiCol_TabSelected]           = ImVec4(0.20f, 0.42f, 0.60f, 1.00f);
    colors[ImGuiCol_TableRowBg]            = ImVec4(0.14f, 0.16f, 0.21f, 1.00f);
    colors[ImGuiCol_TableRowBgAlt]         = ImVec4(0.16f, 0.19f, 0.25f, 1.00f);
}

void UIManager::renderNavigation() {
    if (ImGui::BeginTabBar("HMS_MainTabBar")) {
        if (ImGui::BeginTabItem("  Benh Nhan  ")) {
            setTab(ViewTab::PATIENT_MANAGEMENT);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("  Hang Doi Tiep Don (DSA)  ")) {
            setTab(ViewTab::TRIAGE_QUEUE);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("  Bac Si & Phong Ban  ")) {
            setTab(ViewTab::DOCTOR_MANAGEMENT);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("  Kham Benh & Don Thuoc  ")) {
            setTab(ViewTab::EXAMINATION_RECORD);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("  Kho Duoc Pham  ")) {
            setTab(ViewTab::PHARMACY_STOCK);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("  Vien Phi & Hoa Don  ")) {
            setTab(ViewTab::BILLING_INVOICE);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}

// -----------------------------------------------------------------------------
// TAB 1: PATIENTS
// -----------------------------------------------------------------------------
void UIManager::renderPatientTab() {
    ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "QUAN LY DANH SACH BENH NHAN (3-TIER + CSV EXCEL)");
    ImGui::Separator();

    // Toolbar: Tim kiem & Sap xep
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputTextWithHint("##SearchPat", "Tim kiem theo Ten hoac Ma...", patientSearchBuf, sizeof(patientSearchBuf));
    ImGui::SameLine();
    static bool sortByNameAsc = false;
    if (ImGui::Button("Sap xep theo Ten (QuickSort)")) {
        sortByNameAsc = !sortByNameAsc;
    }
    ImGui::SameLine();
    if (ImGui::Button("Lam moi danh sach")) {
        patientStatusMsg = "Da lam moi danh sach.";
    }

    if (!patientStatusMsg.empty()) {
        ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", patientStatusMsg.c_str());
    }

    std::vector<Patient> list;
    if (std::strlen(patientSearchBuf) > 0) {
        list = patientService->searchPatients(patientSearchBuf);
    } else if (sortByNameAsc) {
        list = patientService->getPatientsSortedByName();
    } else {
        list = patientService->getAllPatients();
    }

    // Bang hien thi danh sach
    if (ImGui::BeginTable("PatientsTable", 9, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY, ImVec2(0, 240))) {
        ImGui::TableSetupColumn("Ma BN", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("Ho va Ten", ImGuiTableColumnFlags_WidthFixed, 150.0f);
        ImGui::TableSetupColumn("Ngay Sinh", ImGuiTableColumnFlags_WidthFixed, 85.0f);
        ImGui::TableSetupColumn("Gioi Tinh", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("SDT", ImGuiTableColumnFlags_WidthFixed, 95.0f);
        ImGui::TableSetupColumn("Ma BHYT", ImGuiTableColumnFlags_WidthFixed, 95.0f);
        ImGui::TableSetupColumn("Nhom Mau", ImGuiTableColumnFlags_WidthFixed, 65.0f);
        ImGui::TableSetupColumn("Muc Uu Tien", ImGuiTableColumnFlags_WidthFixed, 120.0f);
        ImGui::TableSetupColumn("Thao Tac", ImGuiTableColumnFlags_WidthFixed, 65.0f);
        ImGui::TableHeadersRow();

        for (const auto& p : list) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", p.getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", p.getFullName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%s", p.getDateOfBirth().c_str());
            ImGui::TableSetColumnIndex(3); ImGui::Text("%s", p.getGender().c_str());
            ImGui::TableSetColumnIndex(4); ImGui::Text("%s", p.getPhone().c_str());
            ImGui::TableSetColumnIndex(5); ImGui::Text("%s", p.getHealthInsuranceId().c_str());
            ImGui::TableSetColumnIndex(6); ImGui::Text("%s", p.getBloodType().c_str());
            ImGui::TableSetColumnIndex(7);
            if (p.getPriorityLevel() == 1) {
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "1 - Cap cuu");
            } else if (p.getPriorityLevel() == 2) {
                ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.2f, 1.0f), "2 - Uu tien");
            } else {
                ImGui::Text("3 - Thuong");
            }

            ImGui::TableSetColumnIndex(8);
            std::string btnId = "Xoa##" + p.getId();
            if (ImGui::Button(btnId.c_str())) {
                patientService->removePatient(p.getId());
                patientStatusMsg = "Da xoa benh nhan " + p.getId();
            }
        }
        ImGui::EndTable();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextColored(ImVec4(0.3f, 0.9f, 0.6f, 1.0f), "DANG KY BENH NHAN MOI");

    ImGui::Columns(2, "PatFormCols", false);
    if (std::strlen(newPatId) == 0 && patientService) {
        std::string nextPatId = patientService->generateNextPatientId();
        std::strncpy(newPatId, nextPatId.c_str(), sizeof(newPatId));
    }
    ImGui::InputText("Ma BN (Tu dong)", newPatId, sizeof(newPatId));
    ImGui::SameLine();
    if (ImGui::SmallButton("Tao ma##Pat")) {
        std::string nextPatId = patientService->generateNextPatientId();
        std::strncpy(newPatId, nextPatId.c_str(), sizeof(newPatId));
    }
    ImGui::InputText("Ho va Ten", newPatName, sizeof(newPatName));
    ImGui::InputText("Ngay Sinh (DD/MM/YYYY)", newPatDob, sizeof(newPatDob));
    const char* genders[] = { "Nam", "Nu" };
    ImGui::Combo("Gioi Tinh", &newPatGenderIdx, genders, IM_ARRAYSIZE(genders));
    ImGui::InputText("So Dien Thoai", newPatPhone, sizeof(newPatPhone));

    ImGui::NextColumn();
    ImGui::InputText("Dia Chi Thuong Tru", newPatAddress, sizeof(newPatAddress));
    ImGui::InputText("So The BHYT", newPatInsurance, sizeof(newPatInsurance));
    const char* bloodTypes[] = { "O", "A", "B", "AB" };
    ImGui::Combo("Nhom Mau", &newPatBloodIdx, bloodTypes, IM_ARRAYSIZE(bloodTypes));
    ImGui::InputText("SDT Nguoi Than", newPatContact, sizeof(newPatContact));
    const char* priorities[] = { "1 - Cap cuu (Khan cap)", "2 - Uu tien (Tre em/Nguoi gia)", "3 - Thong thuong" };
    ImGui::Combo("Muc Uu Tien", &newPatPriorityIdx, priorities, IM_ARRAYSIZE(priorities));

    ImGui::Columns(1);
    ImGui::Spacing();

    if (ImGui::Button("  Luu Benh Nhan Vao Database (CSV)  ", ImVec2(280, 32))) {
        int prio = (newPatPriorityIdx == 0 ? 1 : (newPatPriorityIdx == 1 ? 2 : 3));
        Patient p(newPatId, newPatName, newPatDob, genders[newPatGenderIdx],
                  newPatPhone, newPatAddress, newPatInsurance, bloodTypes[newPatBloodIdx],
                  newPatContact, prio);

        if (patientService->registerPatient(p)) {
            patientStatusMsg = "Them thanh cong benh nhan [" + std::string(newPatId) + "]: " + std::string(newPatName);
            // Tu dong sinh ma tiep theo cho lan nhap sau
            std::string nextPatId = patientService->generateNextPatientId();
            std::strncpy(newPatId, nextPatId.c_str(), sizeof(newPatId));
            std::memset(newPatName, 0, sizeof(newPatName));
            std::memset(newPatPhone, 0, sizeof(newPatPhone));
            std::memset(newPatAddress, 0, sizeof(newPatAddress));
            std::memset(newPatInsurance, 0, sizeof(newPatInsurance));
        } else {
            patientStatusMsg = "Loi: Ma benh nhan da ton tai hoac de trong thong tin!";
        }
    }
}

// -----------------------------------------------------------------------------
// TAB 2: QUEUE & TRIAGE (DSA DEMO)
// -----------------------------------------------------------------------------
void UIManager::renderQueueTab() {
    ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "HANG DOI TIEP DON BENH NHAN (TRIAGE QUEUE - DSA)");
    ImGui::Text("Su dung Max-Heap PriorityQueue cho Cap Cuu va FIFO Queue cho Benh Nhan Thuong.");
    ImGui::Separator();

    // Stats
    ImGui::Text("Tong so benh nhan dang cho: %zu", queueService->getTotalWaitingCount());
    ImGui::SameLine(250.0f);
    ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Dang cho Cap cuu: %zu", queueService->getEmergencyQueueCount());
    ImGui::SameLine(480.0f);
    ImGui::TextColored(ImVec4(0.3f, 0.8f, 1.0f, 1.0f), "Dang cho Kham thuong: %zu", queueService->getStandardQueueCount());

    ImGui::Spacing();
    ImGui::SetNextItemWidth(180.0f);
    ImGui::InputTextWithHint("##QueuePatId", "Nhap Ma BN vao vien...", queuePatientIdBuf, sizeof(queuePatientIdBuf));
    ImGui::SameLine();
    if (ImGui::Button("Dua Vao Hang Doi Kham")) {
        auto pOpt = patientService->findPatientById(queuePatientIdBuf);
        if (pOpt.has_value()) {
            queueService->enqueuePatient(pOpt.value());
            queueStatusMsg = "Da dua benh nhan [" + pOpt->getFullName() + "] vao hang doi (Muc: " + pOpt->getPriorityDescription() + ")";
            std::memset(queuePatientIdBuf, 0, sizeof(queuePatientIdBuf));
        } else {
            queueStatusMsg = "Khong tim thay benh nhan voi ma nay!";
        }
    }

    ImGui::SameLine();
    if (ImGui::Button("  GOI BENH NHAN TIEP THEO VAO PHONG KHAM  ", ImVec2(320, 0))) {
        auto nextP = queueService->callNextPatient();
        if (nextP.has_value()) {
            lastCalledPatientInfo = "Moi benh nhan: [" + nextP->getId() + "] " + nextP->getFullName() +
                                    " | Uu tien: " + nextP->getPriorityDescription();
            queueStatusMsg = "Da goi benh nhan vao kham!";
            // Auto fill examination tab
            std::strncpy(examPatientId, nextP->getId().c_str(), sizeof(examPatientId));
        } else {
            lastCalledPatientInfo = "Hang doi hien dang rong!";
        }
    }

    if (!lastCalledPatientInfo.empty()) {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.9f, 0.2f, 1.0f), ">>> LOA THONG BAO: %s", lastCalledPatientInfo.c_str());
    }
    if (!queueStatusMsg.empty()) {
        ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", queueStatusMsg.c_str());
    }

    ImGui::Spacing();
    ImGui::Columns(2, "QueueCols", true);
    ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Hang Doi Cap Cuu (Priority Queue - Xu Ly Truoc):");
    auto emergList = queueService->getEmergencyList();
    if (ImGui::BeginTable("EmergQueueTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Ma BN");
        ImGui::TableSetupColumn("Ho va Ten");
        ImGui::TableSetupColumn("Uu Tien");
        ImGui::TableHeadersRow();
        for (const auto& p : emergList) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", p.getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", p.getFullName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Cap cuu");
        }
        ImGui::EndTable();
    }

    ImGui::NextColumn();
    ImGui::TextColored(ImVec4(0.3f, 0.8f, 1.0f, 1.0f), "Hang Doi Thuong (FIFO Queue - Den Truoc Kham Truoc):");
    auto stdList = queueService->getStandardList();
    if (ImGui::BeginTable("StdQueueTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Ma BN");
        ImGui::TableSetupColumn("Ho va Ten");
        ImGui::TableSetupColumn("Uu Tien");
        ImGui::TableHeadersRow();
        for (const auto& p : stdList) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", p.getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", p.getFullName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%s", p.getPriorityDescription().c_str());
        }
        ImGui::EndTable();
    }
    ImGui::Columns(1);
}

// -----------------------------------------------------------------------------
// TAB 3: DOCTORS
// -----------------------------------------------------------------------------
void UIManager::renderDoctorTab() {
    ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "QUAN LY DOI NGU BAC SI & CHUYEN KHOA");
    ImGui::Separator();

    auto list = doctorService->getAllDoctors();
    if (ImGui::BeginTable("DoctorsTable", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg, ImVec2(0, 220))) {
        ImGui::TableSetupColumn("Ma BS", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("Ho va Ten", ImGuiTableColumnFlags_WidthFixed, 180.0f);
        ImGui::TableSetupColumn("Chuyen Khoa", ImGuiTableColumnFlags_WidthFixed, 140.0f);
        ImGui::TableSetupColumn("Khoa Phong", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("So CCHN", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("Kinh Nghiem", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("So Dien Thoai", ImGuiTableColumnFlags_WidthFixed, 95.0f);
        ImGui::TableSetupColumn("Thao Tac", ImGuiTableColumnFlags_WidthFixed, 65.0f);
        ImGui::TableHeadersRow();

        for (const auto& d : list) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", d.getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", d.getFullName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%s", d.getSpecialty().c_str());
            ImGui::TableSetColumnIndex(3); ImGui::Text("%s", d.getDepartmentId().c_str());
            ImGui::TableSetColumnIndex(4); ImGui::Text("%s", d.getLicenseNumber().c_str());
            ImGui::TableSetColumnIndex(5); ImGui::Text("%d nam", d.getYearsOfExperience());
            ImGui::TableSetColumnIndex(6); ImGui::Text("%s", d.getPhone().c_str());
            ImGui::TableSetColumnIndex(7);
            std::string btnId = "Xoa##" + d.getId();
            if (ImGui::Button(btnId.c_str())) {
                doctorService->removeDoctor(d.getId());
            }
        }
        ImGui::EndTable();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextColored(ImVec4(0.3f, 0.9f, 0.6f, 1.0f), "THEM BAC SI MOI");
    ImGui::Columns(2, "DocForm", false);
    ImGui::InputText("Ma Bac Si", newDocId, sizeof(newDocId));
    ImGui::InputText("Ho va Ten", newDocName, sizeof(newDocName));
    ImGui::InputText("Chuyen Khoa", newDocSpecialty, sizeof(newDocSpecialty));
    ImGui::InputText("Khoa Phong", newDocDept, sizeof(newDocDept));

    ImGui::NextColumn();
    ImGui::InputText("So Chung Chi Hanh Nghe", newDocLicense, sizeof(newDocLicense));
    ImGui::InputInt("So Nam Kinh Nghiem", &newDocExp);
    ImGui::InputText("So Dien Thoai Lien He", newDocPhone, sizeof(newDocPhone));
    ImGui::InputText("Dia Chi", newDocAddress, sizeof(newDocAddress));
    ImGui::Columns(1);

    if (ImGui::Button("  Luu Bac Si Vao Danh Sach  ", ImVec2(240, 30))) {
        Doctor d(newDocId, newDocName, "01/01/1980", "Nam", newDocPhone, newDocAddress,
                 newDocSpecialty, newDocLicense, newDocDept, newDocExp);
        doctorService->registerDoctor(d);
        doctorStatusMsg = "Them bac si thanh cong!";
    }
}

// -----------------------------------------------------------------------------
// TAB 4: EXAMINATION & MEDICAL RECORDS
// -----------------------------------------------------------------------------
void UIManager::renderExaminationTab() {
    ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "KHAM BENH, CHUAN DOAN & KE DON THUOC (BUSINESS FLOW)");
    ImGui::Separator();

    ImGui::Columns(2, "ExamCols", false);
    if (std::strlen(examRecordId) == 0 && recordService) {
        std::string nextRecId = recordService->generateNextRecordId();
        std::strncpy(examRecordId, nextRecId.c_str(), sizeof(examRecordId));
    }
    ImGui::InputText("Ma Benh An (Tu dong)", examRecordId, sizeof(examRecordId));
    ImGui::SameLine();
    if (ImGui::SmallButton("Tao ma##Rec")) {
        std::string nextRecId = recordService->generateNextRecordId();
        std::strncpy(examRecordId, nextRecId.c_str(), sizeof(examRecordId));
    }
    ImGui::InputText("Ma Benh Nhan Kham", examPatientId, sizeof(examPatientId));
    ImGui::InputText("Ma Bac Si Kham", examDoctorId, sizeof(examDoctorId));
    ImGui::InputText("Trieu Chung", examSymptoms, sizeof(examSymptoms));
    ImGui::InputText("Chuan Doan Benh", examDiagnosis, sizeof(examDiagnosis));

    ImGui::NextColumn();
    ImGui::InputDouble("Tien Kham Benh (VND)", &examConsultationFee, 10000.0, 50000.0, "%.0f");
    ImGui::InputDouble("Phi Xet Nghiem/Dich Vu (VND)", &examServiceFee, 10000.0, 50000.0, "%.0f");

    ImGui::Spacing();
    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.3f, 1.0f), "Ke don thuoc tu kho:");
    ImGui::SetNextItemWidth(120.0f);
    ImGui::InputText("Ma Thuoc", selectedMedId, sizeof(selectedMedId));
    ImGui::SameLine();
    ImGui::SetNextItemWidth(70.0f);
    ImGui::InputInt("SL", &selectedMedQty);
    ImGui::InputText("Lieu Dung", selectedMedDosage, sizeof(selectedMedDosage));

    if (ImGui::Button("Them Vao Don Thuoc")) {
        auto medOpt = pharmacyService->findMedicineById(selectedMedId);
        if (medOpt.has_value()) {
            if (medOpt->getStockQuantity() >= selectedMedQty) {
                tempPrescription.emplace_back(medOpt->getId(), medOpt->getName(),
                                              selectedMedQty, medOpt->getPrice(), selectedMedDosage);
                examStatusMsg = "Da them thuoc vao don: " + medOpt->getName();
            } else {
                examStatusMsg = "Loi: Kho khong du so luong thuoc nay!";
            }
        } else {
            examStatusMsg = "Loi: Ma thuoc khong hop le!";
        }
    }
    ImGui::Columns(1);

    // Bang don thuoc hien tai
    ImGui::Spacing();
    ImGui::Text("Danh sach thuoc da ke:");
    if (ImGui::BeginTable("TempPrescTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg, ImVec2(0, 120))) {
        ImGui::TableSetupColumn("Ma Thuoc");
        ImGui::TableSetupColumn("Ten Thuoc");
        ImGui::TableSetupColumn("So Luong");
        ImGui::TableSetupColumn("Don Gia");
        ImGui::TableSetupColumn("Lieu Dung");
        ImGui::TableHeadersRow();

        for (const auto& item : tempPrescription) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", item.getMedicineId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", item.getMedicineName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%d", item.getQuantity());
            ImGui::TableSetColumnIndex(3); ImGui::Text("%.0f VND", item.getUnitPrice());
            ImGui::TableSetColumnIndex(4); ImGui::Text("%s", item.getDosage().c_str());
        }
        ImGui::EndTable();
    }

    if (!examStatusMsg.empty()) {
        ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", examStatusMsg.c_str());
    }

    ImGui::Spacing();
    if (ImGui::Button("  XAC NHAN HOAN TAT KHAM & XUAT DON THUOC (TRU KHO)  ", ImVec2(450, 36))) {
        if (std::strlen(examRecordId) > 0 && std::strlen(examPatientId) > 0) {
            MedicalRecord rec(examRecordId, examPatientId, examDoctorId,
                              "30/10/2026", examSymptoms, examDiagnosis,
                              examConsultationFee, examServiceFee);
            for (const auto& p : tempPrescription) {
                rec.addPrescription(p);
            }

            if (recordService->createMedicalRecord(rec)) {
                // Tu dong sinh hoa don vien phi
                auto patOpt = patientService->findPatientById(examPatientId);
                if (patOpt.has_value()) {
                    std::string invId = "HD-" + std::string(examRecordId);
                    Invoice inv = billingService->generateInvoice(invId, rec, patOpt.value(), "30/10/2026");
                    billingService->saveInvoice(inv);
                }

                examStatusMsg = "Tao benh an [" + std::string(examRecordId) + "] va tu dong sinh hoa don vien phi thanh cong!";
                tempPrescription.clear();
                std::memset(examSymptoms, 0, sizeof(examSymptoms));
                std::memset(examDiagnosis, 0, sizeof(examDiagnosis));

                // Tu dong sinh ma benh an ke tiep
                std::string nextRecId = recordService->generateNextRecordId();
                std::strncpy(examRecordId, nextRecId.c_str(), sizeof(examRecordId));
            } else {
                examStatusMsg = "Loi: Khong the tao benh an!";
            }
        }
    }
}

// -----------------------------------------------------------------------------
// TAB 5: PHARMACY
// -----------------------------------------------------------------------------
void UIManager::renderPharmacyTab() {
    ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "QUAN LY KHO DUOC PHAM & DANH MUC THUOC");
    ImGui::Separator();

    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputTextWithHint("##SearchMed", "Tim thuoc theo ten...", medicineSearchBuf, sizeof(medicineSearchBuf));

    auto list = (std::strlen(medicineSearchBuf) > 0)
                ? pharmacyService->searchMedicines(medicineSearchBuf)
                : pharmacyService->getAllMedicines();

    if (ImGui::BeginTable("MedsTable", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY, ImVec2(0, 240))) {
        ImGui::TableSetupColumn("Ma Thuoc", ImGuiTableColumnFlags_WidthFixed, 80.0f);
        ImGui::TableSetupColumn("Ten Thuoc", ImGuiTableColumnFlags_WidthFixed, 180.0f);
        ImGui::TableSetupColumn("Don Vi", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("Don Gia", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("Ton Kho", ImGuiTableColumnFlags_WidthFixed, 80.0f);
        ImGui::TableSetupColumn("Huong Dan Su Dung", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableHeadersRow();

        for (const auto& m : list) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", m.getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", m.getName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%s", m.getUnit().c_str());
            ImGui::TableSetColumnIndex(3); ImGui::Text("%.0f VND", m.getPrice());
            ImGui::TableSetColumnIndex(4);
            if (m.getStockQuantity() < 50) {
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%d (Sap het!)", m.getStockQuantity());
            } else {
                ImGui::Text("%d", m.getStockQuantity());
            }
            ImGui::TableSetColumnIndex(5); ImGui::Text("%s", m.getUsageNote().c_str());
        }
        ImGui::EndTable();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextColored(ImVec4(0.3f, 0.9f, 0.6f, 1.0f), "NHAP THUOC MOI VAO KHO");
    ImGui::Columns(2, "MedForm", false);
    ImGui::InputText("Ma Thuoc", newMedId, sizeof(newMedId));
    ImGui::InputText("Ten Thuoc", newMedName, sizeof(newMedName));
    ImGui::InputText("Don Vi Tinh", newMedUnit, sizeof(newMedUnit));

    ImGui::NextColumn();
    ImGui::InputDouble("Don Gia (VND)", &newMedPrice, 1000.0, 5000.0, "%.0f");
    ImGui::InputInt("So Luong Nhap", &newMedStock);
    ImGui::InputText("Huong Dan", newMedUsage, sizeof(newMedUsage));
    ImGui::Columns(1);

    if (ImGui::Button("  Luu Thuoc Vao Kho  ", ImVec2(200, 30))) {
        Medicine m(newMedId, newMedName, newMedUnit, newMedPrice, newMedStock, newMedUsage);
        pharmacyService->addMedicine(m);
        pharmacyStatusMsg = "Da them thuoc vao kho thanh cong!";
    }
}

// -----------------------------------------------------------------------------
// TAB 6: BILLING & INVOICES
// -----------------------------------------------------------------------------
void UIManager::renderBillingTab() {
    ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "QUAN LY VIEN PHI & HOA DON THANH TOAN");
    ImGui::Separator();

    double revenue = billingService->calculateTotalRevenue();
    double pending = billingService->calculatePendingRevenue();

    ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.4f, 1.0f), "Tong doanh thu da thu: %.0f VND", revenue);
    ImGui::SameLine(350.0f);
    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.2f, 1.0f), "Chua thanh toan: %.0f VND", pending);

    ImGui::Spacing();
    auto invoices = billingService->getAllInvoices();
    if (ImGui::BeginTable("InvoicesTable", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY, ImVec2(0, 260))) {
        ImGui::TableSetupColumn("Ma HD", ImGuiTableColumnFlags_WidthFixed, 80.0f);
        ImGui::TableSetupColumn("Ma Benh An", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("Ma BN", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("Tien Kham", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("Tien Thuoc", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("BHYT", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("Thuc Thu", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("Trang Thai / Thao Tac", ImGuiTableColumnFlags_WidthFixed, 140.0f);
        ImGui::TableHeadersRow();

        for (const auto& inv : invoices) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", inv.getInvoiceId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", inv.getRecordId().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%s", inv.getPatientId().c_str());
            ImGui::TableSetColumnIndex(3); ImGui::Text("%.0f", inv.getConsultationFee() + inv.getServiceFee());
            ImGui::TableSetColumnIndex(4); ImGui::Text("%.0f", inv.getMedicineFee());
            ImGui::TableSetColumnIndex(5); ImGui::Text("%.0f%%", inv.getDiscountRatio() * 100);
            ImGui::TableSetColumnIndex(6); ImGui::TextColored(ImVec4(1.0f, 0.9f, 0.3f, 1.0f), "%.0f VND", inv.getTotalAmount());
            ImGui::TableSetColumnIndex(7);
            if (inv.getIsPaid()) {
                ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.3f, 1.0f), "Da thanh toan");
            } else {
                std::string payBtn = "Xac Nhan Thu##" + inv.getInvoiceId();
                if (ImGui::Button(payBtn.c_str())) {
                    billingService->processPayment(inv.getInvoiceId());
                }
            }
        }
        ImGui::EndTable();
    }
}

void UIManager::renderMainUI() {
    renderNavigation();
    ImGui::Spacing();
    switch (currentTab) {
        case ViewTab::PATIENT_MANAGEMENT:  renderPatientTab(); break;
        case ViewTab::TRIAGE_QUEUE:        renderQueueTab(); break;
        case ViewTab::DOCTOR_MANAGEMENT:   renderDoctorTab(); break;
        case ViewTab::EXAMINATION_RECORD:  renderExaminationTab(); break;
        case ViewTab::PHARMACY_STOCK:      renderPharmacyTab(); break;
        case ViewTab::BILLING_INVOICE:     renderBillingTab(); break;
    }
}
