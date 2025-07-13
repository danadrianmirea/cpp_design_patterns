#include "composite.hpp"
#include <iostream>

void demonstrateCompositePattern() {
    std::cout << "\n=== Composite Pattern Demo ===\n" << std::endl;

    // Create file system manager
    FileSystemManager fs_manager;
    
    // Create the file system structure
    std::cout << "--- Creating File System Structure ---" << std::endl;
    fs_manager.createFileSystem();
    
    // Display the entire file system
    fs_manager.displayFileSystem();
    
    // Show statistics
    fs_manager.showStatistics();
    
    // Demonstrate individual component operations
    std::cout << "\n--- Individual Component Operations ---" << std::endl;
    
    // Create a new directory
    auto projects = std::make_shared<Directory>("Projects", "/Projects");
    
    // Add files to the new directory
    auto source_file = std::make_shared<File>("main", "/Projects", "cpp", 15360);
    auto header_file = std::make_shared<File>("header", "/Projects", "hpp", 8192);
    auto config_file = std::make_shared<File>("config", "/Projects", "json", 2048);
    
    projects->add(source_file);
    projects->add(header_file);
    projects->add(config_file);
    
    std::cout << "Created new directory 'Projects' with files:" << std::endl;
    projects->display();
    
    // Demonstrate remove operation
    std::cout << "\n--- Remove Operation Demo ---" << std::endl;
    projects->remove(config_file);
    std::cout << "After removing config.json:" << std::endl;
    projects->display();
    
    // Demonstrate getChild operation
    std::cout << "\n--- Get Child Operation Demo ---" << std::endl;
    auto first_child = projects->getChild(0);
    if (first_child) {
        std::cout << "First child: " << first_child->getName() << " (" << first_child->getType() << ")" << std::endl;
    }
    
    // Demonstrate nested structure
    std::cout << "\n--- Nested Structure Demo ---" << std::endl;
    auto src_dir = std::make_shared<Directory>("src", "/Projects/src");
    auto include_dir = std::make_shared<Directory>("include", "/Projects/include");
    
    auto utils_file = std::make_shared<File>("utils", "/Projects/src", "cpp", 10240);
    auto helper_file = std::make_shared<File>("helper", "/Projects/include", "hpp", 5120);
    
    src_dir->add(utils_file);
    include_dir->add(helper_file);
    
    projects->add(src_dir);
    projects->add(include_dir);
    
    std::cout << "Complex nested structure:" << std::endl;
    projects->display();
    
    // Demonstrate uniform treatment
    std::cout << "\n--- Uniform Treatment Demo ---" << std::endl;
    std::vector<std::shared_ptr<FileSystemComponent>> components;
    
    // Add both files and directories to the same container
    components.push_back(source_file);
    components.push_back(projects);
    components.push_back(header_file);
    
    std::cout << "Treating files and directories uniformly:" << std::endl;
    for (const auto& component : components) {
        std::cout << "Component: " << component->getName() 
                  << " (Type: " << component->getType() 
                  << ", Size: " << component->getSize() << ")" << std::endl;
    }
    
    // Demonstrate search functionality
    std::cout << "\n--- Search Functionality Demo ---" << std::endl;
    fs_manager.searchByName("report");
    fs_manager.searchByName("Pictures");
    fs_manager.searchByName("png");
    
    // Demonstrate Composite Pattern Benefits
    std::cout << "\n--- Composite Pattern Benefits ---" << std::endl;
    std::cout << "1. Uniform Treatment: Files and directories are treated the same way" << std::endl;
    std::cout << "2. Hierarchical Structure: Natural tree-like organization" << std::endl;
    std::cout << "3. Recursive Operations: Operations work on entire hierarchies" << std::endl;
    std::cout << "4. Extensibility: Easy to add new component types" << std::endl;
    std::cout << "5. Single Interface: One interface for all components" << std::endl;
    
    // Performance demonstration
    std::cout << "\n--- Performance Demo ---" << std::endl;
    
    // Create a large nested structure
    auto large_dir = std::make_shared<Directory>("LargeProject", "/LargeProject");
    
    for (int i = 1; i <= 5; ++i) {
        auto sub_dir = std::make_shared<Directory>("SubDir" + std::to_string(i), "/LargeProject/SubDir" + std::to_string(i));
        
        for (int j = 1; j <= 3; ++j) {
            auto file = std::make_shared<File>("file" + std::to_string(j), "/LargeProject/SubDir" + std::to_string(i), "txt", 1024 * j);
            sub_dir->add(file);
        }
        
        large_dir->add(sub_dir);
    }
    
    std::cout << "Large project structure created with " << large_dir->getSize() << " total items" << std::endl;
    std::cout << "Files: " << large_dir->getFileCount() << ", Directories: " << large_dir->getDirectoryCount() << std::endl;
    
    // Demonstrate recursive operations
    std::cout << "\n--- Recursive Operations Demo ---" << std::endl;
    std::cout << "Displaying large project structure:" << std::endl;
    large_dir->display();
    
    std::cout << "\n=== End Composite Pattern Demo ===\n" << std::endl;
} 