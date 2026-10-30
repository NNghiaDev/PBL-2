# Hospital Management System (HMS) - PBL-2

Hệ thống Quản lý Bệnh viện theo kiến trúc 3 tầng (3-Tier Architecture) hoàn chỉnh, ứng dụng Lập trình hướng đối tượng (OOP), Cấu trúc dữ liệu & Giải thuật (DSA), giao diện đồ họa **Dear ImGui** (GLFW + OpenGL3) và lưu trữ dữ liệu dạng **file Excel/CSV** (sẵn sàng chuyển đổi sang MySQL).

---

## 🛠 Tech Stack
* **Language:** C++17
* **GUI:** [Dear ImGui](https://github.com/ocornut/imgui) (Backend: GLFW + OpenGL3)
* **Architecture:** 3-Tier (Presentation - Business Logic - Data Access)
* **Storage:** CSV Database (Tương thích 100% Microsoft Excel, mở và chỉnh sửa trực tiếp)
* **DSA:** Priority Queue (Max-Heap), Queue (FIFO), QuickSort, Binary Search
* **Build System:** CMake (>= 3.15) & Ninja / MinGW

---

## 🏛 Cấu trúc Dự án 3 Tầng

```text
PBL-2/
├── data/                       # Chứa cơ sở dữ liệu file CSV (Excel mở trực tiếp)
│   ├── patients.csv            # Danh sách bệnh nhân
│   ├── doctors.csv             # Danh sách bác sĩ & chuyên khoa
│   ├── medicines.csv           # Kho thuốc & đơn giá
│   ├── medical_records.csv     # Hồ sơ bệnh án & đơn thuốc
│   └── invoices.csv            # Hóa đơn thanh toán & BHYT
├── vendor/
│   └── imgui/                  # Thư viện Dear ImGui + GLFW/OpenGL3 backends
├── include/
│   ├── core/
│   │   ├── models/             # OOP Models: Person, Patient, Doctor, Medicine, MedicalRecord, Invoice
│   │   ├── services/           # Business Logic: PatientService, QueueService, PharmacyService,...
│   │   └── dsa/                # DSA: CustomQueue, CustomPriorityQueue, QuickSort, BinarySearch
│   ├── dao/                    # DAO Interfaces (IPatientDAO,...) và CSV implementations
│   └── gui/                    # Presentation: UIManager.h (Dear ImGui UI components)
├── src/
│   ├── core/                   # Cài đặt code Models và Services
│   ├── dao/                    # Cài đặt code đọc/ghi file CSV
│   ├── gui/                    # Cài đặt giao diện Dear ImGui (UIManager.cpp)
│   └── main.cpp                # Vòng lặp chính khởi tạo cửa sổ GLFW & ImGui
├── CMakeLists.txt              # Cấu hình biên dịch CMake
└── run.bat                     # File chạy nhanh ứng dụng
```

---

## 🚀 Cách Biên dịch và Chạy Ứng dụng

### 1. Biên dịch dự án bằng CMake:
```bash
cmake -B build -G "Ninja"
cmake --build build
```

### 2. Chạy ứng dụng:
* Nhấp đúp chuột vào file `run.bat` hoặc gõ lệnh:
```bash
.\build\HMS.exe
```

---

## 🌟 Các Tính năng Chính trên Giao diện ImGui
1. **Quản lý Bệnh nhân**:
   - Tìm kiếm bệnh nhân theo Tên / Mã ID.
   - Sắp xếp bệnh nhân theo Tên bằng thuật toán **QuickSort**.
   - Tra cứu bệnh nhân bằng **Binary Search** $O(\log N)$.
   - Đăng ký bệnh nhân mới, lưu tự động vào `data/patients.csv`.
2. **Hàng đợi Tiếp đón (Triage Queue - DSA)**:
   - Phân luồng ca cấp cứu qua **Max-Heap PriorityQueue** (xử lý ưu tiên trước).
   - Phân luồng ca khám thông thường qua **FIFO Queue** (đến trước khám trước).
   - Nút gọi bệnh nhân tiếp theo vào phòng khám.
3. **Phòng Khám & Kê đơn thuốc**:
   - Bác sĩ nhập triệu chứng, chẩn đoán, kê đơn thuốc nhiều loại.
   - Khi hoàn tất khám: **Hệ thống tự động trừ kho thuốc** và tự động sinh hóa đơn viện phí.
4. **Kho Dược phẩm**:
   - Quản lý danh mục thuốc, đơn vị, giá bán, số lượng tồn kho.
   - Cảnh báo thuốc sắp hết hàng (< 50 đơn vị).
5. **Thu ngân & Viện phí**:
   - Tổng hợp tiền khám + tiền xét nghiệm + tiền thuốc.
   - Tự động áp dụng mức giảm trừ **BHYT** (chiết khấu 80%).
   - Cập nhật trạng thái thanh toán và thống kê doanh thu bệnh viện.
