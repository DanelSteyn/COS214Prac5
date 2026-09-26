#ifndef CAMPUSGUARD_RESOLVED_STATE_H
#define CAMPUSGUARD_RESOLVED_STATE_H
#include "IncidentState.h"

class ResolvedState : public IncidentState {
public:
    const char* getName() const override;
};
#endif