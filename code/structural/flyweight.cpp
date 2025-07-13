#include "flyweight.hpp"
#include <iostream>

void demonstrateFlyweightPattern() {
    std::cout << "\n=== Flyweight Pattern Demo ===\n" << std::endl;

    // Create document editor
    DocumentEditor editor;
    
    std::cout << "--- Adding Characters with Different Properties ---" << std::endl;
    
    // Add characters with various properties
    editor.addCharacter('H', 0, 0, "Arial", 12, "Black", false, false);
    editor.addCharacter('e', 1, 0, "Arial", 12, "Black", false, false);
    editor.addCharacter('l', 2, 0, "Arial", 12, "Black", false, false);
    editor.addCharacter('l', 3, 0, "Arial", 12, "Black", false, false);
    editor.addCharacter('o', 4, 0, "Arial", 12, "Black", false, false);
    
    // Add some bold characters
    editor.addCharacter('W', 6, 0, "Arial", 12, "Black", true, false);
    editor.addCharacter('o', 7, 0, "Arial", 12, "Black", true, false);
    editor.addCharacter('r', 8, 0, "Arial", 12, "Black", true, false);
    editor.addCharacter('l', 9, 0, "Arial", 12, "Black", true, false);
    editor.addCharacter('d', 10, 0, "Arial", 12, "Black", true, false);
    
    // Add italic characters
    editor.addCharacter('I', 12, 0, "Arial", 12, "Black", false, true);
    editor.addCharacter('t', 13, 0, "Arial", 12, "Black", false, true);
    editor.addCharacter('a', 14, 0, "Arial", 12, "Black", false, true);
    editor.addCharacter('l', 15, 0, "Arial", 12, "Black", false, true);
    editor.addCharacter('i', 16, 0, "Arial", 12, "Black", false, true);
    editor.addCharacter('c', 17, 0, "Arial", 12, "Black", false, true);
    
    // Add colored characters
    editor.addCharacter('R', 19, 0, "Arial", 12, "Red", false, false);
    editor.addCharacter('e', 20, 0, "Arial", 12, "Red", false, false);
    editor.addCharacter('d', 21, 0, "Arial", 12, "Red", false, false);
    
    // Add larger font characters
    editor.addCharacter('B', 23, 0, "Arial", 18, "Blue", true, false);
    editor.addCharacter('i', 24, 0, "Arial", 18, "Blue", true, false);
    editor.addCharacter('g', 25, 0, "Arial", 18, "Blue", true, false);
    
    // Display the document
    editor.displayDocument();
    
    // Show memory statistics
    editor.displayMemoryStats();
    
    // Show the cache
    editor.displayCache();
    
    // Demonstrate reuse of properties
    std::cout << "\n--- Demonstrating Property Reuse ---" << std::endl;
    
    // Add more characters with the same properties (should reuse)
    for (int i = 0; i < 5; ++i) {
        editor.addCharacter('a' + i, i, 2, "Arial", 12, "Black", false, false);
    }
    
    for (int i = 0; i < 3; ++i) {
        editor.addCharacter('X' + i, i, 3, "Arial", 12, "Black", true, false);
    }
    
    for (int i = 0; i < 4; ++i) {
        editor.addCharacter('y' + i, i, 4, "Arial", 12, "Black", false, true);
    }
    
    // Show updated statistics
    editor.displayMemoryStats();
    editor.displayCache();
    
    // Demonstrate Style Manager
    std::cout << "\n--- Style Manager Demo ---" << std::endl;
    StyleManager style_manager;
    
    // Create different styles
    style_manager.createStyle("Normal", "Arial", 12, "Black", false, false);
    style_manager.createStyle("Bold", "Arial", 12, "Black", true, false);
    style_manager.createStyle("Italic", "Arial", 12, "Black", false, true);
    style_manager.createStyle("BoldItalic", "Arial", 12, "Black", true, true);
    style_manager.createStyle("Large", "Arial", 18, "Black", false, false);
    style_manager.createStyle("RedBold", "Arial", 12, "Red", true, false);
    style_manager.createStyle("BlueItalic", "Arial", 12, "Blue", false, true);
    
    // Display available styles
    style_manager.displayStyles();
    
    // Demonstrate using styles
    std::cout << "\n--- Using Styles ---" << std::endl;
    
    DocumentEditor styled_editor;
    
    // Add text using different styles
    std::string text = "Styled Text Example";
    int x = 0;
    
    for (char c : text) {
        if (c == ' ') {
            x++;
            continue;
        }
        
        // Alternate between styles
        if (x % 3 == 0) {
            auto style = style_manager.getStyle("Normal");
            styled_editor.addCharacter(c, x, 0, 
                style->getProperties()->getFontFamily(),
                style->getProperties()->getFontSize(),
                style->getProperties()->getColor(),
                style->getProperties()->isBold(),
                style->getProperties()->isItalic());
        } else if (x % 3 == 1) {
            auto style = style_manager.getStyle("Bold");
            styled_editor.addCharacter(c, x, 0, 
                style->getProperties()->getFontFamily(),
                style->getProperties()->getFontSize(),
                style->getProperties()->getColor(),
                style->getProperties()->isBold(),
                style->getProperties()->isItalic());
        } else {
            auto style = style_manager.getStyle("Italic");
            styled_editor.addCharacter(c, x, 0, 
                style->getProperties()->getFontFamily(),
                style->getProperties()->getFontSize(),
                style->getProperties()->getColor(),
                style->getProperties()->isBold(),
                style->getProperties()->isItalic());
        }
        x++;
    }
    
    styled_editor.displayDocument();
    styled_editor.displayMemoryStats();
    
    // Demonstrate performance comparison
    std::cout << "\n--- Performance Comparison ---" << std::endl;
    
    // Without Flyweight (hypothetical)
    std::cout << "Without Flyweight:" << std::endl;
    std::cout << "  - Each character would have its own properties object" << std::endl;
    std::cout << "  - Memory usage: " << styled_editor.getCharacterCount() << " property objects" << std::endl;
    std::cout << "  - No sharing, no memory savings" << std::endl;
    
    // With Flyweight
    std::cout << "\nWith Flyweight:" << std::endl;
    std::cout << "  - Shared properties objects" << std::endl;
    std::cout << "  - Memory usage: " << styled_editor.getUniquePropertiesCount() << " property objects" << std::endl;
    std::cout << "  - Memory saved: " << (styled_editor.getCharacterCount() - styled_editor.getUniquePropertiesCount()) << " objects" << std::endl;
    
    // Demonstrate Flyweight Pattern Benefits
    std::cout << "\n--- Flyweight Pattern Benefits ---" << std::endl;
    std::cout << "1. Memory Efficiency: Shared intrinsic state reduces memory usage" << std::endl;
    std::cout << "2. Performance: Fewer object creations and better cache utilization" << std::endl;
    std::cout << "3. Scalability: Works well with large numbers of similar objects" << std::endl;
    std::cout << "4. Separation of Concerns: Intrinsic vs extrinsic state separation" << std::endl;
    std::cout << "5. Factory Pattern Integration: Centralized object creation and caching" << std::endl;
    
    // Demonstrate large-scale usage
    std::cout << "\n--- Large Scale Demo ---" << std::endl;
    
    DocumentEditor large_editor;
    
    // Create a large document with repeated properties
    for (int i = 0; i < 100; ++i) {
        // Use only 3 different property combinations
        int style_index = i % 3;
        
        if (style_index == 0) {
            large_editor.addCharacter('a' + (i % 26), i, 0, "Arial", 12, "Black", false, false);
        } else if (style_index == 1) {
            large_editor.addCharacter('A' + (i % 26), i, 0, "Arial", 12, "Black", true, false);
        } else {
            large_editor.addCharacter('x' + (i % 26), i, 0, "Arial", 12, "Black", false, true);
        }
    }
    
    large_editor.displayMemoryStats();
    large_editor.displayCache();
    
    std::cout << "\n=== End Flyweight Pattern Demo ===\n" << std::endl;
} 