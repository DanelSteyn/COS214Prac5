#include "Incident.h"
#include "IncidentObserver.h"
#include "IncidentState.h"
#include "ReportedState.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

namespace {
bool isBlank(const std::string& value) {
    return value.find_first_not_of(" \t\r\n\f\v") == std::string::npos;
}
}

Incident::Incident(int id, const std::string& location,
                   const std::string& description)
    : id_(id), location_(location), description_(description),
      state_(new ReportedState()) {
    if (id <= 0 || isBlank(location) || isBlank(description)) {
        throw std::invalid_argument(
            "Incident needs a positive ID, a location and a description.");
    }
}

Incident::~Incident() = default;
int Incident::getId() const { return id_; }
const std::string& Incident::getLocation() const { return location_; }
const std::string& Incident::getDescription() const { return description_; }
std::string Incident::getStatus() const { return state_->getName(); }

bool Incident::activate() { return transitionTo(state_->activate()); }
bool Incident::resolve() { return transitionTo(state_->resolve()); }

bool Incident::transitionTo(std::unique_ptr<IncidentState> next) {
    if (!next) return false;
    // The state's method has returned before the old state is destroyed.
    state_ = std::move(next);
    notifyObservers();
    return true;
}

bool Incident::addObserver(IncidentObserver& observer) {
    if (std::find(observers_.begin(), observers_.end(), &observer)
            != observers_.end()) return false;
    observers_.push_back(&observer);
    return true;
}

bool Incident::removeObserver(IncidentObserver& observer) {
    const auto found = std::find(observers_.begin(), observers_.end(), &observer);
    if (found == observers_.end()) return false;
    observers_.erase(found);
    return true;
}

void Incident::notifyObservers() {
    for (IncidentObserver* observer : observers_) observer->update(*this);
}