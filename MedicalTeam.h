#ifndef CAMPUSGUARD_MEDICAL_TEAM_H
#define CAMPUSGUARD_MEDICAL_TEAM_H

#include "ResponseComponent.h"
#include "ResponseServices.h"
#include <set>
#include <string>
#include <vector>

class MedicalTeam : public ResponseComponent, public MedicalResponse {
public:
    explicit MedicalTeam(int units = 2);

    void dispatch(const Incident& incident) override;

    bool dispatch(int incidentId, const std::string& location);
    bool standby(const std::string& location);
    bool standDown(const std::string& location);
    int availableUnits() const;

    bool reportCasualties(int incidentId, const std::string& location, int count);

private:
    int totalUnits_;
    std::vector<std::string> deployed_;
    std::set<std::string> standbyAt_;
};

#endif
