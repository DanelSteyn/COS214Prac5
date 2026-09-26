#ifndef CAMPUSGUARD_ACTIVE_STATE_H
#define CAMPUSGUARD_ACTIVE_STATE_H
#include "IncidentState.h"

class ActiveState : public IncidentState {
public:
    const char* getName() const override;
    std::unique_ptr<IncidentState> resolve() const override;
};
#endif