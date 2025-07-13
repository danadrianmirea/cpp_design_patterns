#ifndef PROXY_HPP
#define PROXY_HPP

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map> // Added for CachedImage

// Subject Interface
class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
    virtual void load() = 0;
    virtual std::string getFilename() const = 0;
    virtual bool isLoaded() const = 0;
    virtual int getSize() const = 0;
};

// Real Subject: High Resolution Image
class HighResolutionImage : public Image {
private:
    std::string filename_;
    bool is_loaded_;
    int size_mb_;
    
public:
    HighResolutionImage(const std::string& filename, int size_mb = 50)
        : filename_(filename), is_loaded_(false), size_mb_(size_mb) {}
    
    void load() override {
        if (!is_loaded_) {
            std::cout << "Loading high resolution image: " << filename_ << " (" << size_mb_ << "MB)" << std::endl;
            
            // Simulate loading time
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            
            is_loaded_ = true;
            std::cout << "Image loaded successfully!" << std::endl;
        } else {
            std::cout << "Image already loaded: " << filename_ << std::endl;
        }
    }
    
    void display() override {
        if (!is_loaded_) {
            std::cout << "Cannot display image. Please load it first: " << filename_ << std::endl;
            return;
        }
        
        std::cout << "Displaying high resolution image: " << filename_ << std::endl;
        std::cout << "Image details: " << size_mb_ << "MB, High Quality" << std::endl;
    }
    
    std::string getFilename() const override {
        return filename_;
    }
    
    bool isLoaded() const override {
        return is_loaded_;
    }
    
    int getSize() const override {
        return size_mb_;
    }
};

// Proxy: Virtual Proxy for Lazy Loading
class ImageProxy : public Image {
private:
    std::string filename_;
    int size_mb_;
    std::shared_ptr<HighResolutionImage> real_image_;
    
public:
    ImageProxy(const std::string& filename, int size_mb = 50)
        : filename_(filename), size_mb_(size_mb), real_image_(nullptr) {}
    
    void load() override {
        if (!real_image_) {
            std::cout << "Creating proxy for image: " << filename_ << std::endl;
            real_image_ = std::make_shared<HighResolutionImage>(filename_, size_mb_);
        }
        real_image_->load();
    }
    
    void display() override {
        if (!real_image_) {
            std::cout << "Loading image through proxy: " << filename_ << std::endl;
            load();
        }
        real_image_->display();
    }
    
    std::string getFilename() const override {
        return filename_;
    }
    
    bool isLoaded() const override {
        return real_image_ && real_image_->isLoaded();
    }
    
    int getSize() const override {
        return size_mb_;
    }
    
    // Proxy-specific methods
    bool isProxyCreated() const {
        return real_image_ != nullptr;
    }
    
    void unload() {
        if (real_image_) {
            std::cout << "Unloading image from memory: " << filename_ << std::endl;
            real_image_ = nullptr;
        }
    }
};

// Protection Proxy: Access Control
class ProtectedImage : public Image {
private:
    std::shared_ptr<HighResolutionImage> real_image_;
    std::string user_role_;
    std::vector<std::string> allowed_roles_;
    
public:
    ProtectedImage(const std::string& filename, const std::string& user_role, 
                   const std::vector<std::string>& allowed_roles)
        : real_image_(std::make_shared<HighResolutionImage>(filename)), 
          user_role_(user_role), allowed_roles_(allowed_roles) {}
    
    bool hasAccess() const {
        return std::find(allowed_roles_.begin(), allowed_roles_.end(), user_role_) != allowed_roles_.end();
    }
    
    void load() override {
        if (!hasAccess()) {
            std::cout << "Access denied. User role '" << user_role_ << "' cannot load this image." << std::endl;
            return;
        }
        real_image_->load();
    }
    
    void display() override {
        if (!hasAccess()) {
            std::cout << "Access denied. User role '" << user_role_ << "' cannot display this image." << std::endl;
            return;
        }
        real_image_->display();
    }
    
    std::string getFilename() const override {
        return real_image_->getFilename();
    }
    
    bool isLoaded() const override {
        return real_image_->isLoaded();
    }
    
    int getSize() const override {
        return real_image_->getSize();
    }
    
    void setUserRole(const std::string& role) {
        user_role_ = role;
        std::cout << "User role changed to: " << role << std::endl;
    }
};

// Caching Proxy: Cache Management
class CachedImage : public Image {
private:
    std::shared_ptr<HighResolutionImage> real_image_;
    std::string cache_key_;
    static std::unordered_map<std::string, std::shared_ptr<HighResolutionImage>> image_cache_;
    
public:
    CachedImage(const std::string& filename, int size_mb = 50)
        : real_image_(nullptr), cache_key_(filename) {}
    
    void load() override {
        // Check if image is already in cache
        auto it = image_cache_.find(cache_key_);
        if (it != image_cache_.end()) {
            std::cout << "Loading image from cache: " << cache_key_ << std::endl;
            real_image_ = it->second;
        } else {
            std::cout << "Loading image from disk and caching: " << cache_key_ << std::endl;
            real_image_ = std::make_shared<HighResolutionImage>(cache_key_);
            real_image_->load();
            image_cache_[cache_key_] = real_image_;
        }
    }
    
    void display() override {
        if (!real_image_) {
            load();
        }
        real_image_->display();
    }
    
    std::string getFilename() const override {
        return cache_key_;
    }
    
    bool isLoaded() const override {
        return real_image_ && real_image_->isLoaded();
    }
    
    int getSize() const override {
        return real_image_ ? real_image_->getSize() : 0;
    }
    
    // Cache management methods
    static void clearCache() {
        std::cout << "Clearing image cache..." << std::endl;
        image_cache_.clear();
    }
    
    static size_t getCacheSize() {
        return image_cache_.size();
    }
    
    static void displayCacheStats() {
        std::cout << "Cache contains " << image_cache_.size() << " images" << std::endl;
        for (const auto& pair : image_cache_) {
            std::cout << "  - " << pair.first << std::endl;
        }
    }
};

// Static member declaration (definition in .cpp file)

// Image Gallery (Client)
class ImageGallery {
private:
    std::vector<std::shared_ptr<Image>> images_;
    
public:
    void addImage(std::shared_ptr<Image> image) {
        images_.push_back(image);
        std::cout << "Added image to gallery: " << image->getFilename() << std::endl;
    }
    
    void displayAllImages() {
        std::cout << "\n=== Displaying All Images ===" << std::endl;
        for (const auto& image : images_) {
            std::cout << "\n--- Image: " << image->getFilename() << " ---" << std::endl;
            image->display();
        }
    }
    
    void loadAllImages() {
        std::cout << "\n=== Loading All Images ===" << std::endl;
        for (const auto& image : images_) {
            std::cout << "\n--- Loading: " << image->getFilename() << " ---" << std::endl;
            image->load();
        }
    }
    
    void showGalleryInfo() const {
        std::cout << "\n=== Gallery Information ===" << std::endl;
        std::cout << "Total images: " << images_.size() << std::endl;
        
        int loaded_count = 0;
        int total_size = 0;
        
        for (const auto& image : images_) {
            if (image->isLoaded()) {
                loaded_count++;
                total_size += image->getSize();
            }
        }
        
        std::cout << "Loaded images: " << loaded_count << std::endl;
        std::cout << "Total size: " << total_size << "MB" << std::endl;
    }
    
    size_t getImageCount() const {
        return images_.size();
    }
};

void demonstrateProxyPattern();

#endif // PROXY_HPP 