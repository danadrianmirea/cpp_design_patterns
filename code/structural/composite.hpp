#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// Component Interface
class FileSystemComponent {
protected:
    std::string name_;
    std::string path_;
    
public:
    FileSystemComponent(const std::string& name, const std::string& path) 
        : name_(name), path_(path) {}
    
    virtual ~FileSystemComponent() = default;
    
    virtual void display(int depth = 0) const = 0;
    virtual void add(std::shared_ptr<FileSystemComponent> component) = 0;
    virtual void remove(std::shared_ptr<FileSystemComponent> component) = 0;
    virtual std::shared_ptr<FileSystemComponent> getChild(int index) = 0;
    virtual int getSize() const = 0;
    virtual std::string getType() const = 0;
    
    std::string getName() const { return name_; }
    std::string getPath() const { return path_; }
    void setPath(const std::string& path) { path_ = path; }
};

// Leaf: File
class File : public FileSystemComponent {
private:
    std::string extension_;
    size_t size_bytes_;
    
public:
    File(const std::string& name, const std::string& path, const std::string& extension, size_t size_bytes)
        : FileSystemComponent(name, path), extension_(extension), size_bytes_(size_bytes) {}
    
    void display(int depth = 0) const override {
        std::string indent(depth * 2, ' ');
        std::cout << indent << "📄 " << name_ << "." << extension_ 
                  << " (" << size_bytes_ << " bytes)" << std::endl;
    }
    
    void add(std::shared_ptr<FileSystemComponent> component) override {
        std::cout << "Cannot add to a file: " << name_ << std::endl;
    }
    
    void remove(std::shared_ptr<FileSystemComponent> component) override {
        std::cout << "Cannot remove from a file: " << name_ << std::endl;
    }
    
    std::shared_ptr<FileSystemComponent> getChild(int index) override {
        std::cout << "Files don't have children: " << name_ << std::endl;
        return nullptr;
    }
    
    int getSize() const override {
        return 1; // Files count as 1 item
    }
    
    std::string getType() const override {
        return "File";
    }
    
    std::string getExtension() const { return extension_; }
    size_t getSizeBytes() const { return size_bytes_; }
};

// Composite: Directory
class Directory : public FileSystemComponent {
private:
    std::vector<std::shared_ptr<FileSystemComponent>> children_;
    
public:
    Directory(const std::string& name, const std::string& path)
        : FileSystemComponent(name, path) {}
    
    void display(int depth = 0) const override {
        std::string indent(depth * 2, ' ');
        std::cout << indent << "📁 " << name_ << "/ (" << children_.size() << " items)" << std::endl;
        
        for (const auto& child : children_) {
            child->display(depth + 1);
        }
    }
    
    void add(std::shared_ptr<FileSystemComponent> component) override {
        // Update the child's path
        component->setPath(path_ + "/" + component->getName());
        children_.push_back(component);
        std::cout << "Added " << component->getName() << " to " << name_ << std::endl;
    }
    
    void remove(std::shared_ptr<FileSystemComponent> component) override {
        auto it = std::find(children_.begin(), children_.end(), component);
        if (it != children_.end()) {
            children_.erase(it);
            std::cout << "Removed " << component->getName() << " from " << name_ << std::endl;
        } else {
            std::cout << component->getName() << " not found in " << name_ << std::endl;
        }
    }
    
    std::shared_ptr<FileSystemComponent> getChild(int index) override {
        if (index >= 0 && index < static_cast<int>(children_.size())) {
            return children_[index];
        }
        std::cout << "Invalid index: " << index << std::endl;
        return nullptr;
    }
    
    int getSize() const override {
        int total = 1; // Count this directory
        for (const auto& child : children_) {
            total += child->getSize();
        }
        return total;
    }
    
    std::string getType() const override {
        return "Directory";
    }
    
    // Additional directory-specific methods
    void listContents() const {
        std::cout << "\nContents of " << name_ << "/:" << std::endl;
        for (const auto& child : children_) {
            std::cout << "  " << child->getType() << ": " << child->getName() << std::endl;
        }
    }
    
    int getFileCount() const {
        int count = 0;
        for (const auto& child : children_) {
            if (child->getType() == "File") {
                count++;
            } else if (child->getType() == "Directory") {
                // Recursively count files in subdirectories
                if (auto dir = std::dynamic_pointer_cast<Directory>(child)) {
                    count += dir->getFileCount();
                }
            }
        }
        return count;
    }
    
    int getDirectoryCount() const {
        int count = 0;
        for (const auto& child : children_) {
            if (child->getType() == "Directory") {
                count++;
                // Recursively count subdirectories
                if (auto dir = std::dynamic_pointer_cast<Directory>(child)) {
                    count += dir->getDirectoryCount();
                }
            }
        }
        return count;
    }
};

// Client: File System Manager
class FileSystemManager {
private:
    std::shared_ptr<Directory> root_;
    
public:
    FileSystemManager() {
        root_ = std::make_shared<Directory>("root", "/");
    }
    
    void createFileSystem() {
        // Create a sample file system structure
        auto documents = std::make_shared<Directory>("Documents", "/Documents");
        auto pictures = std::make_shared<Directory>("Pictures", "/Pictures");
        auto downloads = std::make_shared<Directory>("Downloads", "/Downloads");
        
        // Add files to Documents
        auto report = std::make_shared<File>("report", "/Documents", "pdf", 2048576);
        auto presentation = std::make_shared<File>("presentation", "/Documents", "pptx", 5120000);
        auto spreadsheet = std::make_shared<File>("budget", "/Documents", "xlsx", 1024000);
        
        documents->add(report);
        documents->add(presentation);
        documents->add(spreadsheet);
        
        // Add files to Pictures
        auto photo1 = std::make_shared<File>("vacation", "/Pictures", "jpg", 3145728);
        auto photo2 = std::make_shared<File>("family", "/Pictures", "png", 2097152);
        
        pictures->add(photo1);
        pictures->add(photo2);
        
        // Create a subdirectory in Pictures
        auto screenshots = std::make_shared<Directory>("Screenshots", "/Pictures/Screenshots");
        auto screenshot1 = std::make_shared<File>("error", "/Pictures/Screenshots", "png", 524288);
        auto screenshot2 = std::make_shared<File>("success", "/Pictures/Screenshots", "png", 786432);
        
        screenshots->add(screenshot1);
        screenshots->add(screenshot2);
        pictures->add(screenshots);
        
        // Add files to Downloads
        auto installer = std::make_shared<File>("setup", "/Downloads", "exe", 15728640);
        auto archive = std::make_shared<File>("backup", "/Downloads", "zip", 5242880);
        
        downloads->add(installer);
        downloads->add(archive);
        
        // Add directories to root
        root_->add(documents);
        root_->add(pictures);
        root_->add(downloads);
    }
    
    void displayFileSystem() {
        std::cout << "\n=== File System Structure ===" << std::endl;
        root_->display();
    }
    
    void showStatistics() {
        std::cout << "\n=== File System Statistics ===" << std::endl;
        std::cout << "Total items: " << root_->getSize() << std::endl;
        std::cout << "Total files: " << root_->getFileCount() << std::endl;
        std::cout << "Total directories: " << root_->getDirectoryCount() << std::endl;
    }
    
    void searchByName(const std::string& name) {
        std::cout << "\n=== Searching for: " << name << " ===" << std::endl;
        searchRecursive(root_, name);
    }
    
private:
    void searchRecursive(std::shared_ptr<FileSystemComponent> component, const std::string& name) {
        if (component->getName().find(name) != std::string::npos) {
            std::cout << "Found: " << component->getType() << " - " 
                      << component->getPath() << std::endl;
        }
        
        if (component->getType() == "Directory") {
            auto dir = std::dynamic_pointer_cast<Directory>(component);
            for (int i = 0; i < dir->getSize() - 1; ++i) {
                auto child = dir->getChild(i);
                if (child) {
                    searchRecursive(child, name);
                }
            }
        }
    }
};

void demonstrateCompositePattern();

#endif // COMPOSITE_HPP 