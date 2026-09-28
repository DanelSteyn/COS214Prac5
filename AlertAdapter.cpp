#include "AlertAdapter.h"
#include "Incident.h"
#include <iostream>

void LegacyAlertSystem::broadcast(int priority, const std::string& text) {
    lastPriority_ = priority;
    lastMessage_ = text;
    std::cout << "[Legacy alert] Priority " << priority << ": " << text << '\n';
}
void AlertAdapter::sendAlert(const Incident& incident) {
    // Translate the domain object into the legacy priority/text protocol.
    legacy_.broadcast(1, "Incident " + std::to_string(incident.getId()) + " at "
        + incident.getLocation() + ": " + incident.getDescription());
}
