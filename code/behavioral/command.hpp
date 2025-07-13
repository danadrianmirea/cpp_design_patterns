#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <memory>
#include <vector>

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Receiver: Light
class Light {
public:
    void on() {
        std::cout << "Light is ON" << std::endl;
    }
    void off() {
        std::cout << "Light is OFF" << std::endl;
    }
};

// ConcreteCommand: Turn Light On
class LightOnCommand : public Command {
    Light& light_;
public:
    explicit LightOnCommand(Light& light) : light_(light) {}
    void execute() override {
        light_.on();
    }
    void undo() override {
        light_.off();
    }
};

// ConcreteCommand: Turn Light Off
class LightOffCommand : public Command {
    Light& light_;
public:
    explicit LightOffCommand(Light& light) : light_(light) {}
    void execute() override {
        light_.off();
    }
    void undo() override {
        light_.on();
    }
};

// Invoker: Remote Control
class RemoteControl {
    std::shared_ptr<Command> on_command_;
    std::shared_ptr<Command> off_command_;
    std::vector<std::shared_ptr<Command>> history_;
public:
    void setOnCommand(std::shared_ptr<Command> cmd) {
        on_command_ = cmd;
    }
    void setOffCommand(std::shared_ptr<Command> cmd) {
        off_command_ = cmd;
    }
    void pressOn() {
        if (on_command_) {
            on_command_->execute();
            history_.push_back(on_command_);
        }
    }
    void pressOff() {
        if (off_command_) {
            off_command_->execute();
            history_.push_back(off_command_);
        }
    }
    void pressUndo() {
        if (!history_.empty()) {
            history_.back()->undo();
            history_.pop_back();
        }
    }
};

// Demo function
template <typename T>
void safe_delete(T*& ptr) {
    delete ptr;
    ptr = nullptr;
}

void demonstrateCommandPattern();

#endif // COMMAND_HPP 