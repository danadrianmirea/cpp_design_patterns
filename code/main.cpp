#include <iostream>
#include "allpatterns.hpp"

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