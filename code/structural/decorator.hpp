#ifndef DECORATOR_HPP
#define DECORATOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Component Interface
class DecoratorCoffee {
protected:
    std::string description_;
    double cost_;
    
public:
    DecoratorCoffee(const std::string& description = "Unknown Coffee", double cost = 0.0)
        : description_(description), cost_(cost) {}
    
    virtual ~DecoratorCoffee() = default;
    
    virtual std::string getDescription() const {
        return description_;
    }
    
    virtual double getCost() const {
        return cost_;
    }
    
    virtual void display() const {
        std::cout << getDescription() << " - $" << getCost() << std::endl;
    }
};

// Concrete Component: Simple Coffee
class SimpleDecoratorCoffee : public DecoratorCoffee {
public:
    SimpleDecoratorCoffee() : DecoratorCoffee("Simple Coffee", 2.00) {}
};

// Concrete Component: Espresso
class DecoratorEspresso : public DecoratorCoffee {
public:
    DecoratorEspresso() : DecoratorCoffee("Espresso", 3.50) {}
};

// Concrete Component: Cappuccino
class DecoratorCappuccino : public DecoratorCoffee {
public:
    DecoratorCappuccino() : DecoratorCoffee("Cappuccino", 4.00) {}
};

// Decorator Base Class
class CoffeeDecorator : public DecoratorCoffee {
protected:
    std::shared_ptr<DecoratorCoffee> coffee_;
    
public:
    CoffeeDecorator(std::shared_ptr<DecoratorCoffee> coffee, const std::string& description, double cost)
        : DecoratorCoffee(description, cost), coffee_(coffee) {}
    
    std::string getDescription() const override {
        return coffee_->getDescription() + ", " + description_;
    }
    
    double getCost() const override {
        return coffee_->getCost() + cost_;
    }
};

// Concrete Decorator 1: Milk
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::shared_ptr<DecoratorCoffee> coffee)
        : CoffeeDecorator(coffee, "Milk", 0.50) {}
};

// Concrete Decorator 2: Sugar
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::shared_ptr<DecoratorCoffee> coffee)
        : CoffeeDecorator(coffee, "Sugar", 0.25) {}
};

// Concrete Decorator 3: Whipped Cream
class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(std::shared_ptr<DecoratorCoffee> coffee)
        : CoffeeDecorator(coffee, "Whipped Cream", 0.75) {}
};

// Concrete Decorator 4: Caramel
class CaramelDecorator : public CoffeeDecorator {
public:
    CaramelDecorator(std::shared_ptr<DecoratorCoffee> coffee)
        : CoffeeDecorator(coffee, "Caramel", 0.60) {}
};

// Concrete Decorator 5: Vanilla
class VanillaDecorator : public CoffeeDecorator {
public:
    VanillaDecorator(std::shared_ptr<DecoratorCoffee> coffee)
        : CoffeeDecorator(coffee, "Vanilla", 0.40) {}
};

// Concrete Decorator 6: Chocolate
class ChocolateDecorator : public CoffeeDecorator {
public:
    ChocolateDecorator(std::shared_ptr<DecoratorCoffee> coffee)
        : CoffeeDecorator(coffee, "Chocolate", 0.80) {}
};

// Concrete Decorator 7: Cinnamon
class CinnamonDecorator : public CoffeeDecorator {
public:
    CinnamonDecorator(std::shared_ptr<DecoratorCoffee> coffee)
        : CoffeeDecorator(coffee, "Cinnamon", 0.30) {}
};

// Concrete Decorator 8: Hazelnut
class HazelnutDecorator : public CoffeeDecorator {
public:
    HazelnutDecorator(std::shared_ptr<DecoratorCoffee> coffee)
        : CoffeeDecorator(coffee, "Hazelnut", 0.70) {}
};

// Coffee Shop Menu Builder
class CoffeeShop {
private:
    std::vector<std::shared_ptr<DecoratorCoffee>> menu_;
    
public:
    void addToMenu(std::shared_ptr<DecoratorCoffee> coffee) {
        menu_.push_back(coffee);
    }
    
    void displayMenu() const {
        std::cout << "\n=== Coffee Shop Menu ===" << std::endl;
        for (size_t i = 0; i < menu_.size(); ++i) {
            std::cout << i + 1 << ". ";
            menu_[i]->display();
        }
    }
    
    std::shared_ptr<DecoratorCoffee> getCoffee(int index) const {
        if (index >= 0 && index < static_cast<int>(menu_.size())) {
            return menu_[index];
        }
        return nullptr;
    }
    
    size_t getMenuSize() const {
        return menu_.size();
    }
};

// Coffee Builder for Complex Combinations
class CoffeeBuilder {
private:
    std::shared_ptr<DecoratorCoffee> current_coffee_;
    
public:
    CoffeeBuilder(std::shared_ptr<DecoratorCoffee> base_coffee) : current_coffee_(base_coffee) {}
    
    CoffeeBuilder& addMilk() {
        current_coffee_ = std::make_shared<MilkDecorator>(current_coffee_);
        return *this;
    }
    
    CoffeeBuilder& addSugar() {
        current_coffee_ = std::make_shared<SugarDecorator>(current_coffee_);
        return *this;
    }
    
    CoffeeBuilder& addWhippedCream() {
        current_coffee_ = std::make_shared<WhippedCreamDecorator>(current_coffee_);
        return *this;
    }
    
    CoffeeBuilder& addCaramel() {
        current_coffee_ = std::make_shared<CaramelDecorator>(current_coffee_);
        return *this;
    }
    
    CoffeeBuilder& addVanilla() {
        current_coffee_ = std::make_shared<VanillaDecorator>(current_coffee_);
        return *this;
    }
    
    CoffeeBuilder& addChocolate() {
        current_coffee_ = std::make_shared<ChocolateDecorator>(current_coffee_);
        return *this;
    }
    
    CoffeeBuilder& addCinnamon() {
        current_coffee_ = std::make_shared<CinnamonDecorator>(current_coffee_);
        return *this;
    }
    
    CoffeeBuilder& addHazelnut() {
        current_coffee_ = std::make_shared<HazelnutDecorator>(current_coffee_);
        return *this;
    }
    
    std::shared_ptr<DecoratorCoffee> build() {
        return current_coffee_;
    }
};

// Order Management System
class OrderManager {
private:
    std::vector<std::shared_ptr<DecoratorCoffee>> orders_;
    double total_revenue_;
    
public:
    OrderManager() : total_revenue_(0.0) {}
    
    void placeOrder(std::shared_ptr<DecoratorCoffee> coffee) {
        orders_.push_back(coffee);
        total_revenue_ += coffee->getCost();
        std::cout << "Order placed: ";
        coffee->display();
    }
    
    void displayOrders() const {
        std::cout << "\n=== Current Orders ===" << std::endl;
        for (size_t i = 0; i < orders_.size(); ++i) {
            std::cout << "Order " << i + 1 << ": ";
            orders_[i]->display();
        }
        std::cout << "Total Revenue: $" << total_revenue_ << std::endl;
    }
    
    void clearOrders() {
        orders_.clear();
        total_revenue_ = 0.0;
        std::cout << "All orders cleared." << std::endl;
    }
    
    double getTotalRevenue() const {
        return total_revenue_;
    }
    
    size_t getOrderCount() const {
        return orders_.size();
    }
};

void demonstrateDecoratorPattern();

#endif // DECORATOR_HPP 