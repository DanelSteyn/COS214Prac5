#include "SecurityTeam.h"
#include "Incident.h"
#include <algorithm>
#include <cctype>

SecurityTeam::SecurityTeam() : ResponseComponent("Security") {}

bool SecurityTeam::dispatch(int incidentId, const std::string& location) {
    if (deployed_.count(location)) {
        log("already deployed at " + location + " (incident " + std::to_string(incidentId) + ")");
        return false;
    }
    deployed_.insert(location);
    log("officers dispatched to " + location + " for incident " + std::to_string(incidentId));
    return true;
}

bool SecurityTeam::standDown(const std::string& location) {
    if (deployed_.erase(location) == 0) {
        log("WARNING: nobody deployed at " + location + " to stand down");
        return false;
    }
    log("officers stood down from " + location);
    return true;
}

bool SecurityTeam::isDeployedAt(const std::string& location) const {
    return deployed_.count(location) > 0;
}

bool SecurityTeam::reportEvacuationRequired(int incidentId, const std::string& location, const std::string& reason) {
    log("on scene at " + location + ": evacuation required (" + reason + ")");
    return report(EmergencyEvent{EventType::EvacuationRequired, incidentId, location, reason});
}

bool SecurityTeam::reportAllClear(int incidentId, const std::string& location) {
    log("scene at " + location + " is safe");
    return report(EmergencyEvent{EventType::AllClear, incidentId, location, "Scene declared safe"});
}

void SecurityTeam::dispatch(const Incident& incident) {
    if (!dispatch(incident.getId(), incident.getLocation())) return;
    if (needsEvacuation(incident)) {
        reportEvacuationRequired(incident.getId(), incident.getLocation(), incident.getDescription());
    }
}

bool SecurityTeam::needsEvacuation(const Incident& incident) {
    std::string text = incident.getDescription();
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    static const char* const hazards[] = {"fire", "evacuat", "gas leak", "bomb"};
    for (const char* h : hazards) if (text.find(h) != std::string::npos) return true;
    return false;
}
