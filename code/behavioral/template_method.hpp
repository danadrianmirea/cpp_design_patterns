#ifndef TEMPLATE_METHOD_HPP
#define TEMPLATE_METHOD_HPP

#include <iostream>
#include <string>

// Abstract Class with Template Method
class Beverage {
public:
    // Template Method - defines the algorithm skeleton
    void prepareBeverage() {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();
        }
        std::cout << "Beverage is ready!" << std::endl;
    }

    virtual ~Beverage() = default;

protected:
    // Common steps
    void boilWater() {
        std::cout << "Boiling water..." << std::endl;
    }

    void pourInCup() {
        std::cout << "Pouring into cup..." << std::endl;
    }

    // Abstract methods to be implemented by subclasses
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    // Hook method - can be overridden by subclasses
    virtual bool customerWantsCondiments() {
        return true; // Default implementation
    }
};

// Concrete Class: Coffee
class Coffee : public Beverage {
protected:
    void brew() override {
        std::cout << "Dripping coffee through filter..." << std::endl;
    }

    void addCondiments() override {
        std::cout << "Adding sugar and milk..." << std::endl;
    }

    bool customerWantsCondiments() override {
        std::cout << "Would you like milk and sugar with your coffee? (y/n): ";
        char response;
        std::cin >> response;
        return response == 'y' || response == 'Y';
    }
};

// Concrete Class: Tea
class Tea : public Beverage {
protected:
    void brew() override {
        std::cout << "Steeping the tea..." << std::endl;
    }

    void addCondiments() override {
        std::cout << "Adding lemon..." << std::endl;
    }

    bool customerWantsCondiments() override {
        std::cout << "Would you like lemon with your tea? (y/n): ";
        char response;
        std::cin >> response;
        return response == 'y' || response == 'Y';
    }
};

void demonstrateTemplateMethodPattern();

#endif // TEMPLATE_METHOD_HPP 