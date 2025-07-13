#ifndef CHAIN_OF_RESPONSIBILITY_HPP
#define CHAIN_OF_RESPONSIBILITY_HPP

#include <iostream>
#include <string>
#include <memory>

// Abstract Handler class
class Handler {
protected:
    std::shared_ptr<Handler> next_handler_;

public:
    Handler() : next_handler_(nullptr) {}
    virtual ~Handler() = default;

    // Set the next handler in the chain
    void setNext(std::shared_ptr<Handler> handler) {
        next_handler_ = handler;
    }

    // Template method pattern - defines the algorithm
    void handle(const std::string& request) {
        if (canHandle(request)) {
            processRequest(request);
        } else if (next_handler_) {
            next_handler_->handle(request);
        } else {
            std::cout << "No handler found for request: " << request << std::endl;
        }
    }

protected:
    // Abstract methods to be implemented by concrete handlers
    virtual bool canHandle(const std::string& request) const = 0;
    virtual void processRequest(const std::string& request) = 0;
};

// Concrete Handler: Console Logger
class ConsoleLogger : public Handler {
private:
    int level_;

public:
    ConsoleLogger(int level) : level_(level) {}

protected:
    bool canHandle(const std::string& request) const override {
        return request.find("CONSOLE") != std::string::npos;
    }

    void processRequest(const std::string& request) override {
        std::cout << "Console Logger (Level " << level_ << "): " << request << std::endl;
    }
};

// Concrete Handler: File Logger
class FileLogger : public Handler {
private:
    int level_;

public:
    FileLogger(int level) : level_(level) {}

protected:
    bool canHandle(const std::string& request) const override {
        return request.find("FILE") != std::string::npos;
    }

    void processRequest(const std::string& request) override {
        std::cout << "File Logger (Level " << level_ << "): " << request << std::endl;
    }
};

// Concrete Handler: Error Logger
class ErrorLogger : public Handler {
private:
    int level_;

public:
    ErrorLogger(int level) : level_(level) {}

protected:
    bool canHandle(const std::string& request) const override {
        return request.find("ERROR") != std::string::npos;
    }

    void processRequest(const std::string& request) override {
        std::cout << "Error Logger (Level " << level_ << "): " << request << std::endl;
    }
};

// Demonstration function
void demonstrateChainOfResponsibility();

#endif // CHAIN_OF_RESPONSIBILITY_HPP 