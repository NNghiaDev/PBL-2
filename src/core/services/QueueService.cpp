#include "core/services/QueueService.h"

void QueueService::enqueuePatient(const Patient& patient) {
    if (patient.getPriorityLevel() == 1) {
        emergencyQueue.push(patient);
    } else {
        standardQueue.push(patient);
    }
}

std::optional<Patient> QueueService::callNextPatient() {
    if (!emergencyQueue.isEmpty()) {
        Patient p = emergencyQueue.top();
        emergencyQueue.pop();
        return p;
    }
    if (!standardQueue.isEmpty()) {
        Patient p = standardQueue.front();
        standardQueue.pop();
        return p;
    }
    return std::nullopt;
}

bool QueueService::hasPendingPatients() const {
    return !emergencyQueue.isEmpty() || !standardQueue.isEmpty();
}

size_t QueueService::getEmergencyQueueCount() const {
    return emergencyQueue.size();
}

size_t QueueService::getStandardQueueCount() const {
    return standardQueue.size();
}

size_t QueueService::getTotalWaitingCount() const {
    return emergencyQueue.size() + standardQueue.size();
}

std::vector<Patient> QueueService::getEmergencyList() const {
    return emergencyQueue.getElements();
}

std::vector<Patient> QueueService::getStandardList() const {
    std::vector<Patient> res;
    // Copy queue without destroying original
    CustomQueue<Patient> copyQueue = standardQueue;
    while (!copyQueue.isEmpty()) {
        res.push_back(copyQueue.front());
        copyQueue.pop();
    }
    return res;
}

void QueueService::clearAll() {
    emergencyQueue.clear();
    standardQueue.clear();
}
