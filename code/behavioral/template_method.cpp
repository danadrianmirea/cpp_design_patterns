#include "template_method.hpp"
#include <iostream>

void demonstrateTemplateMethodPattern() {
    std::cout << "\n=== Template Method Pattern Demo ===\n" << std::endl;

    std::cout << "Preparing Coffee:" << std::endl;
    std::cout << "=================" << std::endl;
    Coffee coffee;
    coffee.prepareBeverage();

    std::cout << "\nPreparing Tea:" << std::endl;
    std::cout << "==============" << std::endl;
    Tea tea;
    tea.prepareBeverage();

    std::cout << "\n=== End Template Method Pattern Demo ===\n" << std::endl;
} 