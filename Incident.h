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
    Incident(const Incident&) = delete; //made incident non-copyable to avoid creating ambiguous ownership 
    Incident& operator=(const Incident&) = delete; //of the state and observers (due to the unique_ptr)

    int getId() const;
    const std::string& getLocation() const;
    const std::string& getDescription() const;
    std::string getStatus() const;


    bool activate(); //delegates to current incedent state
    bool resolve();

    // Non-owning subscriptions. Observer must remain alive until removed
    bool addObserver(IncidentObserver& observer);
    bool removeObserver(IncidentObserver& observer);

private:
    int id_;
    std::string location_;
    std::string description_;
    std::unique_ptr<IncidentState> state_; //(transitions) exclusive ownership of the state
    std::vector<IncidentObserver*> observers_;

    bool transitionTo(std::unique_ptr<IncidentState> next); //where state and observer connect
    void notifyObservers();
};

#endif