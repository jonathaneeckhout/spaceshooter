cmake_minimum_required(VERSION 3.10)
project(Spaceshooter)

# Use clang++ and set flags
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(JEngine REQUIRED)

# Find all .cpp source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable target
add_executable(Spaceshooter ${SOURCES})

# Include headers
target_include_directories(Spaceshooter PRIVATE include)

target_link_libraries(Spaceshooter 
    PRIVATE 
        JEngine::JEngine
        SDL2::SDL2
        SDL2_ttf::SDL2_ttf)