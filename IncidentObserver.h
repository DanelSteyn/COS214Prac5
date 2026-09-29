#ifndef CAMPUSGUARD_INCIDENT_OBSERVER_H
#define CAMPUSGUARD_INCIDENT_OBSERVER_H

class Incident;

class IncidentObserver {
public:
    virtual ~IncidentObserver() {}
    virtual void update(const Incident& incident) = 0;
};

#endif