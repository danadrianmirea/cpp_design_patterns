#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <iostream>
#include <string>
#include <memory>

// Strategy interface
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void pay(double amount) = 0;
};

// Concrete Strategies
class CreditCardPayment : public PaymentStrategy {
    std::string card_number_;
    std::string name_;
public:
    CreditCardPayment(const std::string& card_number, const std::string& name)
        : card_number_(card_number), name_(name) {}
    
    void pay(double amount) override {
        std::cout << "Paid $" << amount << " using Credit Card" << std::endl;
        std::cout << "Card: " << card_number_ << ", Name: " << name_ << std::endl;
    }
};

class PayPalPayment : public PaymentStrategy {
    std::string email_;
public:
    explicit PayPalPayment(const std::string& email) : email_(email) {}
    
    void pay(double amount) override {
        std::cout << "Paid $" << amount << " using PayPal" << std::endl;
        std::cout << "Email: " << email_ << std::endl;
    }
};

class CashPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        std::cout << "Paid $" << amount << " using Cash" << std::endl;
        std::cout << "Please collect your receipt" << std::endl;
    }
};

// Context: Shopping Cart
class ShoppingCart {
    std::shared_ptr<PaymentStrategy> payment_strategy_;
    double total_amount_;
public:
    ShoppingCart() : total_amount_(0.0) {}
    
    void addItem(double price) {
        total_amount_ += price;
        std::cout << "Added item: $" << price << std::endl;
    }
    
    void setPaymentStrategy(std::shared_ptr<PaymentStrategy> strategy) {
        payment_strategy_ = strategy;
    }
    
    void checkout() {
        if (payment_strategy_) {
            std::cout << "\nTotal amount: $" << total_amount_ << std::endl;
            payment_strategy_->pay(total_amount_);
        } else {
            std::cout << "No payment strategy selected!" << std::endl;
        }
    }
    
    double getTotal() const { return total_amount_; }
};

void demonstrateStrategyPattern();

#endif // STRATEGY_HPP 