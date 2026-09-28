#ifndef CAMPUSGUARD_EMERGENCY_FACADE_H
#define CAMPUSGUARD_EMERGENCY_FACADE_H
#include "ResponseServices.h"
#include "AlertAdapter.h"
class EmergencyFacade {
public:
    EmergencyFacade(SecurityResponse& security, MedicalResponse& medical,
                    AccessResponse& access, AlertService& alerts)
        : security_(security), medical_(medical), access_(access), alerts_(alerts) {}
    // Reject an invalid lifecycle entry before any response actions.
    bool handleMedicalEmergency(Incident& incident);
private:
    SecurityResponse& security_;
    MedicalResponse& medical_;
    AccessResponse& access_;
    AlertService& alerts_;
};
#endif
