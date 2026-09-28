#ifndef CAMPUSGUARD_STATUS_DISPLAY_H
#define CAMPUSGUARD_STATUS_DISPLAY_H
#include "IncidentObserver.h"
#include <string>
#include <vector>

class StatusDisplay : public IncidentObserver {
public:
    void update(const Incident& incident) override;
    const std::vector<std::string>& getUpdates() const { return updates_; }
private:
    std::vector<std::string> updates_;
};
#endif
