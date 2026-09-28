#include "AccessControl.h"
#include "AlertAdapter.h"
#include "AlertDesk.h"
#include "CampusMediator.h"
#include "Command.h"
#include "EmergencyFacade.h"
#include "Incident.h"
#include "MedicalTeam.h"
#include "SecurityTeam.h"
#include "StatusDisplay.h"
#include <iostream>

static void banner(const char* title) { std::cout << "\n=== " << title << " ===\n"; }

int main() {
    LegacyAlertSystem legacy;
    AlertAdapter adapter(legacy);
    SecurityTeam security;
    MedicalTeam medical(2);
    AccessControl access;
    AlertDesk alerts(&adapter);
    CampusMediator mediator;
    mediator.registerSecurity(security);
    mediator.registerMedical(medical);
    mediator.registerAccess(access);
    mediator.registerAlerts(alerts);
    StatusDisplay display;
    OperatorConsole console;
    EmergencyFacade facade(security, medical, access, alerts);

    banner("Scenario 1: fire / evacuation (State, Observer, Command, Mediator, Adapter)");
    Incident fire(1, "Engineering", "Fire evacuation");
    fire.addObserver(display);
    fire.addObserver(mediator);
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
    fire.removeObserver(mediator);

    banner("Scenario 2: medical emergency (Facade)");
    Incident injury(2, "Library", "Student needs medical assistance");
    injury.addObserver(display);
    injury.addObserver(mediator);
    if (facade.handleMedicalEmergency(injury)) {
        injury.resolve();
    }
    if (!facade.handleMedicalEmergency(injury)) {
        std::cout << "Facade refused to re-run a resolved incident.\n";
    }
    injury.removeObserver(display);
    injury.removeObserver(mediator);

    banner("Other invalid operations");
    access.unlockArea("Gym");
    access.reportBreach(2, "Gym");
    std::cout << "\nAlerts sent through AlertDesk: " << alerts.alertsSent() << '\n';
    return 0;
}
