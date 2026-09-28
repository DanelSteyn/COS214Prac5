#ifndef CAMPUSGUARD_ACCESS_CONTROL_H
#define CAMPUSGUARD_ACCESS_CONTROL_H

#include "ResponseComponent.h"
#include "ResponseServices.h"
#include <set>
#include <string>

class AccessControl : public ResponseComponent, public AccessResponse {
public:
    AccessControl();

    void restrictAccess(const Incident& incident) override;

    bool restrictArea(const std::string& area);
    bool unlockArea(const std::string& area);
    bool isRestricted(const std::string& area) const;
    bool reportBreach(int incidentId, const std::string& area);

private:
    std::set<std::string> restricted_;
};

#endif
