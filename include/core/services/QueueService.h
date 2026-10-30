#ifndef QUEUE_SERVICE_H
#define QUEUE_SERVICE_H

#include "core/models/Patient.h"
#include "core/dsa/CustomPriorityQueue.hpp"
#include "core/dsa/CustomQueue.hpp"
#include <optional>
#include <vector>

/**
 * @brief QueueService manages patient check-in triage.
 * Uses CustomPriorityQueue for emergency patients (priority 1)
 * and CustomQueue for standard/priority patients (priority 2 and 3).
 */
class QueueService {
private:
    CustomPriorityQueue<Patient> emergencyQueue; // Priority 1 (Max-Heap)
    CustomQueue<Patient> standardQueue;           // Priority 2 & 3 (FIFO)

public:
    QueueService() = default;

    // Check in patient into the appropriate queue
    void enqueuePatient(const Patient& patient);

    // Call next patient: emergency cases are always prioritized
    std::optional<Patient> callNextPatient();

    bool hasPendingPatients() const;
    size_t getEmergencyQueueCount() const;
    size_t getStandardQueueCount() const;
    size_t getTotalWaitingCount() const;

    // Helper to get pending lists for UI display
    std::vector<Patient> getEmergencyList() const;
    std::vector<Patient> getStandardList() const;
    
    void clearAll();
};

#endif // QUEUE_SERVICE_H
