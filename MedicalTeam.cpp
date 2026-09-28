#include "MedicalTeam.h"
#include "Incident.h"
#include <algorithm>

MedicalTeam::MedicalTeam(int units) : ResponseComponent("Medical"), totalUnits_(units < 0 ? 0 : units) {}

int MedicalTeam::availableUnits() const {
    return totalUnits_ - static_cast<int>(deployed_.size());
}

bool MedicalTeam::dispatch(int incidentId, const std::string& location) {
    if (availableUnits() <= 0) {
        log("WARNING: no free unit for incident " + std::to_string(incidentId) + " at " + location);
        return false;
    }
    deployed_.push_back(location);
    log("unit dispatched to " + location + " (" + std::to_string(availableUnits()) +
        " unit(s) still free)");
    return true;
}

bool MedicalTeam::standby(const std::string& location) {
    if (!standbyAt_.insert(location).second) {
        log("already on standby for " + location);
        return false;
    }
    log("on standby near " + location);
    return true;
}

bool MedicalTeam::standDown(const std::string& location) {
    const std::size_t before = deployed_.size();
    deployed_.erase(std::remove(deployed_.begin(), deployed_.end(), location),
                    deployed_.end());
    const bool wasStandby = standbyAt_.erase(location) > 0;
    if (before == deployed_.size() && !wasStandby) {
        log("WARNING: nothing to stand down at " + location);
        return false;
    }
    log("stood down at " + location + " (" + std::to_string(availableUnits()) + " unit(s) free)");
    return true;
}

bool MedicalTeam::reportCasualties(int incidentId, const std::string& location, int count) {
    log(std::to_string(count) + " casualty(ies) at " + location);
    return report(EmergencyEvent{EventType::CasualtiesReported, incidentId, location, std::to_string(count) + " casualty(ies)"});
}

void MedicalTeam::dispatch(const Incident& incident) {
    dispatch(incident.getId(), incident.getLocation());
}
