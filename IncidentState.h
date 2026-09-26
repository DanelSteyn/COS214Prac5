#ifndef CAMPUSGUARD_INCIDENT_STATE_H
#define CAMPUSGUARD_INCIDENT_STATE_H

#include <memory>

class IncidentState {
public:
    virtual ~IncidentState() {}
    virtual const char* getName() const = 0;
    virtual std::unique_ptr<IncidentState> activate() const;
    virtual std::unique_ptr<IncidentState> resolve() const;
};

#endif