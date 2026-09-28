#include "StatusDisplay.h"
#include "Incident.h"
#include <iostream>

void StatusDisplay::update(const Incident& incident) {
    updates_.push_back(std::to_string(incident.getId()) + ":" + incident.getStatus());
    std::cout << "[Observer] Incident " << incident.getId() << " at "
              << incident.getLocation() << " -> " << incident.getStatus() << '\n';
}
