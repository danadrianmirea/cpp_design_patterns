#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// Abstract Prototype: Shape
class Shape {
protected:
    std::string color_;
    int x_;
    int y_;
    
public:
    Shape(const std::string& color, int x, int y) 
        : color_(color), x_(x), y_(y) {}
    
    virtual ~Shape() = default;
    
    // Clone method
    virtual std::shared_ptr<Shape> clone() const = 0;
    
    virtual void draw() const = 0;
    
    void setPosition(int x, int y) {
        x_ = x;
        y_ = y;
    }
    
    void setColor(const std::string& color) {
        color_ = color;
    }
    
    std::string getColor() const { return color_; }
    int getX() const { return x_; }
    int getY() const { return y_; }
};

// Concrete Prototypes
class Circle : public Shape {
private:
    int radius_;
    
public:
    Circle(const std::string& color, int x, int y, int radius)
        : Shape(color, x, y), radius_(radius) {}
    
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Circle>(*this);
    }
    
    void draw() const override {
        std::cout << "Drawing Circle at (" << x_ << ", " << y_ 
                  << ") with color " << color_ 
                  << " and radius " << radius_ << std::endl;
    }
    
    void setRadius(int radius) {
        radius_ = radius;
    }
    
    int getRadius() const { return radius_; }
};

class Rectangle : public Shape {
private:
    int width_;
    int height_;
    
public:
    Rectangle(const std::string& color, int x, int y, int width, int height)
        : Shape(color, x, y), width_(width), height_(height) {}
    
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Rectangle>(*this);
    }
    
    void draw() const override {
        std::cout << "Drawing Rectangle at (" << x_ << ", " << y_ 
                  << ") with color " << color_ 
                  << " and size " << width_ << "x" << height_ << std::endl;
    }
    
    void setSize(int width, int height) {
        width_ = width;
        height_ = height;
    }
    
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
};

class Triangle : public Shape {
private:
    int base_;
    int height_;
    
public:
    Triangle(const std::string& color, int x, int y, int base, int height)
        : Shape(color, x, y), base_(base), height_(height) {}
    
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Triangle>(*this);
    }
    
    void draw() const override {
        std::cout << "Drawing Triangle at (" << x_ << ", " << y_ 
                  << ") with color " << color_ 
                  << " and base " << base_ << ", height " << height_ << std::endl;
    }
    
    void setDimensions(int base, int height) {
        base_ = base;
        height_ = height;
    }
    
    int getBase() const { return base_; }
    int getHeight() const { return height_; }
};

// Prototype Registry
class ShapeRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<Shape>> prototypes_;
    
public:
    void addPrototype(const std::string& key, std::shared_ptr<Shape> prototype) {
        prototypes_[key] = prototype;
    }
    
    std::shared_ptr<Shape> getPrototype(const std::string& key) {
        auto it = prototypes_.find(key);
        if (it != prototypes_.end()) {
            return it->second->clone();
        }
        return nullptr;
    }
    
    void listPrototypes() const {
        std::cout << "Available prototypes:" << std::endl;
        for (const auto& pair : prototypes_) {
            std::cout << "  - " << pair.first << std::endl;
        }
    }
};

void demonstratePrototypePattern();

#endif // PROTOTYPE_HPP 