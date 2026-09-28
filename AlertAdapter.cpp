#include "AlertAdapter.h"
#include "Incident.h"
#include <iostream>

void LegacyAlertSystem::broadcast(int priority, const std::string& text) {
    lastPriority_ = priority;
    lastMessage_ = text;
    std::cout << "[Legacy alert] Priority " << priority << ": " << text << '\n';
}
void AlertAdapter::sendAlert(const Incident& incident) {
    legacy_.broadcast(1, "Incident " + std::to_string(incident.getId()) + " at " + incident.getLocation() + ": " + incident.getDescription());
}

void AlertAdapter::sendNotice(int severity, const std::string& location, const std::string& message) {
    const int priority = severity >= 3 ? 1 : (severity == 2 ? 2 : 3);
    legacy_.broadcast(priority, "[" + location + "] " + message);
}