#ifndef CAMPUSGUARD_INCIDENT_H
#define CAMPUSGUARD_INCIDENT_H

#include <memory>
#include <string>
#include <vector>

class IncidentState;
class IncidentObserver;

class Incident {
public:
    Incident(int id, const std::string& location, const std::string& description);
    ~Incident();
    Incident(const Incident&) = delete;
    Incident& operator=(const Incident&) = delete;

    int getId() const;
    const std::string& getLocation() const;
    const std::string& getDescription() const;
    std::string getStatus() const;

    // Return false for an invalid transition
    bool activate();
    bool resolve();

    // Non-owning subscriptions. Observer must remain alive until removed
    bool addObserver(IncidentObserver& observer);
    bool removeObserver(IncidentObserver& observer);

private:
    int id_;
    std::string location_;
    std::string description_;
    std::unique_ptr<IncidentState> state_;
    std::vector<IncidentObserver*> observers_;

    bool transitionTo(std::unique_ptr<IncidentState> next);
    void notifyObservers();
};

#endif