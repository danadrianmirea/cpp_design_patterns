#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <iostream>
#include <string>
#include <memory>

// Product: ComputerSystem
class ComputerSystem {
private:
    std::string cpu_;
    std::string ram_;
    std::string storage_;
    std::string gpu_;
    bool has_wifi_;
    bool has_bluetooth_;
    
public:
    void setCPU(const std::string& cpu) { cpu_ = cpu; }
    void setRAM(const std::string& ram) { ram_ = ram; }
    void setStorage(const std::string& storage) { storage_ = storage; }
    void setGPU(const std::string& gpu) { gpu_ = gpu; }
    void setWifi(bool wifi) { has_wifi_ = wifi; }
    void setBluetooth(bool bluetooth) { has_bluetooth_ = bluetooth; }
    
    void display() const {
        std::cout << "Computer Configuration:" << std::endl;
        std::cout << "  CPU: " << cpu_ << std::endl;
        std::cout << "  RAM: " << ram_ << std::endl;
        std::cout << "  Storage: " << storage_ << std::endl;
        std::cout << "  GPU: " << gpu_ << std::endl;
        std::cout << "  WiFi: " << (has_wifi_ ? "Yes" : "No") << std::endl;
        std::cout << "  Bluetooth: " << (has_bluetooth_ ? "Yes" : "No") << std::endl;
    }
};

// Abstract Builder
class ComputerBuilder {
protected:
    std::shared_ptr<ComputerSystem> computer_;
    
public:
    ComputerBuilder() : computer_(std::make_shared<ComputerSystem>()) {}
    virtual ~ComputerBuilder() = default;
    
    virtual void buildCPU() = 0;
    virtual void buildRAM() = 0;
    virtual void buildStorage() = 0;
    virtual void buildGPU() = 0;
    virtual void buildWifi() = 0;
    virtual void buildBluetooth() = 0;
    
    std::shared_ptr<ComputerSystem> getResult() {
        return computer_;
    }
    
    void reset() {
        computer_ = std::make_shared<ComputerSystem>();
    }
};

// Concrete Builder: Gaming Computer
class GamingComputerBuilder : public ComputerBuilder {
public:
    void buildCPU() override {
        computer_->setCPU("Intel Core i9-12900K");
    }
    
    void buildRAM() override {
        computer_->setRAM("32GB DDR5-5600");
    }
    
    void buildStorage() override {
        computer_->setStorage("2TB NVMe SSD");
    }
    
    void buildGPU() override {
        computer_->setGPU("NVIDIA RTX 4090");
    }
    
    void buildWifi() override {
        computer_->setWifi(true);
    }
    
    void buildBluetooth() override {
        computer_->setBluetooth(true);
    }
};

// Concrete Builder: Office Computer
class OfficeComputerBuilder : public ComputerBuilder {
public:
    void buildCPU() override {
        computer_->setCPU("Intel Core i5-12400");
    }
    
    void buildRAM() override {
        computer_->setRAM("16GB DDR4-3200");
    }
    
    void buildStorage() override {
        computer_->setStorage("512GB SATA SSD");
    }
    
    void buildGPU() override {
        computer_->setGPU("Integrated Graphics");
    }
    
    void buildWifi() override {
        computer_->setWifi(true);
    }
    
    void buildBluetooth() override {
        computer_->setBluetooth(false);
    }
};

// Director
class ComputerDirector {
    std::shared_ptr<ComputerBuilder> builder_;
    
public:
    void setBuilder(std::shared_ptr<ComputerBuilder> builder) {
        builder_ = builder;
    }
    
    std::shared_ptr<ComputerSystem> construct() {
        if (!builder_) {
            throw std::runtime_error("No builder set!");
        }
        
        builder_->buildCPU();
        builder_->buildRAM();
        builder_->buildStorage();
        builder_->buildGPU();
        builder_->buildWifi();
        builder_->buildBluetooth();
        
        return builder_->getResult();
    }
    
    std::shared_ptr<ComputerSystem> constructMinimal() {
        if (!builder_) {
            throw std::runtime_error("No builder set!");
        }
        
        builder_->buildCPU();
        builder_->buildRAM();
        builder_->buildStorage();
        builder_->buildGPU();
        
        return builder_->getResult();
    }
};

void demonstrateBuilderPattern();

#endif // BUILDER_HPP 