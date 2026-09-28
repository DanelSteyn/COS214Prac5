#ifndef CAMPUSGUARD_ALERT_ADAPTER_H
#define CAMPUSGUARD_ALERT_ADAPTER_H
#include <string>
class Incident;
class AlertService {
public:
    virtual ~AlertService() {}
    virtual void sendAlert(const Incident& incident) = 0;
    virtual void sendNotice(int severity, const std::string& location, const std::string& message) = 0;
};
class LegacyAlertSystem {
public:
    void broadcast(int priority, const std::string& text);
    int getLastPriority() const { return lastPriority_; }
    const std::string& getLastMessage() const { return lastMessage_; }
private:
    int lastPriority_ = 0;
    std::string lastMessage_;
};
class AlertAdapter : public AlertService {
public:
    explicit AlertAdapter(LegacyAlertSystem& legacy) : legacy_(legacy) {}
    void sendAlert(const Incident& incident) override;
    void sendNotice(int severity, const std::string& location, const std::string& message) override;
private:
    LegacyAlertSystem& legacy_;
};
#endif
