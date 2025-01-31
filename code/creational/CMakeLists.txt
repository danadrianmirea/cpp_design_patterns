# Collect all .cpp files in this directory
file(GLOB CREATIONAL_SOURCES "*.cpp")

# Make this variable available to the parent scope
set(CREATIONAL_SOURCES ${CREATIONAL_SOURCES} PARENT_SCOPE)

# Create a static library from these sources
add_library(creational_lib ${CREATIONAL_SOURCES})