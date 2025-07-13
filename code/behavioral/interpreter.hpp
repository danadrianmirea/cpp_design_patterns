#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <string>
#include <memory>
#include <map>

// Context holds variable values
class Context {
    std::map<std::string, int> variables_;
public:
    void setVariable(const std::string& name, int value) {
        variables_[name] = value;
    }
    int getVariable(const std::string& name) const {
        auto it = variables_.find(name);
        if (it != variables_.end()) return it->second;
        throw std::runtime_error("Variable not found: " + name);
    }
};

// AbstractExpression
class AbstractExpression {
public:
    virtual ~AbstractExpression() = default;
    virtual int interpret(const Context& context) const = 0;
};

// TerminalExpression: Variable or Number
class NumberExpression : public AbstractExpression {
    int number_;
public:
    explicit NumberExpression(int number) : number_(number) {}
    int interpret(const Context&) const override { return number_; }
};

class VariableExpression : public AbstractExpression {
    std::string name_;
public:
    explicit VariableExpression(const std::string& name) : name_(name) {}
    int interpret(const Context& context) const override {
        return context.getVariable(name_);
    }
};

// NonTerminalExpression: Addition and Subtraction
class AddExpression : public AbstractExpression {
    std::shared_ptr<AbstractExpression> left_;
    std::shared_ptr<AbstractExpression> right_;
public:
    AddExpression(std::shared_ptr<AbstractExpression> left, std::shared_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {}
    int interpret(const Context& context) const override {
        return left_->interpret(context) + right_->interpret(context);
    }
};

class SubtractExpression : public AbstractExpression {
    std::shared_ptr<AbstractExpression> left_;
    std::shared_ptr<AbstractExpression> right_;
public:
    SubtractExpression(std::shared_ptr<AbstractExpression> left, std::shared_ptr<AbstractExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {}
    int interpret(const Context& context) const override {
        return left_->interpret(context) - right_->interpret(context);
    }
};

void demonstrateInterpreterPattern();

#endif // INTERPRETER_HPP 