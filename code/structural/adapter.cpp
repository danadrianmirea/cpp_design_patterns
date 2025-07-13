#include "adapter.hpp"
#include <iostream>

void demonstrateAdapterPattern() {
    std::cout << "\n=== Adapter Pattern Demo ===\n" << std::endl;

    // Create the legacy payment system
    auto legacy_system = std::make_shared<LegacyPaymentSystem>();
    
    // Create the adapter to make legacy system compatible
    auto legacy_adapter = std::make_shared<LegacyPaymentAdapter>(legacy_system);
    
    // Create modern payment systems
    auto credit_card_system = std::make_shared<ModernPaymentSystem>("Credit Card");
    auto paypal_system = std::make_shared<ModernPaymentSystem>("PayPal");
    
    // Create e-commerce system
    EcommerceSystem ecommerce(legacy_adapter);
    
    std::cout << "--- Testing Legacy System via Adapter ---" << std::endl;
    ecommerce.checkout(99.99, "USD");
    
    std::cout << "\n--- Switching to Modern Credit Card System ---" << std::endl;
    ecommerce.changePaymentProcessor(credit_card_system);
    ecommerce.checkout(149.99, "EUR");
    
    std::cout << "\n--- Switching to PayPal System ---" << std::endl;
    ecommerce.changePaymentProcessor(paypal_system);
    ecommerce.checkout(29.99, "GBP");
    
    std::cout << "\n--- Switching back to Legacy System via Adapter ---" << std::endl;
    ecommerce.changePaymentProcessor(legacy_adapter);
    ecommerce.checkout(199.99, "USD");
    
    // Demonstrate the adapter's role
    std::cout << "\n--- Adapter Pattern Benefits ---" << std::endl;
    std::cout << "1. Legacy system interface: authorizePayment(float, string)" << std::endl;
    std::cout << "2. Modern interface: processPayment(double, string)" << std::endl;
    std::cout << "3. Adapter converts between incompatible interfaces" << std::endl;
    std::cout << "4. Client code remains unchanged regardless of payment system" << std::endl;
    
    // Test error handling
    std::cout << "\n--- Error Handling Demo ---" << std::endl;
    auto disconnected_legacy = std::make_shared<LegacyPaymentSystem>();
    auto disconnected_adapter = std::make_shared<LegacyPaymentAdapter>(disconnected_legacy);
    disconnected_legacy->disconnectFromLegacySystem();
    
    EcommerceSystem test_system(disconnected_adapter);
    test_system.checkout(50.00, "USD");
    
    std::cout << "\n=== End Adapter Pattern Demo ===\n" << std::endl;
} 