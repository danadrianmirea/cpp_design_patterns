#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector> // Added for GraphicsEditor

// Implementation Interface (Bridge)
class DrawingAPI {
public:
    virtual ~DrawingAPI() = default;
    virtual void drawCircle(double x, double y, double radius) = 0;
    virtual void drawRectangle(double x, double y, double width, double height) = 0;
    virtual void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3) = 0;
    virtual std::string getAPI() const = 0;
};

// Concrete Implementation 1: OpenGL
class OpenGLDrawingAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        std::cout << "OpenGL: Drawing circle at (" << x << ", " << y 
                  << ") with radius " << radius << std::endl;
    }
    
    void drawRectangle(double x, double y, double width, double height) override {
        std::cout << "OpenGL: Drawing rectangle at (" << x << ", " << y 
                  << ") with size " << width << "x" << height << std::endl;
    }
    
    void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3) override {
        std::cout << "OpenGL: Drawing triangle with vertices (" 
                  << x1 << ", " << y1 << "), (" << x2 << ", " << y2 
                  << "), (" << x3 << ", " << y3 << ")" << std::endl;
    }
    
    std::string getAPI() const override {
        return "OpenGL";
    }
};

// Concrete Implementation 2: DirectX
class DirectXDrawingAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        std::cout << "DirectX: Drawing circle at (" << x << ", " << y 
                  << ") with radius " << radius << std::endl;
    }
    
    void drawRectangle(double x, double y, double width, double height) override {
        std::cout << "DirectX: Drawing rectangle at (" << x << ", " << y 
                  << ") with size " << width << "x" << height << std::endl;
    }
    
    void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3) override {
        std::cout << "DirectX: Drawing triangle with vertices (" 
                  << x1 << ", " << y1 << "), (" << x2 << ", " << y2 
                  << "), (" << x3 << ", " << y3 << ")" << std::endl;
    }
    
    std::string getAPI() const override {
        return "DirectX";
    }
};

// Concrete Implementation 3: Vulkan
class VulkanDrawingAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        std::cout << "Vulkan: Drawing circle at (" << x << ", " << y 
                  << ") with radius " << radius << std::endl;
    }
    
    void drawRectangle(double x, double y, double width, double height) override {
        std::cout << "Vulkan: Drawing rectangle at (" << x << ", " << y 
                  << ") with size " << width << "x" << height << std::endl;
    }
    
    void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3) override {
        std::cout << "Vulkan: Drawing triangle with vertices (" 
                  << x1 << ", " << y1 << "), (" << x2 << ", " << y2 
                  << "), (" << x3 << ", " << y3 << ")" << std::endl;
    }
    
    std::string getAPI() const override {
        return "Vulkan";
    }
};

// Abstraction Interface
class BridgeShape {
protected:
    std::shared_ptr<DrawingAPI> drawing_api_;
    
public:
    explicit BridgeShape(std::shared_ptr<DrawingAPI> api) : drawing_api_(api) {}
    virtual ~BridgeShape() = default;
    
    virtual void draw() = 0;
    virtual void resize(double factor) = 0;
    virtual std::string getShapeType() const = 0;
    
    void setDrawingAPI(std::shared_ptr<DrawingAPI> api) {
        drawing_api_ = api;
        std::cout << "Switched to " << api->getAPI() << " rendering" << std::endl;
    }
    
    std::string getCurrentAPI() const {
        return drawing_api_->getAPI();
    }
};

// Refined Abstraction 1: Circle
class BridgeCircle : public BridgeShape {
private:
    double x_, y_, radius_;
    
public:
    BridgeCircle(std::shared_ptr<DrawingAPI> api, double x, double y, double radius)
        : BridgeShape(api), x_(x), y_(y), radius_(radius) {}
    
    void draw() override {
        std::cout << "Drawing " << getShapeType() << " using " << getCurrentAPI() << std::endl;
        drawing_api_->drawCircle(x_, y_, radius_);
    }
    
    void resize(double factor) override {
        radius_ *= factor;
        std::cout << "Resized " << getShapeType() << " by factor " << factor 
                  << " (new radius: " << radius_ << ")" << std::endl;
    }
    
    std::string getShapeType() const override {
        return "Circle";
    }
    
    void setPosition(double x, double y) {
        x_ = x;
        y_ = y;
    }
    
    void setRadius(double radius) {
        radius_ = radius;
    }
};

// Refined Abstraction 2: Rectangle
class BridgeRectangle : public BridgeShape {
private:
    double x_, y_, width_, height_;
    
public:
    BridgeRectangle(std::shared_ptr<DrawingAPI> api, double x, double y, double width, double height)
        : BridgeShape(api), x_(x), y_(y), width_(width), height_(height) {}
    
    void draw() override {
        std::cout << "Drawing " << getShapeType() << " using " << getCurrentAPI() << std::endl;
        drawing_api_->drawRectangle(x_, y_, width_, height_);
    }
    
    void resize(double factor) override {
        width_ *= factor;
        height_ *= factor;
        std::cout << "Resized " << getShapeType() << " by factor " << factor 
                  << " (new size: " << width_ << "x" << height_ << ")" << std::endl;
    }
    
    std::string getShapeType() const override {
        return "Rectangle";
    }
    
    void setPosition(double x, double y) {
        x_ = x;
        y_ = y;
    }
    
    void setSize(double width, double height) {
        width_ = width;
        height_ = height;
    }
};

// Refined Abstraction 3: Triangle
class BridgeTriangle : public BridgeShape {
private:
    double x1_, y1_, x2_, y2_, x3_, y3_;
    
public:
    BridgeTriangle(std::shared_ptr<DrawingAPI> api, double x1, double y1, double x2, double y2, double x3, double y3)
        : BridgeShape(api), x1_(x1), y1_(y1), x2_(x2), y2_(y2), x3_(x3), y3_(y3) {}
    
    void draw() override {
        std::cout << "Drawing " << getShapeType() << " using " << getCurrentAPI() << std::endl;
        drawing_api_->drawTriangle(x1_, y1_, x2_, y2_, x3_, y3_);
    }
    
    void resize(double factor) override {
        x1_ *= factor; y1_ *= factor;
        x2_ *= factor; y2_ *= factor;
        x3_ *= factor; y3_ *= factor;
        std::cout << "Resized " << getShapeType() << " by factor " << factor << std::endl;
    }
    
    std::string getShapeType() const override {
        return "Triangle";
    }
    
    void setVertices(double x1, double y1, double x2, double y2, double x3, double y3) {
        x1_ = x1; y1_ = y1;
        x2_ = x2; y2_ = y2;
        x3_ = x3; y3_ = y3;
    }
};

// Client: Graphics Editor
class GraphicsEditor {
private:
    std::vector<std::shared_ptr<BridgeShape>> shapes_;
    std::shared_ptr<DrawingAPI> current_api_;
    
public:
    explicit GraphicsEditor(std::shared_ptr<DrawingAPI> api) : current_api_(api) {}
    
    void addShape(std::shared_ptr<BridgeShape> shape) {
        shapes_.push_back(shape);
        std::cout << "Added " << shape->getShapeType() << " to editor" << std::endl;
    }
    
    void drawAllShapes() {
        std::cout << "\n--- Drawing All Shapes ---" << std::endl;
        for (auto& shape : shapes_) {
            shape->draw();
        }
    }
    
    void resizeAllShapes(double factor) {
        std::cout << "\n--- Resizing All Shapes by Factor " << factor << " ---" << std::endl;
        for (auto& shape : shapes_) {
            shape->resize(factor);
        }
    }
    
    void switchRenderingAPI(std::shared_ptr<DrawingAPI> new_api) {
        current_api_ = new_api;
        std::cout << "\n--- Switching to " << new_api->getAPI() << " ---" << std::endl;
        for (auto& shape : shapes_) {
            shape->setDrawingAPI(new_api);
        }
    }
    
    void listShapes() {
        std::cout << "\n--- Current Shapes in Editor ---" << std::endl;
        for (size_t i = 0; i < shapes_.size(); ++i) {
            std::cout << i + 1 << ". " << shapes_[i]->getShapeType() 
                      << " (using " << shapes_[i]->getCurrentAPI() << ")" << std::endl;
        }
    }
};

void demonstrateBridgePattern();

#endif // BRIDGE_HPP 