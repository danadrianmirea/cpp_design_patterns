# Explicitly list all .cpp files in this directory
set(BEHAVIORAL_SOURCES
    behavioral/chain_of_responsibility.cpp
    behavioral/command.cpp
    behavioral/interpreter.cpp
    behavioral/iterator.cpp
    behavioral/mediator.cpp
    behavioral/memento.cpp
    behavioral/observer.cpp
    behavioral/state.cpp
    behavioral/strategy.cpp
    behavioral/template_method.cpp
    behavioral/visitor.cpp
)

# Make this variable available to the parent scope
set(BEHAVIORAL_SOURCES ${BEHAVIORAL_SOURCES} PARENT_SCOPE)

# Create a static library from these sources
#add_library(behavioral_lib ${BEHAVIORAL_SOURCES})
