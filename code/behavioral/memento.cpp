#include "memento.hpp"
#include <iostream>

void demonstrateMementoPattern() {
    std::cout << "\n=== Memento Pattern Demo ===\n" << std::endl;

    TextEditor editor;
    Caretaker caretaker;

    // Initial state
    editor.setContent("Hello");
    editor.showContent();
    caretaker.addMemento(editor.createMemento());

    // First change
    editor.setContent("Hello World");
    editor.showContent();
    caretaker.addMemento(editor.createMemento());

    // Second change
    editor.setContent("Hello World!");
    editor.showContent();
    caretaker.addMemento(editor.createMemento());

    // Undo to previous state
    std::cout << "\nUndoing to previous state:" << std::endl;
    editor.restoreFromMemento(caretaker.getMemento(1));
    editor.showContent();

    // Undo to initial state
    std::cout << "\nUndoing to initial state:" << std::endl;
    editor.restoreFromMemento(caretaker.getMemento(0));
    editor.showContent();

    std::cout << "\n=== End Memento Pattern Demo ===\n" << std::endl;
} 