#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include <iostream>
#include <string>
#include <memory>

// Target Interface: Modern Payment System
class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;
    virtual bool processPayment(double amount, const std::string& currency) = 0;
    virtual std::string getPaymentMethod() const = 0;
};

// Adaptee: Legacy Payment System (incompatible interface)
class LegacyPaymentSystem {
private:
    std::string payment_type_;
    bool is_connected_;
    
public:
    LegacyPaymentSystem() : payment_type_("Legacy"), is_connected_(false) {}
    
    // Legacy interface - different method names and parameters
    bool authorizePayment(float payment_amount, std::string payment_currency) {
        if (!is_connected_) {
            std::cout << "Legacy system not connected!" << std::endl;
            return false;
        }
        
        std::cout << "Legacy system: Processing payment of " 
                  << payment_amount << " " << payment_currency << std::endl;
        std::cout << "Legacy system: Payment authorized successfully" << std::endl;
        return true;
    }
    
    bool connectToLegacySystem() {
        is_connected_ = true;
        std::cout << "Legacy payment system connected" << std::endl;
        return true;
    }
    
    void disconnectFromLegacySystem() {
        is_connected_ = false;
        std::cout << "Legacy payment system disconnected" << std::endl;
    }
    
    std::string getLegacyPaymentType() const {
        return payment_type_;
    }
    
    bool isConnected() const {
        return is_connected_;
    }
};

// Adapter: Adapts LegacyPaymentSystem to PaymentProcessor interface
class LegacyPaymentAdapter : public PaymentProcessor {
private:
    std::shared_ptr<LegacyPaymentSystem> legacy_system_;
    
public:
    explicit LegacyPaymentAdapter(std::shared_ptr<LegacyPaymentSystem> legacy_system)
        : legacy_system_(legacy_system) {
        legacy_system_->connectToLegacySystem();
    }
    
    ~LegacyPaymentAdapter() {
        if (legacy_system_) {
            legacy_system_->disconnectFromLegacySystem();
        }
    }
    
    bool processPayment(double amount, const std::string& currency) override {
        // Convert double to float and adapt the interface
        return legacy_system_->authorizePayment(static_cast<float>(amount), currency);
    }
    
    std::string getPaymentMethod() const override {
        return "Legacy System (" + legacy_system_->getLegacyPaymentType() + ")";
    }
};

// Modern Payment System (implements target interface directly)
class ModernPaymentSystem : public PaymentProcessor {
private:
    std::string payment_method_;
    
public:
    explicit ModernPaymentSystem(const std::string& method) : payment_method_(method) {}
    
    bool processPayment(double amount, const std::string& currency) override {
        std::cout << "Modern system: Processing " << payment_method_ 
                  << " payment of " << amount << " " << currency << std::endl;
        std::cout << "Modern system: Payment processed successfully" << std::endl;
        return true;
    }
    
    std::string getPaymentMethod() const override {
        return payment_method_;
    }
};

// Client: E-commerce system that works with any PaymentProcessor
class EcommerceSystem {
private:
    std::shared_ptr<PaymentProcessor> payment_processor_;
    
public:
    explicit EcommerceSystem(std::shared_ptr<PaymentProcessor> processor)
        : payment_processor_(processor) {}
    
    bool checkout(double amount, const std::string& currency) {
        std::cout << "E-commerce system: Starting checkout process..." << std::endl;
        std::cout << "Using payment method: " << payment_processor_->getPaymentMethod() << std::endl;
        
        bool success = payment_processor_->processPayment(amount, currency);
        
        if (success) {
            std::cout << "E-commerce system: Checkout completed successfully!" << std::endl;
        } else {
            std::cout << "E-commerce system: Checkout failed!" << std::endl;
        }
        
        return success;
    }
    
    void changePaymentProcessor(std::shared_ptr<PaymentProcessor> new_processor) {
        payment_processor_ = new_processor;
        std::cout << "E-commerce system: Switched to " 
                  << new_processor->getPaymentMethod() << std::endl;
    }
};

void demonstrateAdapterPattern();

#endif // ADAPTER_HPP 