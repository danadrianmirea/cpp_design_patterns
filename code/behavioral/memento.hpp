#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Memento class - stores the state
class Memento {
    std::string state_;
public:
    explicit Memento(const std::string& state) : state_(state) {}
    std::string getState() const { return state_; }
};

// Originator class - creates and uses mementos
class TextEditor {
    std::string content_;
public:
    void setContent(const std::string& content) {
        content_ = content;
    }
    
    std::string getContent() const {
        return content_;
    }
    
    // Creates a memento
    std::shared_ptr<Memento> createMemento() {
        return std::make_shared<Memento>(content_);
    }
    
    // Restores state from memento
    void restoreFromMemento(const std::shared_ptr<Memento>& memento) {
        content_ = memento->getState();
    }
    
    void showContent() const {
        std::cout << "Current content: " << content_ << std::endl;
    }
};

// Caretaker class - manages mementos
class Caretaker {
    std::vector<std::shared_ptr<Memento>> mementos_;
public:
    void addMemento(const std::shared_ptr<Memento>& memento) {
        mementos_.push_back(memento);
    }
    
    std::shared_ptr<Memento> getMemento(int index) {
        if (index >= 0 && index < static_cast<int>(mementos_.size())) {
            return mementos_[index];
        }
        return nullptr;
    }
    
    int getMementoCount() const {
        return static_cast<int>(mementos_.size());
    }
};

void demonstrateMementoPattern();

#endif // MEMENTO_HPP 