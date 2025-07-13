#ifndef FACTORY_METHOD_HPP
#define FACTORY_METHOD_HPP

#include <iostream>
#include <string>
#include <memory>

// Abstract Product: Document
class Document {
public:
    virtual ~Document() = default;
    virtual void open() = 0;
    virtual void save() = 0;
    virtual void close() = 0;
    virtual void print() = 0;
};

// Concrete Products
class PDFDocument : public Document {
private:
    std::string filename_;
    
public:
    explicit PDFDocument(const std::string& filename) : filename_(filename) {}
    
    void open() override {
        std::cout << "Opening PDF document: " << filename_ << std::endl;
    }
    
    void save() override {
        std::cout << "Saving PDF document: " << filename_ << std::endl;
    }
    
    void close() override {
        std::cout << "Closing PDF document: " << filename_ << std::endl;
    }
    
    void print() override {
        std::cout << "Printing PDF document: " << filename_ << std::endl;
    }
};

class WordDocument : public Document {
private:
    std::string filename_;
    
public:
    explicit WordDocument(const std::string& filename) : filename_(filename) {}
    
    void open() override {
        std::cout << "Opening Word document: " << filename_ << std::endl;
    }
    
    void save() override {
        std::cout << "Saving Word document: " << filename_ << std::endl;
    }
    
    void close() override {
        std::cout << "Closing Word document: " << filename_ << std::endl;
    }
    
    void print() override {
        std::cout << "Printing Word document: " << filename_ << std::endl;
    }
};

class TextDocument : public Document {
private:
    std::string filename_;
    
public:
    explicit TextDocument(const std::string& filename) : filename_(filename) {}
    
    void open() override {
        std::cout << "Opening Text document: " << filename_ << std::endl;
    }
    
    void save() override {
        std::cout << "Saving Text document: " << filename_ << std::endl;
    }
    
    void close() override {
        std::cout << "Closing Text document: " << filename_ << std::endl;
    }
    
    void print() override {
        std::cout << "Printing Text document: " << filename_ << std::endl;
    }
};

// Abstract Creator
class DocumentCreator {
public:
    virtual ~DocumentCreator() = default;
    
    // Factory Method
    virtual std::shared_ptr<Document> createDocument(const std::string& filename) = 0;
    
    // Template method that uses the factory method
    void processDocument(const std::string& filename) {
        auto document = createDocument(filename);
        document->open();
        document->save();
        document->print();
        document->close();
    }
};

// Concrete Creators
class PDFCreator : public DocumentCreator {
public:
    std::shared_ptr<Document> createDocument(const std::string& filename) override {
        return std::make_shared<PDFDocument>(filename);
    }
};

class WordCreator : public DocumentCreator {
public:
    std::shared_ptr<Document> createDocument(const std::string& filename) override {
        return std::make_shared<WordDocument>(filename);
    }
};

class TextCreator : public DocumentCreator {
public:
    std::shared_ptr<Document> createDocument(const std::string& filename) override {
        return std::make_shared<TextDocument>(filename);
    }
};

void demonstrateFactoryMethodPattern();

#endif // FACTORY_METHOD_HPP 