#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <vector>
#include <memory>

// Forward declaration
template<typename T>
class ConcreteAggregate;

// Iterator interface
template<typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual T first() = 0;
    virtual T next() = 0;
    virtual bool isDone() const = 0;
    virtual T currentItem() const = 0;
};

// Concrete Iterator
template<typename T>
class ConcreteIterator : public Iterator<T> {
    ConcreteAggregate<T>* aggregate_;
    int current_;
public:
    explicit ConcreteIterator(ConcreteAggregate<T>* aggregate) 
        : aggregate_(aggregate), current_(0) {}
    
    T first() override {
        current_ = 0;
        return aggregate_->getItem(current_);
    }
    
    T next() override {
        current_++;
        if (current_ < aggregate_->getCount()) {
            return aggregate_->getItem(current_);
        }
        return T{};
    }
    
    bool isDone() const override {
        return current_ >= aggregate_->getCount();
    }
    
    T currentItem() const override {
        return aggregate_->getItem(current_);
    }
};

// Aggregate interface
template<typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator<T>> createIterator() = 0;
};

// Concrete Aggregate
template<typename T>
class ConcreteAggregate : public Aggregate<T> {
    std::vector<T> items_;
public:
    void addItem(const T& item) {
        items_.push_back(item);
    }
    
    T getItem(int index) const {
        if (index >= 0 && index < static_cast<int>(items_.size())) {
            return items_[index];
        }
        return T{};
    }
    
    int getCount() const {
        return static_cast<int>(items_.size());
    }
    
    std::unique_ptr<Iterator<T>> createIterator() override {
        return std::make_unique<ConcreteIterator<T>>(this);
    }
};

void demonstrateIteratorPattern();

#endif // ITERATOR_HPP 