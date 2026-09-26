#ifndef CAMPUSGUARD_INCIDENT_OBSERVER_H
#define CAMPUSGUARD_INCIDENT_OBSERVER_H

class Incident;

class IncidentObserver {
public:
    virtual ~IncidentObserver() {}
    // Inspect the incident after a successful change. Callbacks must not throw
    // or change the incident/subscriptions during notification.
    virtual void update(const Incident& incident) = 0;
};

#endif