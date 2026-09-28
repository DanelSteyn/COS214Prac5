#include "ResponseComponent.h"
#include "ResponseMediator.h"
#include <iostream>

ResponseComponent::ResponseComponent(const std::string& name)
    : name_(name), mediator_(nullptr) {}

ResponseComponent::~ResponseComponent() {}

const std::string& ResponseComponent::getName() const { return name_; }
void ResponseComponent::setMediator(ResponseMediator* mediator) { mediator_ = mediator; }
bool ResponseComponent::hasMediator() const { return mediator_ != nullptr; }

bool ResponseComponent::report(const EmergencyEvent& event) {
    if (!mediator_) {
        log("WARNING: cannot report " + std::string(toString(event.type)) + " - not attached to a mediator");
        return false;
    }
    mediator_->notify(*this, event);
    return true;
}

void ResponseComponent::log(const std::string& message) const {
    std::cout << "  [" << name_ << "] " << message << std::endl;
}
