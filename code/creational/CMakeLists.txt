# Explicitly list all .cpp files in this directory
set(CREATIONAL_SOURCES
    creational/abstract_factory.cpp
    creational/builder.cpp
    creational/factory_method.cpp
    creational/prototype.cpp
    creational/singleton.cpp
)

# Make this variable available to the parent scope
set(CREATIONAL_SOURCES ${CREATIONAL_SOURCES} PARENT_SCOPE)

# Create a static library from these sources
#add_library(creational_lib ${CREATIONAL_SOURCES})