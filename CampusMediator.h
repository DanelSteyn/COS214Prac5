#ifndef CAMPUSGUARD_CAMPUS_MEDIATOR_H
#define CAMPUSGUARD_CAMPUS_MEDIATOR_H

#include "IncidentObserver.h"
#include "ResponseMediator.h"
#include <map>

class SecurityTeam;
class MedicalTeam;
class AccessControl;
class AlertDesk;

class CampusMediator : public ResponseMediator, public IncidentObserver {
public:
    CampusMediator();

    void registerSecurity(SecurityTeam& team);
    void registerMedical(MedicalTeam& team);
    void registerAccess(AccessControl& access);
    void registerAlerts(AlertDesk& alerts);

    void notify(const ResponseComponent& sender, const EmergencyEvent& event) override;
    void update(const Incident& incident) override;

private:
    typedef void (CampusMediator::*Handler)(const EmergencyEvent&);
    std::map<EventType, Handler> handlers_;

    SecurityTeam* security_;
    MedicalTeam* medical_;
    AccessControl* access_;
    AlertDesk* alerts_;

    void onEvacuationRequired(const EmergencyEvent& event);
    void onCasualtiesReported(const EmergencyEvent& event);
    void onBreachDetected(const EmergencyEvent& event);
    void onAllClear(const EmergencyEvent& event);

    void say(const std::string& message) const;
};

#endif
