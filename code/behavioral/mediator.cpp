#include "mediator.hpp"
#include <iostream>

void demonstrateMediatorPattern() {
    std::cout << "\n=== Mediator Pattern Demo ===\n" << std::endl;

    // Create a chat room (mediator)
    auto chatRoom = std::make_shared<ChatRoom>();

    // Create users (colleagues)
    auto alice = std::make_shared<User>(chatRoom.get(), "Alice");
    auto bob = std::make_shared<User>(chatRoom.get(), "Bob");
    auto charlie = std::make_shared<User>(chatRoom.get(), "Charlie");

    // Add users to the chat room
    chatRoom->addUser(alice);
    chatRoom->addUser(bob);
    chatRoom->addUser(charlie);

    // Users send messages through the mediator
    std::cout << "Chat Room Activity:" << std::endl;
    alice->send("Hello everyone!");
    bob->send("Hi Alice!");
    charlie->send("Hello from Charlie!");

    std::cout << "\n=== End Mediator Pattern Demo ===\n" << std::endl;
} 