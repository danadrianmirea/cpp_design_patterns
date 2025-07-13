#include "facade.hpp"
#include <iostream>

void demonstrateFacadePattern() {
    std::cout << "\n=== Facade Pattern Demo ===\n" << std::endl;

    // Create the facade
    HomeTheaterFacade home_theater;
    
    std::cout << "--- Initial Status ---" << std::endl;
    home_theater.showStatus();
    
    // Demonstrate movie watching
    std::cout << "\n--- Movie Watching Demo ---" << std::endl;
    home_theater.watchMovie("BluRay Player");
    home_theater.showStatus();
    
    // Demonstrate pause functionality
    std::cout << "\n--- Pause Demo ---" << std::endl;
    home_theater.pauseEntertainment();
    home_theater.showStatus();
    
    // Demonstrate resume functionality
    std::cout << "\n--- Resume Demo ---" << std::endl;
    home_theater.resumeEntertainment();
    home_theater.showStatus();
    
    // Demonstrate 3D movie watching
    std::cout << "\n--- 3D Movie Demo ---" << std::endl;
    home_theater.watch3DMovie("3D BluRay Player");
    home_theater.showStatus();
    
    // Demonstrate music listening
    std::cout << "\n--- Music Listening Demo ---" << std::endl;
    home_theater.listenToMusic("Spotify");
    home_theater.showStatus();
    
    // Demonstrate ending entertainment
    std::cout << "\n--- End Entertainment Demo ---" << std::endl;
    home_theater.endEntertainment();
    home_theater.showStatus();
    
    // Demonstrate complex scenario
    std::cout << "\n--- Complex Scenario Demo ---" << std::endl;
    
    // Start with music
    home_theater.listenToMusic("Apple Music");
    home_theater.showStatus();
    
    // Switch to movie
    home_theater.watchMovie("Netflix");
    home_theater.showStatus();
    
    // Pause for a break
    home_theater.pauseEntertainment();
    home_theater.showStatus();
    
    // Resume movie
    home_theater.resumeEntertainment();
    home_theater.showStatus();
    
    // Switch to 3D movie
    home_theater.watch3DMovie("3D Netflix");
    home_theater.showStatus();
    
    // End everything
    home_theater.endEntertainment();
    home_theater.showStatus();
    
    // Demonstrate Facade Pattern Benefits
    std::cout << "\n--- Facade Pattern Benefits ---" << std::endl;
    std::cout << "1. Simplified Interface: Complex subsystem operations are hidden" << std::endl;
    std::cout << "2. Decoupling: Client code doesn't depend on subsystem details" << std::endl;
    std::cout << "3. Single Responsibility: Facade manages subsystem coordination" << std::endl;
    std::cout << "4. Easy to Use: Simple methods like watchMovie() instead of complex setup" << std::endl;
    std::cout << "5. Maintainable: Changes to subsystems don't affect client code" << std::endl;
    
    // Demonstrate without facade (complex way)
    std::cout << "\n--- Without Facade (Complex Way) ---" << std::endl;
    
    // Create subsystems directly
    auto audio = std::make_shared<AudioSystem>();
    auto video = std::make_shared<VideoSystem>();
    auto lighting = std::make_shared<LightingSystem>();
    auto projector = std::make_shared<ProjectorSystem>();
    auto popcorn = std::make_shared<PopcornMachine>();
    
    // Manual setup for movie watching
    std::cout << "Manual movie setup:" << std::endl;
    audio->turnOn();
    audio->setVolume(80);
    audio->setSource("BluRay Player");
    
    video->turnOn();
    video->setInputSource("BluRay Player");
    video->setBrightness(70);
    video->setContrast(60);
    
    projector->turnOn();
    projector->setInputSource("BluRay Player");
    projector->enable3DMode(false);
    
    lighting->turnOn();
    lighting->setBrightness(20);
    lighting->setMode("Dim");
    
    popcorn->turnOn();
    popcorn->startPopping();
    
    std::cout << "Manual setup complete!" << std::endl;
    
    // Compare with facade approach
    std::cout << "\n--- With Facade (Simple Way) ---" << std::endl;
    home_theater.watchMovie("BluRay Player");
    
    std::cout << "\n--- Comparison ---" << std::endl;
    std::cout << "Without Facade: 15+ lines of complex setup code" << std::endl;
    std::cout << "With Facade: 1 simple method call" << std::endl;
    std::cout << "Result: Same functionality, much simpler interface!" << std::endl;
    
    // Performance demonstration
    std::cout << "\n--- Performance Demo ---" << std::endl;
    
    // Test multiple rapid mode changes
    for (int i = 0; i < 3; ++i) {
        std::cout << "\n--- Cycle " << (i + 1) << " ---" << std::endl;
        home_theater.watchMovie("Movie " + std::to_string(i + 1));
        home_theater.pauseEntertainment();
        home_theater.resumeEntertainment();
        home_theater.listenToMusic("Music " + std::to_string(i + 1));
        home_theater.endEntertainment();
    }
    
    std::cout << "\n=== End Facade Pattern Demo ===\n" << std::endl;
} 