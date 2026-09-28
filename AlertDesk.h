#ifndef CAMPUSGUARD_ALERT_DESK_H
#define CAMPUSGUARD_ALERT_DESK_H

#include "AlertAdapter.h"
#include "ResponseComponent.h"
#include <string>
class AlertDesk : public ResponseComponent, public AlertService {
public:
    explicit AlertDesk(AlertService* backend = nullptr);

    void setBackend(AlertService* backend);
    void sendAlert(const Incident& incident) override;
    void sendNotice(int severity, const std::string& location, const std::string& message) override;
    int alertsSent() const;

private:
    AlertService* backend_;
    int sent_;
};

#endif
