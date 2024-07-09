cmake_minimum_required(VERSION 3.11)
project(Game_test)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
set(RAYGUI_VERSION 4.0)
set(FLECS_VERSION 3.2.11)

# Fetch and build raylib if not found
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/raylib-src"
    BINARY_DIR "${CMAKE_BINARY_DIR}/_deps/raylib-build"
  )
  FetchContent_MakeAvailable(raylib)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Use file(GLOB ...) to add all source files
file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "src/*.hpp"
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} raylib)

# Debug configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_Debug")
  target_compile_definitions(${PROJECT_NAME} PRIVATE "DEBUG")
  target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
  # Add any other debug-specific configurations here
endif()

# Web Configurations
# if (DEFINED PLATFORM AND PLATFORM STREQUAL "Web")
#     # Tell Emscripten to build an example.html file.
#     set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

#     # Additional flags for targeting WebAssembly
#     set(CMAKE_EXECUTABLE_SUFFIX ".html") # Ensures the output is an HTML file that loads the WASM
#     set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s WASM=1 -s USE_GLFW=3 -s ALLOW_MEMORY_GROWTH=1 -s FULL_ES3=1")

#     # Link GLFW and other necessary libraries
#     target_link_libraries(${PROJECT_NAME} glfw)
# endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/resources")
  file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
endif()
