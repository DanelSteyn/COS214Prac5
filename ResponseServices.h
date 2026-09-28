#ifndef CAMPUSGUARD_RESPONSE_SERVICES_H
#define CAMPUSGUARD_RESPONSE_SERVICES_H
class Incident;

class SecurityResponse {
public:
    virtual ~SecurityResponse() {}
    virtual void dispatch(const Incident& incident) = 0;
};
class MedicalResponse {
public:
    virtual ~MedicalResponse() {}
    virtual void dispatch(const Incident& incident) = 0;
};
class AccessResponse {
public:
    virtual ~AccessResponse() {}
    virtual void restrictAccess(const Incident& incident) = 0;
};
#endif
