#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class CPU;
class GPU;
class Memory;
class HardDrive;

// Visitor interface
class ComputerPartVisitor {
public:
    virtual ~ComputerPartVisitor() = default;
    virtual void visit(CPU* cpu) = 0;
    virtual void visit(GPU* gpu) = 0;
    virtual void visit(Memory* memory) = 0;
    virtual void visit(HardDrive* hardDrive) = 0;
};

// Element interface
class ComputerPart {
public:
    virtual ~ComputerPart() = default;
    virtual void accept(ComputerPartVisitor* visitor) = 0;
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
};

// Concrete Elements
class CPU : public ComputerPart {
    std::string name_;
    double price_;
public:
    CPU(const std::string& name, double price) : name_(name), price_(price) {}
    
    void accept(ComputerPartVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name_; }
    double getPrice() const override { return price_; }
};

class GPU : public ComputerPart {
    std::string name_;
    double price_;
public:
    GPU(const std::string& name, double price) : name_(name), price_(price) {}
    
    void accept(ComputerPartVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name_; }
    double getPrice() const override { return price_; }
};

class Memory : public ComputerPart {
    std::string name_;
    double price_;
public:
    Memory(const std::string& name, double price) : name_(name), price_(price) {}
    
    void accept(ComputerPartVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name_; }
    double getPrice() const override { return price_; }
};

class HardDrive : public ComputerPart {
    std::string name_;
    double price_;
public:
    HardDrive(const std::string& name, double price) : name_(name), price_(price) {}
    
    void accept(ComputerPartVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name_; }
    double getPrice() const override { return price_; }
};

// Concrete Visitors
class PriceVisitor : public ComputerPartVisitor {
    double total_price_;
public:
    PriceVisitor() : total_price_(0.0) {}
    
    void visit(CPU* cpu) override {
        total_price_ += cpu->getPrice();
        std::cout << "CPU: " << cpu->getName() << " - $" << cpu->getPrice() << std::endl;
    }
    
    void visit(GPU* gpu) override {
        total_price_ += gpu->getPrice();
        std::cout << "GPU: " << gpu->getName() << " - $" << gpu->getPrice() << std::endl;
    }
    
    void visit(Memory* memory) override {
        total_price_ += memory->getPrice();
        std::cout << "Memory: " << memory->getName() << " - $" << memory->getPrice() << std::endl;
    }
    
    void visit(HardDrive* hardDrive) override {
        total_price_ += hardDrive->getPrice();
        std::cout << "Hard Drive: " << hardDrive->getName() << " - $" << hardDrive->getPrice() << std::endl;
    }
    
    double getTotalPrice() const { return total_price_; }
};

class DiagnosticVisitor : public ComputerPartVisitor {
public:
    void visit(CPU* cpu) override {
        std::cout << "Diagnosing CPU: " << cpu->getName() << " - Running stress test..." << std::endl;
    }
    
    void visit(GPU* gpu) override {
        std::cout << "Diagnosing GPU: " << gpu->getName() << " - Running graphics test..." << std::endl;
    }
    
    void visit(Memory* memory) override {
        std::cout << "Diagnosing Memory: " << memory->getName() << " - Running memory test..." << std::endl;
    }
    
    void visit(HardDrive* hardDrive) override {
        std::cout << "Diagnosing Hard Drive: " << hardDrive->getName() << " - Running disk check..." << std::endl;
    }
};

// Computer class that contains parts
class Computer {
    std::vector<std::shared_ptr<ComputerPart>> parts_;
public:
    void addPart(std::shared_ptr<ComputerPart> part) {
        parts_.push_back(part);
    }
    
    void accept(ComputerPartVisitor* visitor) {
        for (auto& part : parts_) {
            part->accept(visitor);
        }
    }
};

void demonstrateVisitorPattern();

#endif // VISITOR_HPP 