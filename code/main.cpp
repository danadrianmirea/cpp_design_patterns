#include <iostream>
#include "behavioral/chain_of_responsibility.hpp"
#include "behavioral/command.hpp"
#include "behavioral/interpreter.hpp"
#include "behavioral/iterator.hpp"
#include "behavioral/mediator.hpp"
#include "behavioral/memento.hpp"
#include "behavioral/observer.hpp"

int main()
{
	std::cout << "Design Patterns in C++ - Gang of Four Implementation" << std::endl;
	std::cout << "=====================================================" << std::endl;

	// Test Behavioral Patterns
	//demonstrateChainOfResponsibility();
	//demonstrateCommandPattern();
	//demonstrateInterpreterPattern();
	//demonstrateIteratorPattern();
	//demonstrateMediatorPattern();
	//demonstrateMementoPattern();
	demonstrateObserverPattern();

	return 0;
}