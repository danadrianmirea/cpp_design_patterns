#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Colleague;
class ChatRoom;

// Mediator interface
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void sendMessage(const std::string& message, Colleague* sender) = 0;
};

// Colleague interface
class Colleague {
protected:
    Mediator* mediator_;
    std::string name_;
public:
    Colleague(Mediator* mediator, const std::string& name) 
        : mediator_(mediator), name_(name) {}
    virtual ~Colleague() = default;
    virtual void send(const std::string& message) = 0;
    virtual void receive(const std::string& message) = 0;
    const std::string& getName() const { return name_; }
};

// Concrete Colleague: User
class User : public Colleague {
public:
    User(Mediator* mediator, const std::string& name) 
        : Colleague(mediator, name) {}
    
    void send(const std::string& message) override {
        std::cout << name_ << " sends: " << message << std::endl;
        mediator_->sendMessage(message, this);
    }
    
    void receive(const std::string& message) override {
        std::cout << name_ << " receives: " << message << std::endl;
    }
};

// Concrete Mediator: ChatRoom
class ChatRoom : public Mediator {
    std::vector<std::shared_ptr<Colleague>> users_;
public:
    void addUser(std::shared_ptr<Colleague> user) {
        users_.push_back(user);
    }
    
    void sendMessage(const std::string& message, Colleague* sender) override {
        for (auto& user : users_) {
            if (user.get() != sender) {
                user->receive(message);
            }
        }
    }
};

void demonstrateMediatorPattern();

#endif // MEDIATOR_HPP 