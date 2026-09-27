#include "IncidentState.h"

std::unique_ptr<IncidentState> IncidentState::activate() const {
    return std::unique_ptr<IncidentState>();
}

std::unique_ptr<IncidentState> IncidentState::resolve() const {
    return std::unique_ptr<IncidentState>();
}