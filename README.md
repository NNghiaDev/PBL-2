# Hospital Management System (HMS)

## Tech Stack
* **Language:** C++17
* **GUI:** Dear ImGui (Backend: GLFW + OpenGL3)
* **Database:** MySQL
* **DB Driver:** MySQL Connector/C++ (JDBC API)
* **Build System:** CMake (>= 3.15)
* **Architecture:** 3-Tier (Presentation - Business Logic - Data Access)

## System Architecture

```text 
PBL-2/
├── assets/                     # Chứa font chữ, hình ảnh, icon
├── sql/                        # Script tạo bảng DB (schema.sql, seed.sql)
├── vendor/                     # Thư viện bên ngoài (ImGui, MySQL Connector)
├── include/                    # Định nghĩa cấu trúc file (.h / .hpp)
│   ├── gui/                    #   -> File header của giao diện ImGui
│   ├── core/                   #
│   │   ├── models/             #   -> Các class định nghĩa thực thể (Patient.h)
│   │   └── services/           #   -> Các class xử lý nghiệp vụ (PatientManager.h)
│   └── dao/                    #   -> Các file Data Access Object (PatientDAO.h)
└── src/                        # Triển khai code thực tế (.cpp)
    ├── main.cpp                # File chạy chính của chương trình
    ├── gui/                    #   -> Code vẽ UI (PatientUI.cpp)
    ├── core/                   #   -> Code xử lý logic
    └── dao/                    #   -> Code chạy query SQL
