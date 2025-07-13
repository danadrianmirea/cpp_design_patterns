#ifndef FLYWEIGHT_HPP
#define FLYWEIGHT_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

// Flyweight: Character Properties (Intrinsic State)
class CharacterProperties {
private:
    std::string font_family_;
    int font_size_;
    std::string color_;
    bool is_bold_;
    bool is_italic_;
    
public:
    CharacterProperties(const std::string& font_family, int font_size, 
                       const std::string& color, bool is_bold, bool is_italic)
        : font_family_(font_family), font_size_(font_size), color_(color), 
          is_bold_(is_bold), is_italic_(is_italic) {}
    
    // Getters for intrinsic state
    std::string getFontFamily() const { return font_family_; }
    int getFontSize() const { return font_size_; }
    std::string getColor() const { return color_; }
    bool isBold() const { return is_bold_; }
    bool isItalic() const { return is_italic_; }
    
    // Method to display properties
    void display() const {
        std::cout << "Font: " << font_family_ << ", Size: " << font_size_ 
                  << ", Color: " << color_ << ", Bold: " << (is_bold_ ? "Yes" : "No")
                  << ", Italic: " << (is_italic_ ? "Yes" : "No") << std::endl;
    }
    
    // Hash function for unordered_map
    std::string getKey() const {
        return font_family_ + "_" + std::to_string(font_size_) + "_" + 
               color_ + "_" + (is_bold_ ? "1" : "0") + "_" + (is_italic_ ? "1" : "0");
    }
};

// Flyweight Factory
class CharacterPropertiesFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<CharacterProperties>> properties_cache_;
    
public:
    std::shared_ptr<CharacterProperties> getCharacterProperties(
        const std::string& font_family, int font_size, 
        const std::string& color, bool is_bold, bool is_italic) {
        
        // Create a temporary object to get the key
        CharacterProperties temp(font_family, font_size, color, is_bold, is_italic);
        std::string key = temp.getKey();
        
        // Check if properties already exist in cache
        auto it = properties_cache_.find(key);
        if (it != properties_cache_.end()) {
            std::cout << "Reusing existing character properties" << std::endl;
            return it->second;
        }
        
        // Create new properties and cache them
        auto new_properties = std::make_shared<CharacterProperties>(
            font_family, font_size, color, is_bold, is_italic);
        properties_cache_[key] = new_properties;
        
        std::cout << "Creating new character properties" << std::endl;
        return new_properties;
    }
    
    size_t getCacheSize() const {
        return properties_cache_.size();
    }
    
    void displayCache() const {
        std::cout << "\n=== Character Properties Cache ===" << std::endl;
        std::cout << "Total cached properties: " << properties_cache_.size() << std::endl;
        for (const auto& pair : properties_cache_) {
            std::cout << "Key: " << pair.first << " -> ";
            pair.second->display();
        }
    }
};

// Concrete Flyweight: Character (Extrinsic State)
class Character {
private:
    char symbol_;
    int position_x_;
    int position_y_;
    std::shared_ptr<CharacterProperties> properties_;
    
public:
    Character(char symbol, int x, int y, std::shared_ptr<CharacterProperties> properties)
        : symbol_(symbol), position_x_(x), position_y_(y), properties_(properties) {}
    
    void display() const {
        std::cout << "Character '" << symbol_ << "' at (" << position_x_ << ", " << position_y_ << ") with ";
        properties_->display();
    }
    
    char getSymbol() const { return symbol_; }
    int getX() const { return position_x_; }
    int getY() const { return position_y_; }
    std::shared_ptr<CharacterProperties> getProperties() const { return properties_; }
    
    void setPosition(int x, int y) {
        position_x_ = x;
        position_y_ = y;
    }
};

// Document Editor (Client)
class DocumentEditor {
private:
    std::vector<std::shared_ptr<Character>> characters_;
    std::shared_ptr<CharacterPropertiesFactory> factory_;
    
public:
    DocumentEditor() : factory_(std::make_shared<CharacterPropertiesFactory>()) {}
    
    void addCharacter(char symbol, int x, int y, 
                     const std::string& font_family, int font_size,
                     const std::string& color, bool is_bold, bool is_italic) {
        
        auto properties = factory_->getCharacterProperties(
            font_family, font_size, color, is_bold, is_italic);
        
        auto character = std::make_shared<Character>(symbol, x, y, properties);
        characters_.push_back(character);
    }
    
    void displayDocument() const {
        std::cout << "\n=== Document Content ===" << std::endl;
        for (const auto& character : characters_) {
            character->display();
        }
    }
    
    void displayMemoryStats() const {
        std::cout << "\n=== Memory Statistics ===" << std::endl;
        std::cout << "Total characters: " << characters_.size() << std::endl;
        std::cout << "Unique character properties: " << factory_->getCacheSize() << std::endl;
        std::cout << "Memory saved: " << (characters_.size() - factory_->getCacheSize()) 
                  << " character property objects" << std::endl;
        
        double savings_percentage = 0.0;
        if (characters_.size() > 0) {
            savings_percentage = ((double)(characters_.size() - factory_->getCacheSize()) / characters_.size()) * 100.0;
        }
        std::cout << "Memory savings: " << savings_percentage << "%" << std::endl;
    }
    
    void displayCache() const {
        factory_->displayCache();
    }
    
    size_t getCharacterCount() const {
        return characters_.size();
    }
    
    size_t getUniquePropertiesCount() const {
        return factory_->getCacheSize();
    }
};

// Advanced Flyweight: Text Style
class TextStyle {
private:
    std::string style_name_;
    std::shared_ptr<CharacterProperties> properties_;
    
public:
    TextStyle(const std::string& name, std::shared_ptr<CharacterProperties> props)
        : style_name_(name), properties_(props) {}
    
    std::string getName() const { return style_name_; }
    std::shared_ptr<CharacterProperties> getProperties() const { return properties_; }
    
    void display() const {
        std::cout << "Style: " << style_name_ << " -> ";
        properties_->display();
    }
};

// Style Manager
class StyleManager {
private:
    std::unordered_map<std::string, std::shared_ptr<TextStyle>> styles_;
    std::shared_ptr<CharacterPropertiesFactory> factory_;
    
public:
    StyleManager() : factory_(std::make_shared<CharacterPropertiesFactory>()) {}
    
    void createStyle(const std::string& name, const std::string& font_family, 
                    int font_size, const std::string& color, bool is_bold, bool is_italic) {
        
        auto properties = factory_->getCharacterProperties(
            font_family, font_size, color, is_bold, is_italic);
        
        auto style = std::make_shared<TextStyle>(name, properties);
        styles_[name] = style;
        
        std::cout << "Created style: " << name << std::endl;
    }
    
    std::shared_ptr<TextStyle> getStyle(const std::string& name) {
        auto it = styles_.find(name);
        if (it != styles_.end()) {
            return it->second;
        }
        return nullptr;
    }
    
    void displayStyles() const {
        std::cout << "\n=== Available Styles ===" << std::endl;
        for (const auto& pair : styles_) {
            pair.second->display();
        }
    }
    
    size_t getStyleCount() const {
        return styles_.size();
    }
};

void demonstrateFlyweightPattern();

#endif // FLYWEIGHT_HPP 