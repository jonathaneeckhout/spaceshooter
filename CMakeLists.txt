cmake_minimum_required(VERSION 3.20)
project(Spaceshooter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
# set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

set(USE_LOCAL_ENGINE true) # Set to ON to use local directory of engine

if(USE_LOCAL_ENGINE)
    # Local development: use engine from ../myengine (or wherever it's checked out)
    add_subdirectory(../jengine jengine-build)
else()
    # Fetch the engine as a subproject from Git
    include(FetchContent)
    FetchContent_Declare(
        JEngine
        GIT_REPOSITORY https://github.com/jonathaneeckhout/jengine.git
        GIT_TAG main
    )
    FetchContent_MakeAvailable(JEngine)
endif()

# Find all .cpp source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable target
add_executable(Spaceshooter ${SOURCES})

# Include headers
target_include_directories(Spaceshooter PRIVATE
    include
    assets
)

target_link_libraries(Spaceshooter PRIVATE JEngine)
