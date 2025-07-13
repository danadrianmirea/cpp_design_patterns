#include "chain_of_responsibility.hpp"
#include <iostream>

// Function to demonstrate the Chain of Responsibility pattern
void demonstrateChainOfResponsibility() {
    std::cout << "\n=== Chain of Responsibility Pattern Demo ===\n" << std::endl;

    // Create handlers
    auto console_logger = std::make_shared<ConsoleLogger>(1);
    auto file_logger = std::make_shared<FileLogger>(2);
    auto error_logger = std::make_shared<ErrorLogger>(3);

    // Build the chain: Console -> File -> Error
    console_logger->setNext(file_logger);
    file_logger->setNext(error_logger);

    // Test different types of requests
    std::cout << "Testing CONSOLE request:" << std::endl;
    console_logger->handle("CONSOLE: This is a console message");

    std::cout << "\nTesting FILE request:" << std::endl;
    console_logger->handle("FILE: This should be logged to file");

    std::cout << "\nTesting ERROR request:" << std::endl;
    console_logger->handle("ERROR: This is an error message");

    std::cout << "\nTesting UNKNOWN request:" << std::endl;
    console_logger->handle("UNKNOWN: This request has no handler");

    std::cout << "\n=== End Chain of Responsibility Demo ===\n" << std::endl;
} 