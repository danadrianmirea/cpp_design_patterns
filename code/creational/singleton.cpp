#include "singleton.hpp"
#include <iostream>
#include <thread>
#include <chrono>

// Initialize static members for DatabaseConnection
std::shared_ptr<DatabaseConnection> DatabaseConnection::instance_ = nullptr;
std::mutex DatabaseConnection::mutex_;

// Initialize static members for ConfigurationManager
std::shared_ptr<ConfigurationManager> ConfigurationManager::instance_ = nullptr;
std::mutex ConfigurationManager::config_mutex_;

void demonstrateSingletonPattern() {
    std::cout << "\n=== Singleton Pattern Demo ===\n" << std::endl;

    // Demonstrate Database Connection Singleton
    std::cout << "--- Database Connection Singleton ---" << std::endl;
    
    // Get the singleton instance
    auto db1 = DatabaseConnection::getInstance();
    auto db2 = DatabaseConnection::getInstance();
    
    // Verify they are the same instance
    std::cout << "db1 and db2 are the same instance: " 
              << (db1 == db2 ? "Yes" : "No") << std::endl;
    
    // Connect to database
    db1->connect("postgresql://localhost:5432/mydb");
    
    // Try to connect again (should show already connected)
    db2->connect("mysql://localhost:3306/otherdb");
    
    // Execute some operations
    db1->executeQuery("SELECT * FROM users");
    db1->executeTransaction("BEGIN; INSERT INTO logs VALUES (1, 'test'); COMMIT;");
    
    // Demonstrate Configuration Manager Singleton
    std::cout << "\n--- Configuration Manager Singleton ---" << std::endl;
    
    auto config1 = ConfigurationManager::getInstance();
    auto config2 = ConfigurationManager::getInstance();
    
    std::cout << "config1 and config2 are the same instance: " 
              << (config1 == config2 ? "Yes" : "No") << std::endl;
    
    config1->loadConfiguration("app.config");
    config2->saveConfiguration();
    
    // Demonstrate thread safety (simulated)
    std::cout << "\n--- Thread Safety Demo ---" << std::endl;
    
    auto thread1 = std::thread([]() {
        auto db = DatabaseConnection::getInstance();
        db->connect("thread1://localhost/db");
        std::cout << "Thread 1: Connected to " << db->getConnectionString() << std::endl;
    });
    
    auto thread2 = std::thread([]() {
        auto db = DatabaseConnection::getInstance();
        db->connect("thread2://localhost/db");
        std::cout << "Thread 2: Connected to " << db->getConnectionString() << std::endl;
    });
    
    thread1.join();
    thread2.join();
    
    // Show final state
    std::cout << "\n--- Final State ---" << std::endl;
    auto finalDb = DatabaseConnection::getInstance();
    std::cout << "Final connection string: " << finalDb->getConnectionString() << std::endl;
    std::cout << "Is connected: " << (finalDb->isConnected() ? "Yes" : "No") << std::endl;
    
    auto finalConfig = ConfigurationManager::getInstance();
    std::cout << "Final config file: " << finalConfig->getConfigFile() << std::endl;
    std::cout << "Is loaded: " << (finalConfig->isLoaded() ? "Yes" : "No") << std::endl;

    std::cout << "\n=== End Singleton Pattern Demo ===\n" << std::endl;
} 