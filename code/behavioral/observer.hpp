#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Observer;
class WeatherStation;

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float temperature, float humidity, float pressure) = 0;
};

// Subject interface
class Subject {
public:
    virtual ~Subject() = default;
    virtual void registerObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete Subject: Weather Station
class WeatherStation : public Subject {
    std::vector<std::shared_ptr<Observer>> observers_;
    float temperature_;
    float humidity_;
    float pressure_;
public:
    WeatherStation() : temperature_(0.0f), humidity_(0.0f), pressure_(0.0f) {}
    
    void registerObserver(std::shared_ptr<Observer> observer) override {
        observers_.push_back(observer);
    }
    
    void removeObserver(std::shared_ptr<Observer> observer) override {
        observers_.erase(
            std::remove(observers_.begin(), observers_.end(), observer),
            observers_.end()
        );
    }
    
    void notifyObservers() override {
        for (auto& observer : observers_) {
            observer->update(temperature_, humidity_, pressure_);
        }
    }
    
    void setMeasurements(float temperature, float humidity, float pressure) {
        temperature_ = temperature;
        humidity_ = humidity;
        pressure_ = pressure;
        notifyObservers();
    }
};

// Concrete Observer: Current Conditions Display
class CurrentConditionsDisplay : public Observer {
    std::string name_;
public:
    explicit CurrentConditionsDisplay(const std::string& name) : name_(name) {}
    
    void update(float temperature, float humidity, float pressure) override {
        std::cout << name_ << " - Current Conditions:" << std::endl;
        std::cout << "  Temperature: " << temperature << "°C" << std::endl;
        std::cout << "  Humidity: " << humidity << "%" << std::endl;
        std::cout << "  Pressure: " << pressure << " hPa" << std::endl;
        std::cout << std::endl;
    }
};

// Concrete Observer: Statistics Display
class StatisticsDisplay : public Observer {
    std::string name_;
    float min_temp_, max_temp_, avg_temp_;
    int readings_;
public:
    explicit StatisticsDisplay(const std::string& name) 
        : name_(name), min_temp_(0.0f), max_temp_(0.0f), avg_temp_(0.0f), readings_(0) {}
    
    void update(float temperature, float humidity, float pressure) override {
        if (readings_ == 0) {
            min_temp_ = max_temp_ = avg_temp_ = temperature;
        } else {
            min_temp_ = std::min(min_temp_, temperature);
            max_temp_ = std::max(max_temp_, temperature);
            avg_temp_ = (avg_temp_ * readings_ + temperature) / (readings_ + 1);
        }
        readings_++;
        
        std::cout << name_ << " - Statistics:" << std::endl;
        std::cout << "  Min Temperature: " << min_temp_ << "°C" << std::endl;
        std::cout << "  Max Temperature: " << max_temp_ << "°C" << std::endl;
        std::cout << "  Avg Temperature: " << avg_temp_ << "°C" << std::endl;
        std::cout << "  Readings: " << readings_ << std::endl;
        std::cout << std::endl;
    }
};

void demonstrateObserverPattern();

#endif // OBSERVER_HPP 