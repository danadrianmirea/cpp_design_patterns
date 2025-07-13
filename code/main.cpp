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
#include "structural/adapter.hpp"
#include "structural/bridge.hpp"
#include "structural/composite.hpp"
#include "structural/decorator.hpp"
#include "structural/facade.hpp"
#include "structural/flyweight.hpp"
#include "structural/proxy.hpp"

void TestBehavioralPatterns()
{
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
}

void TestCreationalPatterns()
{
	//demonstrateAbstractFactoryPattern();
	//demonstrateBuilderPattern();
	//demonstrateFactoryMethodPattern();
	//demonstratePrototypePattern();
	demonstrateSingletonPattern();
}

void TestStructuralPatterns()
{
	//demonstrateAdapterPattern();
	//demonstrateBridgePattern();
	//demonstrateCompositePattern();
	//demonstrateDecoratorPattern();
	//demonstrateFacadePattern();
	//demonstrateFlyweightPattern();
	//demonstrateProxyPattern();
}

int main()
{
	//TestBehavioralPatterns();
	TestCreationalPatterns();
	//TestStructuralPatterns();
	return 0;
}