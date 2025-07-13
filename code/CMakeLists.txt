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

# Debug: Print the sources being compiled
message(STATUS "CREATIONAL_SOURCES: ${CREATIONAL_SOURCES}")
message(STATUS "BEHAVIORAL_SOURCES: ${BEHAVIORAL_SOURCES}")
message(STATUS "STRUCTURAL_SOURCES: ${STRUCTURAL_SOURCES}")
message(STATUS "All SOURCES: ${SOURCES}")

# Create the main executable
add_executable(main ${SOURCES})

# Explicitly include adapter.cpp if it's not being picked up
if(NOT STRUCTURAL_SOURCES)
    list(APPEND SOURCES "structural/adapter.cpp")
endif()

# Link libraries (if needed)
#target_link_libraries(main creational_lib behavioral_lib structural_lib)
