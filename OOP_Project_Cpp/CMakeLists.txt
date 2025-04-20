cmake_minimum_required(VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("OOP_Project_Cpp")

add_executable(OOP_Project_Cpp 
    main.cpp 
    World.cpp
    Organism.cpp
    Animal.cpp
    Plant.cpp
    Grass.cpp
    Dandelion.cpp
    Guarana.cpp
    Wolfberry.cpp
    Hogweed.cpp
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OOP_Project_Cpp PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(OOP_Project_Cpp PRIVATE .)
target_link_libraries(OOP_Project_Cpp PRIVATE ncurses)