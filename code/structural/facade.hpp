#ifndef FACADE_HPP
#define FACADE_HPP

#include <iostream>
#include <string>
#include <memory>

// Complex Subsystem 1: Audio System
class AudioSystem {
private:
    bool is_on_;
    int volume_;
    std::string source_;
    
public:
    AudioSystem() : is_on_(false), volume_(0), source_("None") {}
    
    void turnOn() {
        is_on_ = true;
        std::cout << "Audio System: Turning on..." << std::endl;
    }
    
    void turnOff() {
        is_on_ = false;
        std::cout << "Audio System: Turning off..." << std::endl;
    }
    
    void setVolume(int volume) {
        if (is_on_) {
            volume_ = volume;
            std::cout << "Audio System: Volume set to " << volume_ << std::endl;
        }
    }
    
    void setSource(const std::string& source) {
        if (is_on_) {
            source_ = source;
            std::cout << "Audio System: Source set to " << source_ << std::endl;
        }
    }
    
    bool isOn() const { return is_on_; }
    int getVolume() const { return volume_; }
    std::string getSource() const { return source_; }
};

// Complex Subsystem 2: Video System
class VideoSystem {
private:
    bool is_on_;
    std::string input_source_;
    int brightness_;
    int contrast_;
    
public:
    VideoSystem() : is_on_(false), input_source_("None"), brightness_(50), contrast_(50) {}
    
    void turnOn() {
        is_on_ = true;
        std::cout << "Video System: Turning on..." << std::endl;
    }
    
    void turnOff() {
        is_on_ = false;
        std::cout << "Video System: Turning off..." << std::endl;
    }
    
    void setInputSource(const std::string& source) {
        if (is_on_) {
            input_source_ = source;
            std::cout << "Video System: Input source set to " << input_source_ << std::endl;
        }
    }
    
    void setBrightness(int brightness) {
        if (is_on_) {
            brightness_ = brightness;
            std::cout << "Video System: Brightness set to " << brightness_ << std::endl;
        }
    }
    
    void setContrast(int contrast) {
        if (is_on_) {
            contrast_ = contrast;
            std::cout << "Video System: Contrast set to " << contrast_ << std::endl;
        }
    }
    
    bool isOn() const { return is_on_; }
    std::string getInputSource() const { return input_source_; }
    int getBrightness() const { return brightness_; }
    int getContrast() const { return contrast_; }
};

// Complex Subsystem 3: Lighting System
class LightingSystem {
private:
    bool is_on_;
    int brightness_;
    std::string mode_;
    
public:
    LightingSystem() : is_on_(false), brightness_(0), mode_("Off") {}
    
    void turnOn() {
        is_on_ = true;
        std::cout << "Lighting System: Turning on..." << std::endl;
    }
    
    void turnOff() {
        is_on_ = false;
        std::cout << "Lighting System: Turning off..." << std::endl;
    }
    
    void setBrightness(int brightness) {
        if (is_on_) {
            brightness_ = brightness;
            std::cout << "Lighting System: Brightness set to " << brightness_ << std::endl;
        }
    }
    
    void setMode(const std::string& mode) {
        if (is_on_) {
            mode_ = mode;
            std::cout << "Lighting System: Mode set to " << mode_ << std::endl;
        }
    }
    
    bool isOn() const { return is_on_; }
    int getBrightness() const { return brightness_; }
    std::string getMode() const { return mode_; }
};

// Complex Subsystem 4: Projector System
class ProjectorSystem {
private:
    bool is_on_;
    std::string input_source_;
    bool is_3d_mode_;
    
public:
    ProjectorSystem() : is_on_(false), input_source_("None"), is_3d_mode_(false) {}
    
    void turnOn() {
        is_on_ = true;
        std::cout << "Projector System: Turning on..." << std::endl;
    }
    
    void turnOff() {
        is_on_ = false;
        std::cout << "Projector System: Turning off..." << std::endl;
    }
    
    void setInputSource(const std::string& source) {
        if (is_on_) {
            input_source_ = source;
            std::cout << "Projector System: Input source set to " << input_source_ << std::endl;
        }
    }
    
    void enable3DMode(bool enable) {
        if (is_on_) {
            is_3d_mode_ = enable;
            std::cout << "Projector System: 3D mode " << (enable ? "enabled" : "disabled") << std::endl;
        }
    }
    
    bool isOn() const { return is_on_; }
    std::string getInputSource() const { return input_source_; }
    bool is3DMode() const { return is_3d_mode_; }
};

// Complex Subsystem 5: Popcorn Machine
class PopcornMachine {
private:
    bool is_on_;
    bool is_popping_;
    int temperature_;
    
public:
    PopcornMachine() : is_on_(false), is_popping_(false), temperature_(0) {}
    
    void turnOn() {
        is_on_ = true;
        std::cout << "Popcorn Machine: Turning on..." << std::endl;
    }
    
    void turnOff() {
        is_on_ = false;
        std::cout << "Popcorn Machine: Turning off..." << std::endl;
    }
    
    void startPopping() {
        if (is_on_) {
            is_popping_ = true;
            temperature_ = 200;
            std::cout << "Popcorn Machine: Starting to pop popcorn..." << std::endl;
        }
    }
    
    void stopPopping() {
        is_popping_ = false;
        temperature_ = 0;
        std::cout << "Popcorn Machine: Stopping popcorn..." << std::endl;
    }
    
    bool isOn() const { return is_on_; }
    bool isPopping() const { return is_popping_; }
    int getTemperature() const { return temperature_; }
};

// Facade: Home Theater Facade
class HomeTheaterFacade {
private:
    std::shared_ptr<AudioSystem> audio_system_;
    std::shared_ptr<VideoSystem> video_system_;
    std::shared_ptr<LightingSystem> lighting_system_;
    std::shared_ptr<ProjectorSystem> projector_system_;
    std::shared_ptr<PopcornMachine> popcorn_machine_;
    
public:
    HomeTheaterFacade() {
        audio_system_ = std::make_shared<AudioSystem>();
        video_system_ = std::make_shared<VideoSystem>();
        lighting_system_ = std::make_shared<LightingSystem>();
        projector_system_ = std::make_shared<ProjectorSystem>();
        popcorn_machine_ = std::make_shared<PopcornMachine>();
    }
    
    // Simplified interface methods
    void watchMovie(const std::string& movie_source) {
        std::cout << "\n=== Starting Movie Mode ===" << std::endl;
        
        // Turn on all systems
        audio_system_->turnOn();
        video_system_->turnOn();
        projector_system_->turnOn();
        popcorn_machine_->turnOn();
        
        // Configure systems for movie watching
        audio_system_->setVolume(80);
        audio_system_->setSource(movie_source);
        
        video_system_->setInputSource(movie_source);
        video_system_->setBrightness(70);
        video_system_->setContrast(60);
        
        projector_system_->setInputSource(movie_source);
        projector_system_->enable3DMode(false);
        
        lighting_system_->turnOn();
        lighting_system_->setBrightness(20);
        lighting_system_->setMode("Dim");
        
        popcorn_machine_->startPopping();
        
        std::cout << "Movie mode is ready! Enjoy your movie." << std::endl;
    }
    
    void watch3DMovie(const std::string& movie_source) {
        std::cout << "\n=== Starting 3D Movie Mode ===" << std::endl;
        
        // Turn on all systems
        audio_system_->turnOn();
        video_system_->turnOn();
        projector_system_->turnOn();
        popcorn_machine_->turnOn();
        
        // Configure systems for 3D movie watching
        audio_system_->setVolume(85);
        audio_system_->setSource(movie_source);
        
        video_system_->setInputSource(movie_source);
        video_system_->setBrightness(80);
        video_system_->setContrast(70);
        
        projector_system_->setInputSource(movie_source);
        projector_system_->enable3DMode(true);
        
        lighting_system_->turnOn();
        lighting_system_->setBrightness(10);
        lighting_system_->setMode("Dark");
        
        popcorn_machine_->startPopping();
        
        std::cout << "3D movie mode is ready! Enjoy your 3D experience." << std::endl;
    }
    
    void listenToMusic(const std::string& music_source) {
        std::cout << "\n=== Starting Music Mode ===" << std::endl;
        
        // Turn on audio system only
        audio_system_->turnOn();
        video_system_->turnOff();
        projector_system_->turnOff();
        lighting_system_->turnOn();
        popcorn_machine_->turnOff();
        
        // Configure for music listening
        audio_system_->setVolume(60);
        audio_system_->setSource(music_source);
        
        lighting_system_->setBrightness(40);
        lighting_system_->setMode("Ambient");
        
        std::cout << "Music mode is ready! Enjoy your music." << std::endl;
    }
    
    void endEntertainment() {
        std::cout << "\n=== Ending Entertainment Session ===" << std::endl;
        
        // Turn off all systems
        audio_system_->turnOff();
        video_system_->turnOff();
        projector_system_->turnOff();
        lighting_system_->turnOff();
        popcorn_machine_->stopPopping();
        popcorn_machine_->turnOff();
        
        std::cout << "All systems turned off. Goodbye!" << std::endl;
    }
    
    void pauseEntertainment() {
        std::cout << "\n=== Pausing Entertainment ===" << std::endl;
        
        // Pause systems
        audio_system_->setVolume(0);
        video_system_->setBrightness(0);
        lighting_system_->setBrightness(60);
        lighting_system_->setMode("Pause");
        
        std::cout << "Entertainment paused. Systems in standby mode." << std::endl;
    }
    
    void resumeEntertainment() {
        std::cout << "\n=== Resuming Entertainment ===" << std::endl;
        
        // Resume systems
        audio_system_->setVolume(80);
        video_system_->setBrightness(70);
        lighting_system_->setBrightness(20);
        lighting_system_->setMode("Dim");
        
        std::cout << "Entertainment resumed." << std::endl;
    }
    
    // Status methods
    void showStatus() const {
        std::cout << "\n=== Home Theater Status ===" << std::endl;
        std::cout << "Audio System: " << (audio_system_->isOn() ? "ON" : "OFF");
        if (audio_system_->isOn()) {
            std::cout << " (Volume: " << audio_system_->getVolume() 
                      << ", Source: " << audio_system_->getSource() << ")";
        }
        std::cout << std::endl;
        
        std::cout << "Video System: " << (video_system_->isOn() ? "ON" : "OFF");
        if (video_system_->isOn()) {
            std::cout << " (Input: " << video_system_->getInputSource() 
                      << ", Brightness: " << video_system_->getBrightness() << ")";
        }
        std::cout << std::endl;
        
        std::cout << "Projector System: " << (projector_system_->isOn() ? "ON" : "OFF");
        if (projector_system_->isOn()) {
            std::cout << " (Input: " << projector_system_->getInputSource() 
                      << ", 3D: " << (projector_system_->is3DMode() ? "ON" : "OFF") << ")";
        }
        std::cout << std::endl;
        
        std::cout << "Lighting System: " << (lighting_system_->isOn() ? "ON" : "OFF");
        if (lighting_system_->isOn()) {
            std::cout << " (Brightness: " << lighting_system_->getBrightness() 
                      << ", Mode: " << lighting_system_->getMode() << ")";
        }
        std::cout << std::endl;
        
        std::cout << "Popcorn Machine: " << (popcorn_machine_->isOn() ? "ON" : "OFF");
        if (popcorn_machine_->isOn()) {
            std::cout << " (Popping: " << (popcorn_machine_->isPopping() ? "YES" : "NO") 
                      << ", Temp: " << popcorn_machine_->getTemperature() << "°C)";
        }
        std::cout << std::endl;
    }
};

void demonstrateFacadePattern();

#endif // FACADE_HPP 