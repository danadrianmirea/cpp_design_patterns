#include "prototype.hpp"
#include <iostream>

void demonstratePrototypePattern() {
    std::cout << "\n=== Prototype Pattern Demo ===\n" << std::endl;

    // Create original shapes
    auto originalCircle = std::make_shared<Circle>("red", 10, 20, 15);
    auto originalRectangle = std::make_shared<Rectangle>("blue", 30, 40, 50, 30);
    auto originalTriangle = std::make_shared<Triangle>("green", 60, 70, 25, 35);

    std::cout << "--- Original Shapes ---" << std::endl;
    originalCircle->draw();
    originalRectangle->draw();
    originalTriangle->draw();

    // Clone shapes
    std::cout << "\n--- Cloned Shapes ---" << std::endl;
    auto clonedCircle = originalCircle->clone();
    auto clonedRectangle = originalRectangle->clone();
    auto clonedTriangle = originalTriangle->clone();

    clonedCircle->draw();
    clonedRectangle->draw();
    clonedTriangle->draw();

    // Modify cloned shapes
    std::cout << "\n--- Modified Cloned Shapes ---" << std::endl;
    clonedCircle->setPosition(100, 200);
    clonedCircle->setColor("yellow");
    std::dynamic_pointer_cast<Circle>(clonedCircle)->setRadius(25);

    clonedRectangle->setPosition(150, 250);
    clonedRectangle->setColor("purple");
    std::dynamic_pointer_cast<Rectangle>(clonedRectangle)->setSize(75, 45);

    clonedTriangle->setPosition(200, 300);
    clonedTriangle->setColor("orange");
    std::dynamic_pointer_cast<Triangle>(clonedTriangle)->setDimensions(35, 50);

    clonedCircle->draw();
    clonedRectangle->draw();
    clonedTriangle->draw();

    // Verify originals are unchanged
    std::cout << "\n--- Original Shapes (Unchanged) ---" << std::endl;
    originalCircle->draw();
    originalRectangle->draw();
    originalTriangle->draw();

    // Prototype Registry demonstration
    std::cout << "\n--- Prototype Registry Demo ---" << std::endl;
    ShapeRegistry registry;
    
    registry.addPrototype("small_red_circle", 
                         std::make_shared<Circle>("red", 0, 0, 10));
    registry.addPrototype("large_blue_rectangle", 
                         std::make_shared<Rectangle>("blue", 0, 0, 100, 60));
    registry.addPrototype("medium_green_triangle", 
                         std::make_shared<Triangle>("green", 0, 0, 30, 40));

    registry.listPrototypes();

    std::cout << "\n--- Creating Shapes from Registry ---" << std::endl;
    auto circle1 = registry.getPrototype("small_red_circle");
    auto circle2 = registry.getPrototype("small_red_circle");
    
    circle1->setPosition(10, 10);
    circle2->setPosition(20, 20);
    
    circle1->draw();
    circle2->draw();

    std::cout << "\n=== End Prototype Pattern Demo ===\n" << std::endl;
} 