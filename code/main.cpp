#include <iostream>
#include "behavioral/chain_of_responsibility.hpp"
#include "behavioral/command.hpp"
#include "behavioral/interpreter.hpp"

// Forward declarations
void demonstrateChainOfResponsibility();
void demonstrateCommandPattern();
void demonstrateInterpreterPattern();

int main()
{
	std::cout << "Design Patterns in C++ - Gang of Four Implementation" << std::endl;
	std::cout << "=====================================================" << std::endl;

	// Test Chain of Responsibility pattern
	//demonstrateChainOfResponsibility();

	// Test Command pattern
	//demonstrateCommandPattern();

	// Test Interpreter pattern
	demonstrateInterpreterPattern();

	return 0;
}