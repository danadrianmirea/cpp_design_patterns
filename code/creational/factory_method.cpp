#include "factory_method.hpp"
#include <iostream>

void demonstrateFactoryMethodPattern() {
    std::cout << "\n=== Factory Method Pattern Demo ===\n" << std::endl;

    // Create different document creators
    auto pdfCreator = std::make_shared<PDFCreator>();
    auto wordCreator = std::make_shared<WordCreator>();
    auto textCreator = std::make_shared<TextCreator>();

    // Process documents using different creators
    std::cout << "--- Processing PDF Document ---" << std::endl;
    pdfCreator->processDocument("report.pdf");

    std::cout << "\n--- Processing Word Document ---" << std::endl;
    wordCreator->processDocument("document.docx");

    std::cout << "\n--- Processing Text Document ---" << std::endl;
    textCreator->processDocument("notes.txt");

    // Direct creation and usage
    std::cout << "\n--- Direct Document Creation ---" << std::endl;
    auto pdfDoc = pdfCreator->createDocument("manual.pdf");
    pdfDoc->open();
    pdfDoc->save();

    auto wordDoc = wordCreator->createDocument("proposal.docx");
    wordDoc->open();
    wordDoc->print();

    std::cout << "\n=== End Factory Method Pattern Demo ===\n" << std::endl;
} 