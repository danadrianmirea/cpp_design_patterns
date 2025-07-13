#include "iterator.hpp"
#include <iostream>

void demonstrateIteratorPattern() {
    std::cout << "\n=== Iterator Pattern Demo ===\n" << std::endl;

    // Create a concrete aggregate
    ConcreteAggregate<std::string> aggregate;
    aggregate.addItem("Item 1");
    aggregate.addItem("Item 2");
    aggregate.addItem("Item 3");
    aggregate.addItem("Item 4");

    // Create an iterator
    auto iterator = aggregate.createIterator();

    std::cout << "Iterating through items:" << std::endl;
    for (iterator->first(); !iterator->isDone(); iterator->next()) {
        std::cout << iterator->currentItem() << std::endl;
    }

    std::cout << "\n=== End Iterator Pattern Demo ===\n" << std::endl;
} 