#include "core/services/DoctorService.h"
#include <sstream>
#include <iomanip>
#include <cctype>

DoctorService::DoctorService(std::shared_ptr<IDoctorDAO> dao) : doctorDao(dao) {}

std::vector<Doctor> DoctorService::getAllDoctors() {
    return doctorDao->getAll();
}

std::optional<Doctor> DoctorService::findDoctorById(const std::string& id) {
    return doctorDao->getById(id);
}

bool DoctorService::registerDoctor(const Doctor& doctor) {
    if (doctor.getId().empty() || doctor.getFullName().empty()) {
        return false;
    }
    return doctorDao->add(doctor);
}

bool DoctorService::updateDoctorInfo(const Doctor& doctor) {
    return doctorDao->update(doctor);
}

bool DoctorService::removeDoctor(const std::string& id) {
    return doctorDao->remove(id);
}

std::vector<Doctor> DoctorService::getDoctorsBySpecialty(const std::string& specialty) {
    return doctorDao->getBySpecialty(specialty);
}

std::string DoctorService::generateNextDoctorId() {
    auto list = doctorDao->getAll();
    int maxId = 0;
    for (const auto& d : list) {
        std::string id = d.getId();
        if (id.rfind("BS", 0) == 0) {
            std::string numStr = "";
            for (size_t i = 2; i < id.length(); ++i) {
                if (std::isdigit(id[i])) {
                    numStr += id[i];
                }
            }
            if (!numStr.empty()) {
                try {
                    int val = std::stoi(numStr);
                    if (val > maxId) maxId = val;
                } catch (...) {}
            }
        }
    }
    std::ostringstream ss;
    ss << "BS" << std::setw(3) << std::setfill('0') << (maxId + 1);
    return ss.str();
}
