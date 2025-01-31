# Add subdirectories
add_subdirectory(creational)
add_subdirectory(behavioral)
add_subdirectory(structural)

# Gather sources from all subdirectories
set(SOURCES main.cpp)

# Link sources from subdirectories
list(APPEND SOURCES ${CREATIONAL_SOURCES})
list(APPEND SOURCES ${BEHAVIORAL_SOURCES})
list(APPEND SOURCES ${STRUCTURAL_SOURCES})

# Create the main executable
add_executable(main ${SOURCES})

# Link libraries (if needed)
#target_link_libraries(main creational_lib behavioral_lib structural_lib)
