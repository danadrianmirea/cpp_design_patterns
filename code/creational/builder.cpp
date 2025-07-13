#include "builder.hpp"
#include <iostream>

void demonstrateBuilderPattern() {
    std::cout << "\n=== Builder Pattern Demo ===\n" << std::endl;

    ComputerDirector director;

    // Build a gaming computer
    std::cout << "--- Building Gaming Computer ---" << std::endl;
    auto gamingBuilder = std::make_shared<GamingComputerBuilder>();
    director.setBuilder(gamingBuilder);
    auto gamingComputer = director.construct();
    gamingComputer->display();

    std::cout << "\n--- Building Office Computer ---" << std::endl;
    auto officeBuilder = std::make_shared<OfficeComputerBuilder>();
    director.setBuilder(officeBuilder);
    auto officeComputer = director.construct();
    officeComputer->display();

    std::cout << "\n--- Building Minimal Office Computer ---" << std::endl;
    director.setBuilder(officeBuilder);
    auto minimalComputer = director.constructMinimal();
    minimalComputer->display();

    std::cout << "\n=== End Builder Pattern Demo ===\n" << std::endl;
} 