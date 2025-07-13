#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <memory>

// Forward declarations
class VendingMachine;

// State interface
class State {
public:
    virtual ~State() = default;
    virtual void insertCoin(VendingMachine* machine) = 0;
    virtual void ejectCoin(VendingMachine* machine) = 0;
    virtual void turnCrank(VendingMachine* machine) = 0;
    virtual void dispense(VendingMachine* machine) = 0;
};

// Context: Vending Machine
class VendingMachine {
    std::shared_ptr<State> state_;
    int count_;
public:
    VendingMachine(int count);
    
    void setState(std::shared_ptr<State> state) {
        state_ = state;
    }
    
    void insertCoin() {
        state_->insertCoin(this);
    }
    
    void ejectCoin() {
        state_->ejectCoin(this);
    }
    
    void turnCrank() {
        state_->turnCrank(this);
    }
    
    void dispense() {
        state_->dispense(this);
    }
    
    int getCount() const { return count_; }
    void setCount(int count) { count_ = count; }
    
    void releaseBall() {
        if (count_ > 0) {
            std::cout << "A ball comes rolling out the slot..." << std::endl;
            count_--;
        }
    }
};

// Concrete States
class IdleState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "You inserted a coin" << std::endl;
        // Change to HasMoneyState
    }
    
    void ejectCoin(VendingMachine* machine) override {
        std::cout << "You haven't inserted a coin" << std::endl;
    }
    
    void turnCrank(VendingMachine* machine) override {
        std::cout << "You turned, but there's no coin" << std::endl;
    }
    
    void dispense(VendingMachine* machine) override {
        std::cout << "You need to pay first" << std::endl;
    }
};

class HasMoneyState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "You can't insert another coin" << std::endl;
    }
    
    void ejectCoin(VendingMachine* machine) override {
        std::cout << "Coin returned" << std::endl;
        // Change to IdleState
    }
    
    void turnCrank(VendingMachine* machine) override {
        std::cout << "You turned..." << std::endl;
        // Change to SoldState
    }
    
    void dispense(VendingMachine* machine) override {
        std::cout << "No ball dispensed" << std::endl;
    }
};

class SoldState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Please wait, we're already giving you a ball" << std::endl;
    }
    
    void ejectCoin(VendingMachine* machine) override {
        std::cout << "Sorry, you already turned the crank" << std::endl;
    }
    
    void turnCrank(VendingMachine* machine) override {
        std::cout << "Turning twice doesn't get you another ball!" << std::endl;
    }
    
    void dispense(VendingMachine* machine) override {
        machine->releaseBall();
        if (machine->getCount() > 0) {
            // Change to IdleState
        } else {
            // Change to SoldOutState
        }
    }
};

class SoldOutState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Sorry, the machine is sold out" << std::endl;
    }
    
    void ejectCoin(VendingMachine* machine) override {
        std::cout << "You can't eject, you haven't inserted a coin yet" << std::endl;
    }
    
    void turnCrank(VendingMachine* machine) override {
        std::cout << "You turned, but there are no balls" << std::endl;
    }
    
    void dispense(VendingMachine* machine) override {
        std::cout << "No ball dispensed" << std::endl;
    }
};

void demonstrateStatePattern();

#endif // STATE_HPP 