#ifndef CAMPUSGUARD_COMMAND_H
#define CAMPUSGUARD_COMMAND_H
#include "ResponseServices.h"
#include "AlertAdapter.h"

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};
class DispatchSecurityCommand : public Command {
public:
    DispatchSecurityCommand(SecurityResponse& receiver, const Incident& incident)
        : receiver_(receiver), incident_(incident) {}
    void execute() override { receiver_.dispatch(incident_); }
private:
    SecurityResponse& receiver_;
    const Incident& incident_;
};
class SecureAreaCommand : public Command {
public:
    SecureAreaCommand(AccessResponse& receiver, const Incident& incident)
        : receiver_(receiver), incident_(incident) {}
    void execute() override { receiver_.restrictAccess(incident_); }
private:
    AccessResponse& receiver_;
    const Incident& incident_;
};
class SendAlertCommand : public Command {
public:
    SendAlertCommand(AlertService& receiver, const Incident& incident)
        : receiver_(receiver), incident_(incident) {}
    void execute() override { receiver_.sendAlert(incident_); }
private:
    AlertService& receiver_;
    const Incident& incident_;
};
class OperatorConsole {
public:
    void execute(Command& command) { command.execute(); }
};
#endif
