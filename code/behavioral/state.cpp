#include "state.hpp"
#include <iostream>

// VendingMachine constructor
VendingMachine::VendingMachine(int count) : count_(count) {
    if (count > 0) {
        setState(std::make_shared<IdleState>());
    } else {
        setState(std::make_shared<SoldOutState>());
    }
}

void demonstrateStatePattern() {
    std::cout << "\n=== State Pattern Demo ===\n" << std::endl;

    // Create a vending machine with 2 balls
    VendingMachine machine(2);
    
    std::cout << "Vending Machine Demo:" << std::endl;
    std::cout << "=====================" << std::endl;

    // Test the machine
    machine.insertCoin();
    machine.turnCrank();
    machine.dispense();
    
    std::cout << "\nTrying to get another ball:" << std::endl;
    machine.insertCoin();
    machine.turnCrank();
    machine.dispense();
    
    std::cout << "\nTrying to get a ball when sold out:" << std::endl;
    machine.insertCoin();
    machine.turnCrank();
    machine.dispense();

    std::cout << "\n=== End State Pattern Demo ===\n" << std::endl;
} 