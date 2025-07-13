#include "bridge.hpp"
#include <iostream>

void demonstrateBridgePattern() {
    std::cout << "\n=== Bridge Pattern Demo ===\n" << std::endl;

    // Create different rendering APIs
    auto opengl_api = std::make_shared<OpenGLDrawingAPI>();
    auto directx_api = std::make_shared<DirectXDrawingAPI>();
    auto vulkan_api = std::make_shared<VulkanDrawingAPI>();

    std::cout << "--- Creating Graphics Editor with OpenGL ---" << std::endl;
    GraphicsEditor editor(opengl_api);

    // Create shapes with OpenGL
    auto circle = std::make_shared<BridgeCircle>(opengl_api, 10.0, 10.0, 5.0);
    auto rectangle = std::make_shared<BridgeRectangle>(opengl_api, 20.0, 20.0, 15.0, 10.0);
    auto triangle = std::make_shared<BridgeTriangle>(opengl_api, 0.0, 0.0, 10.0, 0.0, 5.0, 10.0);

    // Add shapes to editor
    editor.addShape(circle);
    editor.addShape(rectangle);
    editor.addShape(triangle);

    // Draw all shapes with OpenGL
    editor.drawAllShapes();
    editor.listShapes();

    // Switch to DirectX
    std::cout << "\n--- Switching to DirectX Rendering ---" << std::endl;
    editor.switchRenderingAPI(directx_api);
    editor.drawAllShapes();

    // Switch to Vulkan
    std::cout << "\n--- Switching to Vulkan Rendering ---" << std::endl;
    editor.switchRenderingAPI(vulkan_api);
    editor.drawAllShapes();

    // Resize all shapes
    editor.resizeAllShapes(2.0);
    editor.drawAllShapes();

    // Demonstrate individual shape manipulation
    std::cout << "\n--- Individual Shape Manipulation ---" << std::endl;
    
    // Create a new circle with DirectX
    auto new_circle = std::make_shared<BridgeCircle>(directx_api, 50.0, 50.0, 8.0);
    new_circle->draw();
    
    // Switch the same circle to Vulkan
    new_circle->setDrawingAPI(vulkan_api);
    new_circle->draw();
    
    // Resize the circle
    new_circle->resize(1.5);
    new_circle->draw();

    // Demonstrate Bridge Pattern Benefits
    std::cout << "\n--- Bridge Pattern Benefits ---" << std::endl;
    std::cout << "1. Decoupling: Shape abstraction is independent of rendering implementation" << std::endl;
    std::cout << "2. Extensibility: New shapes can be added without changing rendering APIs" << std::endl;
    std::cout << "3. Flexibility: New rendering APIs can be added without changing shapes" << std::endl;
    std::cout << "4. Runtime switching: Can switch rendering APIs at runtime" << std::endl;
    std::cout << "5. Single Responsibility: Each class has one reason to change" << std::endl;

    // Performance comparison demo
    std::cout << "\n--- Performance Comparison Demo ---" << std::endl;
    
    // Create multiple shapes with different APIs
    std::vector<std::shared_ptr<BridgeShape>> performance_shapes;
    
    for (int i = 0; i < 3; ++i) {
        auto shape = std::make_shared<BridgeCircle>(opengl_api, i * 10, i * 10, 3.0);
        performance_shapes.push_back(shape);
    }
    
    for (int i = 0; i < 3; ++i) {
        auto shape = std::make_shared<BridgeRectangle>(directx_api, i * 15, i * 15, 8.0, 6.0);
        performance_shapes.push_back(shape);
    }
    
    for (int i = 0; i < 3; ++i) {
        auto shape = std::make_shared<BridgeTriangle>(vulkan_api, i * 5, i * 5, i * 5 + 5, i * 5, i * 5 + 2.5, i * 5 + 5);
        performance_shapes.push_back(shape);
    }

    std::cout << "Drawing " << performance_shapes.size() << " shapes with mixed APIs:" << std::endl;
    for (auto& shape : performance_shapes) {
        shape->draw();
    }

    // Switch all to same API
    std::cout << "\n--- Switching All Shapes to OpenGL ---" << std::endl;
    for (auto& shape : performance_shapes) {
        shape->setDrawingAPI(opengl_api);
    }
    
    for (auto& shape : performance_shapes) {
        shape->draw();
    }

    std::cout << "\n=== End Bridge Pattern Demo ===\n" << std::endl;
} 