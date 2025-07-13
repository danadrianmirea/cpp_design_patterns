#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <string>
#include <memory>
#include <mutex>

// Thread-safe Singleton: Database Connection
class DatabaseConnection {
private:
    static std::shared_ptr<DatabaseConnection> instance_;
    static std::mutex mutex_;
    
    std::string connection_string_;
    bool is_connected_;
    
    // Private constructor to prevent direct instantiation
    DatabaseConnection() : is_connected_(false) {
        std::cout << "Database connection instance created" << std::endl;
    }
    
    // Delete copy constructor and assignment operator
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
public:
    // Destructor
    ~DatabaseConnection() {
        if (is_connected_) {
            disconnect();
        }
        std::cout << "Database connection instance destroyed" << std::endl;
    }
    
    // Get singleton instance (thread-safe)
    static std::shared_ptr<DatabaseConnection> getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_ = std::shared_ptr<DatabaseConnection>(new DatabaseConnection());
        }
        return instance_;
    }
    
    // Connection methods
    void connect(const std::string& connection_string) {
        if (!is_connected_) {
            connection_string_ = connection_string;
            is_connected_ = true;
            std::cout << "Connected to database: " << connection_string_ << std::endl;
        } else {
            std::cout << "Already connected to database: " << connection_string_ << std::endl;
        }
    }
    
    void disconnect() {
        if (is_connected_) {
            is_connected_ = false;
            std::cout << "Disconnected from database: " << connection_string_ << std::endl;
        }
    }
    
    bool isConnected() const {
        return is_connected_;
    }
    
    void executeQuery(const std::string& query) {
        if (is_connected_) {
            std::cout << "Executing query: " << query << std::endl;
            std::cout << "Query executed successfully" << std::endl;
        } else {
            std::cout << "Cannot execute query - not connected to database" << std::endl;
        }
    }
    
    void executeTransaction(const std::string& transaction) {
        if (is_connected_) {
            std::cout << "Starting transaction: " << transaction << std::endl;
            std::cout << "Transaction completed successfully" << std::endl;
        } else {
            std::cout << "Cannot execute transaction - not connected to database" << std::endl;
        }
    }
    
    std::string getConnectionString() const {
        return connection_string_;
    }
};

// Alternative Singleton: Configuration Manager
class ConfigurationManager {
private:
    static std::shared_ptr<ConfigurationManager> instance_;
    static std::mutex config_mutex_;
    
    std::string config_file_;
    bool is_loaded_;
    
    ConfigurationManager() : is_loaded_(false) {
        std::cout << "Configuration manager instance created" << std::endl;
    }
    
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;
    
public:
    ~ConfigurationManager() {
        std::cout << "Configuration manager instance destroyed" << std::endl;
    }
    
    static std::shared_ptr<ConfigurationManager> getInstance() {
        std::lock_guard<std::mutex> lock(config_mutex_);
        if (!instance_) {
            instance_ = std::shared_ptr<ConfigurationManager>(new ConfigurationManager());
        }
        return instance_;
    }
    
    void loadConfiguration(const std::string& filename) {
        if (!is_loaded_) {
            config_file_ = filename;
            is_loaded_ = true;
            std::cout << "Configuration loaded from: " << config_file_ << std::endl;
        } else {
            std::cout << "Configuration already loaded from: " << config_file_ << std::endl;
        }
    }
    
    void saveConfiguration() {
        if (is_loaded_) {
            std::cout << "Configuration saved to: " << config_file_ << std::endl;
        } else {
            std::cout << "No configuration loaded to save" << std::endl;
        }
    }
    
    bool isLoaded() const {
        return is_loaded_;
    }
    
    std::string getConfigFile() const {
        return config_file_;
    }
};

void demonstrateSingletonPattern();

#endif // SINGLETON_HPP 