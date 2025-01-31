# Collect all .cpp files in this directory
file(GLOB STRUCTURAL_SOURCES "*.cpp")

# Make this variable available to the parent scope
set(STRUCTURAL_SOURCES ${STRUCTURAL_SOURCES} PARENT_SCOPE)

# Create a static library from these sources
#add_library(structural_lib ${STRUCTURAL_SOURCES})
