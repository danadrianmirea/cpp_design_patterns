#include "decorator.hpp"
#include <iostream>

void demonstrateDecoratorPattern() {
    std::cout << "\n=== Decorator Pattern Demo ===\n" << std::endl;

    // Create base coffees
    auto simple_coffee = std::make_shared<SimpleDecoratorCoffee>();
    auto espresso = std::make_shared<DecoratorEspresso>();
    auto cappuccino = std::make_shared<DecoratorCappuccino>();

    std::cout << "--- Base Coffees ---" << std::endl;
    simple_coffee->display();
    espresso->display();
    cappuccino->display();

    // Demonstrate simple decoration
    std::cout << "\n--- Simple Decoration ---" << std::endl;
    
    auto coffee_with_milk = std::make_shared<MilkDecorator>(simple_coffee);
    coffee_with_milk->display();
    
    auto coffee_with_sugar = std::make_shared<SugarDecorator>(simple_coffee);
    coffee_with_sugar->display();
    
    auto coffee_with_both = std::make_shared<SugarDecorator>(
        std::make_shared<MilkDecorator>(simple_coffee)
    );
    coffee_with_both->display();

    // Demonstrate complex decoration chains
    std::cout << "\n--- Complex Decoration Chains ---" << std::endl;
    
    // Create a fancy espresso
    auto fancy_espresso = std::make_shared<WhippedCreamDecorator>(
        std::make_shared<CaramelDecorator>(
            std::make_shared<VanillaDecorator>(espresso)
        )
    );
    fancy_espresso->display();
    
    // Create a premium cappuccino
    auto premium_cappuccino = std::make_shared<ChocolateDecorator>(
        std::make_shared<HazelnutDecorator>(
            std::make_shared<CinnamonDecorator>(
                std::make_shared<WhippedCreamDecorator>(cappuccino)
            )
        )
    );
    premium_cappuccino->display();

    // Demonstrate CoffeeBuilder for fluent interface
    std::cout << "\n--- Coffee Builder Demo ---" << std::endl;
    
    auto custom_coffee = CoffeeBuilder(std::make_shared<SimpleDecoratorCoffee>())
        .addMilk()
        .addSugar()
        .addVanilla()
        .addWhippedCream()
        .build();
    custom_coffee->display();
    
    auto luxury_coffee = CoffeeBuilder(std::make_shared<DecoratorEspresso>())
        .addCaramel()
        .addChocolate()
        .addHazelnut()
        .addWhippedCream()
        .addCinnamon()
        .build();
    luxury_coffee->display();

    // Demonstrate Coffee Shop Menu
    std::cout << "\n--- Coffee Shop Menu Demo ---" << std::endl;
    CoffeeShop coffee_shop;
    
    // Add base coffees to menu
    coffee_shop.addToMenu(simple_coffee);
    coffee_shop.addToMenu(espresso);
    coffee_shop.addToMenu(cappuccino);
    
    // Add decorated coffees to menu
    coffee_shop.addToMenu(coffee_with_milk);
    coffee_shop.addToMenu(coffee_with_both);
    coffee_shop.addToMenu(fancy_espresso);
    coffee_shop.addToMenu(premium_cappuccino);
    coffee_shop.addToMenu(custom_coffee);
    coffee_shop.addToMenu(luxury_coffee);
    
    coffee_shop.displayMenu();

    // Demonstrate Order Management
    std::cout << "\n--- Order Management Demo ---" << std::endl;
    OrderManager order_manager;
    
    // Place some orders
    order_manager.placeOrder(coffee_with_milk);
    order_manager.placeOrder(fancy_espresso);
    order_manager.placeOrder(premium_cappuccino);
    order_manager.placeOrder(luxury_coffee);
    
    order_manager.displayOrders();

    // Demonstrate dynamic decoration at runtime
    std::cout << "\n--- Dynamic Decoration Demo ---" << std::endl;
    
    std::shared_ptr<DecoratorCoffee> base_coffee = std::make_shared<SimpleDecoratorCoffee>();
    std::cout << "Starting with: ";
    base_coffee->display();
    
    // Add decorations based on customer preferences
    std::vector<std::string> customer_preferences = {"Milk", "Sugar", "Vanilla"};
    
    for (const auto& preference : customer_preferences) {
        if (preference == "Milk") {
            base_coffee = std::make_shared<MilkDecorator>(base_coffee);
        } else if (preference == "Sugar") {
            base_coffee = std::make_shared<SugarDecorator>(base_coffee);
        } else if (preference == "Vanilla") {
            base_coffee = std::make_shared<VanillaDecorator>(base_coffee);
        }
        std::cout << "After adding " << preference << ": ";
        base_coffee->display();
    }

    // Demonstrate decoration removal (by creating new base)
    std::cout << "\n--- Decoration Removal Demo ---" << std::endl;
    
    auto complex_coffee = CoffeeBuilder(std::make_shared<DecoratorEspresso>())
        .addMilk()
        .addSugar()
        .addCaramel()
        .addWhippedCream()
        .build();
    
    std::cout << "Complex coffee: ";
    complex_coffee->display();
    
    // "Remove" decorations by creating a simpler version
    auto simpler_coffee = CoffeeBuilder(std::make_shared<DecoratorEspresso>())
        .addMilk()
        .addSugar()
        .build();
    
    std::cout << "Simplified coffee: ";
    simpler_coffee->display();

    // Demonstrate cost calculation
    std::cout << "\n--- Cost Calculation Demo ---" << std::endl;
    
    auto cost_demo = CoffeeBuilder(std::make_shared<SimpleDecoratorCoffee>())
        .addMilk()
        .addSugar()
        .addVanilla()
        .addWhippedCream()
        .addCaramel()
        .build();
    
    std::cout << "Cost breakdown:" << std::endl;
    std::cout << "  Base coffee: $2.00" << std::endl;
    std::cout << "  Milk: +$0.50" << std::endl;
    std::cout << "  Sugar: +$0.25" << std::endl;
    std::cout << "  Vanilla: +$0.40" << std::endl;
    std::cout << "  Whipped Cream: +$0.75" << std::endl;
    std::cout << "  Caramel: +$0.60" << std::endl;
    std::cout << "  Total: $" << cost_demo->getCost() << std::endl;

    // Demonstrate Decorator Pattern Benefits
    std::cout << "\n--- Decorator Pattern Benefits ---" << std::endl;
    std::cout << "1. Open/Closed Principle: Open for extension, closed for modification" << std::endl;
    std::cout << "2. Single Responsibility: Each decorator has one responsibility" << std::endl;
    std::cout << "3. Flexibility: Can combine decorators in any order" << std::endl;
    std::cout << "4. Transparency: Decorated objects work like base objects" << std::endl;
    std::cout << "5. Dynamic Behavior: Can add/remove behaviors at runtime" << std::endl;

    // Performance demonstration
    std::cout << "\n--- Performance Demo ---" << std::endl;
    
    // Create many decorated coffees
    std::vector<std::shared_ptr<DecoratorCoffee>> coffee_collection;
    
    for (int i = 0; i < 5; ++i) {
        auto coffee = CoffeeBuilder(std::make_shared<SimpleDecoratorCoffee>())
            .addMilk()
            .addSugar()
            .build();
        coffee_collection.push_back(coffee);
    }
    
    for (int i = 0; i < 3; ++i) {
        auto coffee = CoffeeBuilder(std::make_shared<DecoratorEspresso>())
            .addCaramel()
            .addWhippedCream()
            .build();
        coffee_collection.push_back(coffee);
    }
    
    double total_cost = 0.0;
    for (const auto& coffee : coffee_collection) {
        total_cost += coffee->getCost();
    }
    
    std::cout << "Created " << coffee_collection.size() << " decorated coffees" << std::endl;
    std::cout << "Total cost: $" << total_cost << std::endl;
    std::cout << "Average cost: $" << total_cost / coffee_collection.size() << std::endl;

    std::cout << "\n=== End Decorator Pattern Demo ===\n" << std::endl;
} 