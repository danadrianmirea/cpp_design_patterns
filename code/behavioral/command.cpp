#include "command.hpp"
#include <iostream>

void demonstrateCommandPattern() {
    std::cout << "\n=== Command Pattern Demo ===\n" << std::endl;

    Light livingRoomLight;
    auto lightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    auto lightOff = std::make_shared<LightOffCommand>(livingRoomLight);

    RemoteControl remote;
    remote.setOnCommand(lightOn);
    remote.setOffCommand(lightOff);

    std::cout << "Pressing ON button:" << std::endl;
    remote.pressOn();

    std::cout << "Pressing OFF button:" << std::endl;
    remote.pressOff();

    std::cout << "Pressing UNDO button (should turn light ON):" << std::endl;
    remote.pressUndo();

    std::cout << "Pressing UNDO button (should turn light OFF):" << std::endl;
    remote.pressUndo();

    std::cout << "\n=== End Command Pattern Demo ===\n" << std::endl;
} 