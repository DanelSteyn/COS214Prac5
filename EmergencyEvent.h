#ifndef CAMPUSGUARD_EMERGENCY_EVENT_H
#define CAMPUSGUARD_EMERGENCY_EVENT_H

#include <string>

enum class EventType {
    EvacuationRequired,
    CasualtiesReported,
    BreachDetected,
    AllClear
};

struct EmergencyEvent {
    EventType type;
    int incidentId;
    std::string location;
    std::string detail;
};

inline const char* toString(EventType type) {
    switch (type) {
        case EventType::EvacuationRequired: return "EVACUATION_REQUIRED";
        case EventType::CasualtiesReported: return "CASUALTIES_REPORTED";
        case EventType::BreachDetected: return "BREACH_DETECTED";
        case EventType::AllClear: return "ALL_CLEAR";
    }
    return "UNKNOWN";
}

#endif
