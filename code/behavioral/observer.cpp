#include "observer.hpp"
#include <iostream>

void demonstrateObserverPattern() {
    std::cout << "\n=== Observer Pattern Demo ===\n" << std::endl;

    // Create the weather station (subject)
    auto weatherStation = std::make_shared<WeatherStation>();

    // Create observers (displays)
    auto currentDisplay = std::make_shared<CurrentConditionsDisplay>("Current Display");
    auto statisticsDisplay = std::make_shared<StatisticsDisplay>("Statistics Display");

    // Register observers with the weather station
    weatherStation->registerObserver(currentDisplay);
    weatherStation->registerObserver(statisticsDisplay);

    // Simulate weather measurements
    std::cout << "Weather Station Updates:" << std::endl;
    std::cout << "=======================" << std::endl;

    weatherStation->setMeasurements(25.5f, 65.0f, 1013.25f);
    weatherStation->setMeasurements(26.2f, 70.0f, 1012.50f);
    weatherStation->setMeasurements(24.8f, 60.0f, 1014.00f);

    std::cout << "=== End Observer Pattern Demo ===\n" << std::endl;
} 