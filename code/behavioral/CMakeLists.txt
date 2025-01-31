# Collect all .cpp files in this directory
file(GLOB BEHAVIORAL_SOURCES "*.cpp")

# Make this variable available to the parent scope
set(BEHAVIORAL_SOURCES ${BEHAVIORAL_SOURCES} PARENT_SCOPE)

# Create a static library from these sources
add_library(behavioral_lib ${BEHAVIORAL_SOURCES})
