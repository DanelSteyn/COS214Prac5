#include "AlertDesk.h"
#include "Incident.h"

AlertDesk::AlertDesk(AlertService* backend) : ResponseComponent("Alert"), backend_(backend), sent_(0) {}

void AlertDesk::setBackend(AlertService* backend) 
{
    backend_ = backend; 
}

int AlertDesk::alertsSent() const 
{ 
    return sent_; 
}

void AlertDesk::sendAlert(const Incident& incident) {
    if (!backend_) { log("WARNING: no alert backend configured"); return; }
    log("broadcasting alert for incident " + std::to_string(incident.getId()));
    backend_->sendAlert(incident);
    ++sent_;
}

void AlertDesk::sendNotice(int severity, const std::string& location, const std::string& message) {
    if (!backend_) { log("WARNING: no alert backend configured"); return; }
    if (message.empty()) { log("WARNING: refusing to send an empty alert"); return; }
    log("broadcasting notice for " + location);
    backend_->sendNotice(severity, location, message);
    ++sent_;
}
