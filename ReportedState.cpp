
#include "ReportedState.h"
#include "ActiveState.h"

const char* ReportedState::getName() const { return "Reported"; }

std::unique_ptr<IncidentState> ReportedState::activate() const {
    return std::unique_ptr<IncidentState>(new ActiveState());
}