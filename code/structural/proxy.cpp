#include "proxy.hpp"
#include <iostream>

// Initialize static member
std::unordered_map<std::string, std::shared_ptr<HighResolutionImage>> CachedImage::image_cache_;

void demonstrateProxyPattern() {
    std::cout << "\n=== Proxy Pattern Demo ===\n" << std::endl;

    // Demonstrate Virtual Proxy (Lazy Loading)
    std::cout << "--- Virtual Proxy Demo (Lazy Loading) ---" << std::endl;
    
    // Create proxy images (not loaded yet)
    auto proxy_image1 = std::make_shared<ImageProxy>("vacation_photo.jpg", 75);
    auto proxy_image2 = std::make_shared<ImageProxy>("family_picture.jpg", 45);
    auto proxy_image3 = std::make_shared<ImageProxy>("landscape.jpg", 120);
    
    std::cout << "Created proxy images (not loaded yet):" << std::endl;
    std::cout << "1. " << proxy_image1->getFilename() << " (" << proxy_image1->getSize() << "MB)" << std::endl;
    std::cout << "2. " << proxy_image2->getFilename() << " (" << proxy_image2->getSize() << "MB)" << std::endl;
    std::cout << "3. " << proxy_image3->getFilename() << " (" << proxy_image3->getSize() << "MB)" << std::endl;
    
    // Display images (will trigger loading)
    std::cout << "\n--- Displaying Images (Triggers Loading) ---" << std::endl;
    proxy_image1->display();
    proxy_image2->display();
    proxy_image3->display();
    
    // Demonstrate Protection Proxy
    std::cout << "\n--- Protection Proxy Demo (Access Control) ---" << std::endl;
    
    std::vector<std::string> admin_roles = {"admin", "superuser"};
    std::vector<std::string> user_roles = {"user", "admin", "superuser"};
    std::vector<std::string> guest_roles = {"guest", "user", "admin", "superuser"};
    
    auto protected_admin_image = std::make_shared<ProtectedImage>("admin_dashboard.png", "admin", admin_roles);
    auto protected_user_image = std::make_shared<ProtectedImage>("user_profile.jpg", "user", user_roles);
    auto protected_guest_image = std::make_shared<ProtectedImage>("public_info.jpg", "guest", guest_roles);
    
    // Test different user roles
    std::cout << "\n--- Testing Admin Access ---" << std::endl;
    protected_admin_image->display();
    protected_user_image->display();
    protected_guest_image->display();
    
    std::cout << "\n--- Testing User Access ---" << std::endl;
    protected_admin_image->setUserRole("user");
    protected_user_image->setUserRole("user");
    protected_guest_image->setUserRole("user");
    
    protected_admin_image->display();
    protected_user_image->display();
    protected_guest_image->display();
    
    std::cout << "\n--- Testing Guest Access ---" << std::endl;
    protected_admin_image->setUserRole("guest");
    protected_user_image->setUserRole("guest");
    protected_guest_image->setUserRole("guest");
    
    protected_admin_image->display();
    protected_user_image->display();
    protected_guest_image->display();
    
    // Demonstrate Caching Proxy
    std::cout << "\n--- Caching Proxy Demo ---" << std::endl;
    
    auto cached_image1 = std::make_shared<CachedImage>("frequently_used.jpg", 30);
    auto cached_image2 = std::make_shared<CachedImage>("logo.png", 5);
    auto cached_image3 = std::make_shared<CachedImage>("background.jpg", 25);
    
    // First time loading (from disk)
    std::cout << "\n--- First Time Loading (From Disk) ---" << std::endl;
    cached_image1->display();
    cached_image2->display();
    cached_image3->display();
    
    // Second time loading (from cache)
    std::cout << "\n--- Second Time Loading (From Cache) ---" << std::endl;
    cached_image1->display();
    cached_image2->display();
    cached_image3->display();
    
    // Show cache statistics
    CachedImage::displayCacheStats();
    
    // Demonstrate Image Gallery with different proxy types
    std::cout << "\n--- Image Gallery Demo ---" << std::endl;
    
    ImageGallery gallery;
    
    // Add different types of images
    gallery.addImage(proxy_image1);
    gallery.addImage(protected_admin_image);
    gallery.addImage(cached_image1);
    
    // Show gallery info before loading
    gallery.showGalleryInfo();
    
    // Load all images
    gallery.loadAllImages();
    
    // Show gallery info after loading
    gallery.showGalleryInfo();
    
    // Display all images
    gallery.displayAllImages();
    
    // Demonstrate Proxy Pattern Benefits
    std::cout << "\n--- Proxy Pattern Benefits ---" << std::endl;
    std::cout << "1. Lazy Loading: Resources are loaded only when needed" << std::endl;
    std::cout << "2. Access Control: Protection proxy controls access to resources" << std::endl;
    std::cout << "3. Caching: Caching proxy improves performance" << std::endl;
    std::cout << "4. Remote Access: Can represent remote objects locally" << std::endl;
    std::cout << "5. Memory Management: Virtual proxy manages memory efficiently" << std::endl;
    
    // Demonstrate performance comparison
    std::cout << "\n--- Performance Comparison ---" << std::endl;
    
    // Without Proxy (immediate loading)
    std::cout << "Without Proxy:" << std::endl;
    std::cout << "  - All images loaded immediately" << std::endl;
    std::cout << "  - High memory usage from start" << std::endl;
    std::cout << "  - Slower application startup" << std::endl;
    
    // With Proxy
    std::cout << "\nWith Proxy:" << std::endl;
    std::cout << "  - Images loaded on-demand" << std::endl;
    std::cout << "  - Lower initial memory usage" << std::endl;
    std::cout << "  - Faster application startup" << std::endl;
    std::cout << "  - Access control and caching benefits" << std::endl;
    
    // Demonstrate memory management
    std::cout << "\n--- Memory Management Demo ---" << std::endl;
    
    // Create a proxy and load it
    auto memory_test_proxy = std::make_shared<ImageProxy>("memory_test.jpg", 100);
    std::cout << "Proxy created, real image not loaded yet" << std::endl;
    
    memory_test_proxy->display(); // This loads the image
    std::cout << "Image loaded and displayed" << std::endl;
    
    // Unload the image
    memory_test_proxy->unload();
    std::cout << "Image unloaded from memory" << std::endl;
    
    // Display again (will reload)
    memory_test_proxy->display();
    
    // Demonstrate cache management
    std::cout << "\n--- Cache Management Demo ---" << std::endl;
    
    // Add more images to cache
    auto cache_test1 = std::make_shared<CachedImage>("cache_test1.jpg", 20);
    auto cache_test2 = std::make_shared<CachedImage>("cache_test2.jpg", 15);
    
    cache_test1->display();
    cache_test2->display();
    
    std::cout << "Cache size: " << CachedImage::getCacheSize() << std::endl;
    CachedImage::displayCacheStats();
    
    // Clear cache
    CachedImage::clearCache();
    std::cout << "Cache cleared" << std::endl;
    
    // Demonstrate complex scenario
    std::cout << "\n--- Complex Scenario Demo ---" << std::endl;
    
    ImageGallery complex_gallery;
    
    // Add different types of images
    complex_gallery.addImage(std::make_shared<ImageProxy>("large_photo.jpg", 200));
    complex_gallery.addImage(std::make_shared<ProtectedImage>("sensitive_data.png", "admin", std::vector<std::string>{"admin"}));
    complex_gallery.addImage(std::make_shared<CachedImage>("common_logo.png", 10));
    complex_gallery.addImage(std::make_shared<ImageProxy>("rare_image.jpg", 150));
    
    std::cout << "Complex gallery created with mixed proxy types" << std::endl;
    complex_gallery.showGalleryInfo();
    
    // Simulate user interaction
    std::cout << "\n--- Simulating User Interaction ---" << std::endl;
    
    // User views gallery (triggers some loads)
    complex_gallery.displayAllImages();
    
    // Show final statistics
    complex_gallery.showGalleryInfo();
    CachedImage::displayCacheStats();
    
    std::cout << "\n=== End Proxy Pattern Demo ===\n" << std::endl;
} 