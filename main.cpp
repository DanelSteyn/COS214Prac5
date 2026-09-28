#include "Incident.h"
#include "StatusDisplay.h"
#include "Command.h"
#include "EmergencyFacade.h"
#include <iostream>

// Temporary receivers until Person B's classes are added.
class TestSecurity : public SecurityResponse {
public:
    int assignedIncident = 0;
    void dispatch(const Incident& incident) override {
        assignedIncident = incident.getId();
        std::cout << "Security dispatched to " << incident.getLocation() << '\n';
    }
};

class TestMedical : public MedicalResponse {
public:
    int assignedIncident = 0;
    void dispatch(const Incident& incident) override {
        assignedIncident = incident.getId();
        std::cout << "Medical dispatched to " << incident.getLocation() << '\n';
    }
};

class TestAccess : public AccessResponse {
public:
    std::string restrictedArea;
    void restrictAccess(const Incident& incident) override {
        restrictedArea = incident.getLocation();
        std::cout << "Access restricted at " << restrictedArea << '\n';
    }
};

int main() {
    TestSecurity security;
    TestMedical medical;
    TestAccess access;
    LegacyAlertSystem legacy;
    AlertAdapter alerts(legacy);
    StatusDisplay display;
    OperatorConsole console;

    // Example 1: State, Observer, Command and Adapter.
    std::cout << "\nFire emergency!!\n";
    Incident fire(1, "Engineering", "Fire evacuation");
    fire.addObserver(display);
    std::cout << "Starting state: " << fire.getStatus() << '\n';
    fire.activate(); 

    DispatchSecurityCommand dispatch(security, fire);
    SecureAreaCommand secure(access, fire);
    SendAlertCommand alert(alerts, fire);
    console.execute(dispatch);
    console.execute(secure);
    console.execute(alert);

    fire.resolve(); 
    if (!fire.activate()) {
        std::cout << "Cannot activate an already resolved incident.\n";
    }
    fire.removeObserver(display);

    // Example 2: The facade runs the medical workflow in one call.
    std::cout << "\nMedical emergency!!!\n";
    Incident injury(2, "Library", "Student needs medical assistance");
    injury.addObserver(display);
    EmergencyFacade facade(security, medical, access, alerts);
    if (facade.handleMedicalEmergency(injury)) {
        injury.resolve();
    }
    injury.removeObserver(display);

    return 0;
}
