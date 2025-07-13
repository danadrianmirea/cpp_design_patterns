#include <iostream>
#include "behavioral/chain_of_responsibility.hpp"
#include "behavioral/command.hpp"
#include "behavioral/interpreter.hpp"
#include "behavioral/iterator.hpp"
#include "behavioral/mediator.hpp"
#include "behavioral/memento.hpp"
#include "behavioral/observer.hpp"
#include "behavioral/state.hpp"
#include "behavioral/strategy.hpp"
#include "behavioral/template_method.hpp"
#include "behavioral/visitor.hpp"
#include "creational/abstract_factory.hpp"
#include "creational/builder.hpp"
#include "creational/factory_method.hpp"
#include "creational/prototype.hpp"
#include "creational/singleton.hpp"

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
	//demonstrateObserverPattern();
	//demonstrateStatePattern();
	//demonstrateStrategyPattern();
	//demonstrateTemplateMethodPattern();
	//demonstrateVisitorPattern();

	// Test Creational Patterns
	//demonstrateAbstractFactoryPattern();
	//demonstrateBuilderPattern();
	//demonstrateFactoryMethodPattern();
	//demonstratePrototypePattern();
	demonstrateSingletonPattern();

	return 0;
}