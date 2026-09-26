#ifndef CAMPUSGUARD_REPORTED_STATE_H
#define CAMPUSGUARD_REPORTED_STATE_H
#include "IncidentState.h"

class ReportedState : public IncidentState {
public:
    const char* getName() const override;
    std::unique_ptr<IncidentState> activate() const override;
};
#endif