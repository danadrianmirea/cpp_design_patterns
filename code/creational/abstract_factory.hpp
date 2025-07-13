#ifndef ABSTRACT_FACTORY_HPP
#define ABSTRACT_FACTORY_HPP

#include <iostream>
#include <string>
#include <memory>

// Abstract Product: Button
class Button {
public:
    virtual ~Button() = default;
    virtual void render() = 0;
    virtual void onClick() = 0;
};

// Abstract Product: Checkbox
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void render() = 0;
    virtual void onCheck() = 0;
};

// Concrete Products for Windows
class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows button" << std::endl;
    }
    
    void onClick() override {
        std::cout << "Windows button clicked!" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Windows checkbox" << std::endl;
    }
    
    void onCheck() override {
        std::cout << "Windows checkbox checked!" << std::endl;
    }
};

// Concrete Products for Mac
class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Mac button" << std::endl;
    }
    
    void onClick() override {
        std::cout << "Mac button clicked!" << std::endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Mac checkbox" << std::endl;
    }
    
    void onCheck() override {
        std::cout << "Mac checkbox checked!" << std::endl;
    }
};

// Abstract Factory
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::shared_ptr<Button> createButton() = 0;
    virtual std::shared_ptr<Checkbox> createCheckbox() = 0;
};

// Concrete Factory for Windows
class WindowsFactory : public GUIFactory {
public:
    std::shared_ptr<Button> createButton() override {
        return std::make_shared<WindowsButton>();
    }
    
    std::shared_ptr<Checkbox> createCheckbox() override {
        return std::make_shared<WindowsCheckbox>();
    }
};

// Concrete Factory for Mac
class MacFactory : public GUIFactory {
public:
    std::shared_ptr<Button> createButton() override {
        return std::make_shared<MacButton>();
    }
    
    std::shared_ptr<Checkbox> createCheckbox() override {
        return std::make_shared<MacCheckbox>();
    }
};

// Application class that uses the factory
class Application {
    std::shared_ptr<GUIFactory> factory_;
    std::shared_ptr<Button> button_;
    std::shared_ptr<Checkbox> checkbox_;
    
public:
    explicit Application(std::shared_ptr<GUIFactory> factory) : factory_(factory) {
        button_ = factory_->createButton();
        checkbox_ = factory_->createCheckbox();
    }
    
    void render() {
        std::cout << "Rendering application UI..." << std::endl;
        button_->render();
        checkbox_->render();
    }
    
    void simulateUserInteraction() {
        std::cout << "Simulating user interaction..." << std::endl;
        button_->onClick();
        checkbox_->onCheck();
    }
};

void demonstrateAbstractFactoryPattern();

#endif // ABSTRACT_FACTORY_HPP 