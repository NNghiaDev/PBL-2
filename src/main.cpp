#include <iostream>
#include <memory>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// Models
#include "core/models/Patient.h"
#include "core/models/Doctor.h"
#include "core/models/Medicine.h"
#include "core/models/MedicalRecord.h"
#include "core/models/Invoice.h"

// DAOs (CSV / Excel format)
#include "dao/CsvPatientDAO.h"
#include "dao/CsvDoctorDAO.h"
#include "dao/CsvMedicineDAO.h"
#include "dao/CsvMedicalRecordDAO.h"
#include "dao/CsvInvoiceDAO.h"

// Services (Business Logic & DSA)
#include "core/services/PatientService.h"
#include "core/services/DoctorService.h"
#include "core/services/PharmacyService.h"
#include "core/services/MedicalRecordService.h"
#include "core/services/BillingService.h"
#include "core/services/QueueService.h"

// GUI Presentation Layer
#include "gui/UIManager.h"

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "[GLFW Error " << error << "]: " << description << std::endl;
}

int main(int, char**) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return 1;
    }

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 750, "He Thong Quan Ly Benh Vien (Hospital Management System) - PBL-2", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW Window!" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // 1. Khoi tao tang Data Access (DAO - CSV Excel)
    auto patientDao = std::make_shared<CsvPatientDAO>("data/patients.csv");
    auto doctorDao = std::make_shared<CsvDoctorDAO>("data/doctors.csv");
    auto medicineDao = std::make_shared<CsvMedicineDAO>("data/medicines.csv");
    auto recordDao = std::make_shared<CsvMedicalRecordDAO>("data/medical_records.csv");
    auto invoiceDao = std::make_shared<CsvInvoiceDAO>("data/invoices.csv");

    // 2. Khoi tao tang Business Logic (Services)
    auto patientService = std::make_shared<PatientService>(patientDao);
    auto doctorService = std::make_shared<DoctorService>(doctorDao);
    auto pharmacyService = std::make_shared<PharmacyService>(medicineDao);
    auto recordService = std::make_shared<MedicalRecordService>(recordDao, pharmacyService);
    auto billingService = std::make_shared<BillingService>(invoiceDao);
    auto queueService = std::make_shared<QueueService>();

    // 3. Khoi tao tang Presentation GUI (UIManager)
    UIManager uiManager(patientService, doctorService, queueService,
                        pharmacyService, recordService, billingService);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Apply custom Dark Hospital Theme
    uiManager.applyDarkHospitalTheme();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main window loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Fit full window
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(display_w), static_cast<float>(display_h)));

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("HMS_RootWindow", nullptr, window_flags);
        uiManager.renderMainUI();
        ImGui::End();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.12f, 0.14f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
