#include "visitor.hpp"
#include <iostream>

void demonstrateVisitorPattern() {
    std::cout << "\n=== Visitor Pattern Demo ===\n" << std::endl;

    // Create computer parts
    auto cpu = std::make_shared<CPU>("Intel i7-12700K", 399.99);
    auto gpu = std::make_shared<GPU>("NVIDIA RTX 3080", 699.99);
    auto memory = std::make_shared<Memory>("Corsair 32GB DDR4", 149.99);
    auto hardDrive = std::make_shared<HardDrive>("Samsung 1TB SSD", 99.99);

    // Create a computer and add parts
    Computer computer;
    computer.addPart(cpu);
    computer.addPart(gpu);
    computer.addPart(memory);
    computer.addPart(hardDrive);

    // Use Price Visitor
    std::cout << "Price Calculation:" << std::endl;
    std::cout << "==================" << std::endl;
    PriceVisitor priceVisitor;
    computer.accept(&priceVisitor);
    std::cout << "Total Price: $" << priceVisitor.getTotalPrice() << std::endl;

    std::cout << "\nDiagnostic Check:" << std::endl;
    std::cout << "=================" << std::endl;
    DiagnosticVisitor diagnosticVisitor;
    computer.accept(&diagnosticVisitor);

    std::cout << "\n=== End Visitor Pattern Demo ===\n" << std::endl;
} 