#include "CampusMediator.h"
#include "AccessControl.h"
#include "AlertDesk.h"
#include "Incident.h"
#include "MedicalTeam.h"
#include "SecurityTeam.h"
#include "ResponseComponent.h"
#include <iostream>

CampusMediator::CampusMediator() : security_(nullptr), medical_(nullptr), access_(nullptr), alerts_(nullptr) {
    handlers_[EventType::EvacuationRequired] = &CampusMediator::onEvacuationRequired;
    handlers_[EventType::CasualtiesReported] = &CampusMediator::onCasualtiesReported;
    handlers_[EventType::BreachDetected]     = &CampusMediator::onBreachDetected;
    handlers_[EventType::AllClear]           = &CampusMediator::onAllClear;
}

void CampusMediator::registerSecurity(SecurityTeam& t) { 
    security_ = &t; t.setMediator(this); 
}

void CampusMediator::registerMedical(MedicalTeam& t) { 
    medical_ = &t;  t.setMediator(this); 
}

void CampusMediator::registerAccess(AccessControl& a) { 
    access_ = &a;   a.setMediator(this); 
}

void CampusMediator::registerAlerts(AlertDesk& a) { 
    alerts_ = &a;   a.setMediator(this); 
}

void CampusMediator::say(const std::string& message) const {
    std::cout << "  [Mediator] " << message << std::endl;
}

void CampusMediator::notify(const ResponseComponent& sender, const EmergencyEvent& event) {
    say("<- " + sender.getName() + " reported " + toString(event.type) + " (incident " + std::to_string(event.incidentId) + ", " + event.location + ")");
    const auto found = handlers_.find(event.type);
    if (found == handlers_.end()) {
        say("WARNING: no handler for event, ignoring");
        return;
    }
    (this->*(found->second))(event);
}

void CampusMediator::onEvacuationRequired(const EmergencyEvent& e) {
    if (medical_) { 
        say("-> Medical: standby"); medical_->standby(e.location); 
    }
    else say("WARNING: no medical team registered");

    if (access_) { 
        say("-> AccessControl: restrict area"); access_->restrictArea(e.location); 
    }
    
    else say("WARNING: no access control registered");

    if (alerts_) { 
        say("-> Alert: evacuation notice");
        alerts_->sendNotice(3, e.location, "EVACUATE: " + e.detail); 
    }
    else say("WARNING: no alert service registered");
}

void CampusMediator::onCasualtiesReported(const EmergencyEvent& e) {
    if (security_) { 
        say("-> Security: secure scene for responders"); security_->dispatch(e.incidentId, e.location); 
    }
    else say("WARNING: no security team registered");

    if (access_) { 
        say("-> AccessControl: restrict area"); access_->restrictArea(e.location); 
    }
    else say("WARNING: no access control registered");
}

void CampusMediator::onBreachDetected(const EmergencyEvent& e) {
    if (security_) { 
        say("-> Security: respond to breach"); security_->dispatch(e.incidentId, e.location); 
    }
    else say("WARNING: no security team registered");

    if (alerts_) { 
        say("-> Alert: breach warning");
        alerts_->sendNotice(3, e.location, "Security breach detected"); 
    }
    else say("WARNING: no alert service registered");
}

void CampusMediator::onAllClear(const EmergencyEvent& e) {
    if (access_) { 
        say("-> AccessControl: restore access"); access_->unlockArea(e.location); 
    }

    if (medical_) { 
        say("-> Medical: stand down"); medical_->standDown(e.location); 
    }

    if (security_) { 
        say("-> Security: stand down"); security_->standDown(e.location); 
    }

    if (alerts_) { 
        say("-> Alert: all clear"); alerts_->sendNotice(1, e.location, "ALL CLEAR"); 
    }
}

void CampusMediator::update(const Incident& incident) {
    const std::string status = incident.getStatus();
    say("observed incident " + std::to_string(incident.getId()) + " -> " + status);
    if (status == "Resolved") {
        onAllClear(EmergencyEvent{EventType::AllClear, incident.getId(), incident.getLocation(), "Incident resolved"});
    }
}
