#ifndef CAMPUSGUARD_SECURITY_TEAM_H
#define CAMPUSGUARD_SECURITY_TEAM_H

#include "ResponseComponent.h"
#include "ResponseServices.h"
#include <set>
#include <string>

class SecurityTeam : public ResponseComponent, public SecurityResponse {
public:
    SecurityTeam();

    void dispatch(const Incident& incident) override;

    bool dispatch(int incidentId, const std::string& location);
    bool standDown(const std::string& location);
    bool isDeployedAt(const std::string& location) const;

    bool reportEvacuationRequired(int incidentId, const std::string& location, const std::string& reason);
    bool reportAllClear(int incidentId, const std::string& location);

private:
    std::set<std::string> deployed_;
    static bool needsEvacuation(const Incident& incident);
};

#endif
