#include "strategy.hpp"
#include <iostream>

void demonstrateStrategyPattern() {
    std::cout << "\n=== Strategy Pattern Demo ===\n" << std::endl;

    // Create a shopping cart
    ShoppingCart cart;
    
    // Add some items
    cart.addItem(25.99);
    cart.addItem(15.50);
    cart.addItem(8.75);

    // Test different payment strategies
    std::cout << "\n--- Credit Card Payment ---" << std::endl;
    cart.setPaymentStrategy(std::make_shared<CreditCardPayment>("1234-5678-9012-3456", "John Doe"));
    cart.checkout();

    std::cout << "\n--- PayPal Payment ---" << std::endl;
    cart.setPaymentStrategy(std::make_shared<PayPalPayment>("john.doe@example.com"));
    cart.checkout();

    std::cout << "\n--- Cash Payment ---" << std::endl;
    cart.setPaymentStrategy(std::make_shared<CashPayment>());
    cart.checkout();

    std::cout << "\n=== End Strategy Pattern Demo ===\n" << std::endl;
} 