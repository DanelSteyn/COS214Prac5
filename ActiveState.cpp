#include "ActiveState.h"
#include "ResolvedState.h"

const char* ActiveState::getName() const { return "Active"; }

std::unique_ptr<IncidentState> ActiveState::resolve() const {
    return std::unique_ptr<IncidentState>(new ResolvedState());
}