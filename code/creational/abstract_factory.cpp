#include "abstract_factory.hpp"
#include <iostream>

void demonstrateAbstractFactoryPattern() {
    std::cout << "\n=== Abstract Factory Pattern Demo ===\n" << std::endl;

    // Create Windows application
    std::cout << "--- Windows Application ---" << std::endl;
    auto windowsFactory = std::make_shared<WindowsFactory>();
    Application windowsApp(windowsFactory);
    windowsApp.render();
    windowsApp.simulateUserInteraction();

    std::cout << "\n--- Mac Application ---" << std::endl;
    auto macFactory = std::make_shared<MacFactory>();
    Application macApp(macFactory);
    macApp.render();
    macApp.simulateUserInteraction();

    std::cout << "\n=== End Abstract Factory Pattern Demo ===\n" << std::endl;
} 