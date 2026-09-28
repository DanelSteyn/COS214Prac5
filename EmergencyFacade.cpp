#include "EmergencyFacade.h"
#include "Incident.h"
#include <iostream>

bool EmergencyFacade::handleMedicalEmergency(Incident& incident) {
    if (!incident.activate()) {
        std::cout << "[Facade] Rejected incident " << incident.getId()
                  << ": expected Reported, got " << incident.getStatus() << '\n';
        return false;
    }
    medical_.dispatch(incident);
    security_.dispatch(incident);
    access_.restrictAccess(incident);
    alerts_.sendAlert(incident);
    return true;
}
