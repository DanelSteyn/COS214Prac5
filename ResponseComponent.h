#ifndef CAMPUSGUARD_RESPONSE_COMPONENT_H
#define CAMPUSGUARD_RESPONSE_COMPONENT_H

#include "EmergencyEvent.h"
#include <string>

class ResponseMediator;

class ResponseComponent {
public:
    explicit ResponseComponent(const std::string& name);
    virtual ~ResponseComponent();
    ResponseComponent(const ResponseComponent&) = delete;
    ResponseComponent& operator=(const ResponseComponent&) = delete;

    const std::string& getName() const;
    void setMediator(ResponseMediator* mediator);
    bool hasMediator() const;

protected:
    bool report(const EmergencyEvent& event);
    void log(const std::string& message) const;

private:
    std::string name_;
    ResponseMediator* mediator_;
};

#endif
