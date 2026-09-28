#include "AccessControl.h"
#include "Incident.h"

AccessControl::AccessControl() : ResponseComponent("AccessControl") {}

bool AccessControl::restrictArea(const std::string& area) {
    if (!restricted_.insert(area).second) {
        log(area + " is already restricted");
        return false;
    }
    log("doors locked, access restricted to " + area);
    return true;
}

bool AccessControl::unlockArea(const std::string& area) {
    if (restricted_.erase(area) == 0) {
        log("WARNING: " + area + " is not restricted, nothing to unlock");
        return false;
    }
    log("access restored to " + area);
    return true;
}

bool AccessControl::isRestricted(const std::string& area) const {
    return restricted_.count(area) > 0;
}

bool AccessControl::reportBreach(int incidentId, const std::string& area) {
    if (!isRestricted(area)) {
        log("WARNING: breach reported for " + area + " but it is not restricted");
        return false;
    }
    log("unauthorised entry detected at restricted area " + area);
    return report(EmergencyEvent{EventType::BreachDetected, incidentId, area, "Unauthorised entry into restricted area"});
}

void AccessControl::restrictAccess(const Incident& incident) {
    restrictArea(incident.getLocation());
}
