# Explicitly list all .cpp files in this directory
set(STRUCTURAL_SOURCES
    structural/adapter.cpp
    structural/bridge.cpp
    structural/composite.cpp
    structural/decorator.cpp
    structural/facade.cpp
    structural/flyweight.cpp
    structural/proxy.cpp
)

# Make this variable available to the parent scope
set(STRUCTURAL_SOURCES ${STRUCTURAL_SOURCES} PARENT_SCOPE)

# Create a static library from these sources
#add_library(structural_lib ${STRUCTURAL_SOURCES})
