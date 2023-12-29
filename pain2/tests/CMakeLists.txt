cmake_minimum_required(VERSION 3.14)
project(UnoTests)

# Fetch Catch2 testing framework
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.7
)
FetchContent_MakeAvailable(Catch2)

# Include directories for your project headers and Catch2 headers
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../include  # Adjust to your project's include directory
        ${catch2_SOURCE_DIR}/single_include
)

# Add the executable for UnoTests
add_executable(UnoTests
        NormalCardTest.cpp
        ../src/Model/NormalCard.cpp
        BotPlayerTest.cpp
        DeckTest.cpp
        HumanPlayerTest.cpp
        WildCardTest.cpp
        UnoGameTest.cpp  # Include the source file of the NormalCard class
        # Add other source files for the classes you're testing here
)

# Link the Catch2 library with your test executable
target_link_libraries(UnoTests PRIVATE Catch2::Catch2)

# Specify C++ Standard
set_property(TARGET UnoTests PROPERTY CXX_STANDARD 17)
