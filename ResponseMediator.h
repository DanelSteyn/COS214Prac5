#ifndef CAMPUSGUARD_RESPONSE_MEDIATOR_H
#define CAMPUSGUARD_RESPONSE_MEDIATOR_H

#include "EmergencyEvent.h"

class ResponseComponent;

class ResponseMediator {
public:
    virtual ~ResponseMediator() {}
    virtual void notify(const ResponseComponent& sender, const EmergencyEvent& event) = 0;
};

#endif
