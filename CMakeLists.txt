cmake_minimum_required(VERSION 3.10)
project(VulkanProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define paths to local dependencies in src/deps
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/src/deps/glfw)
set(GLM_DIR ${CMAKE_SOURCE_DIR}/src/deps/glm)

# Select Vulkan include directory based on platform
if(UNIX AND NOT APPLE)
    set(VULKAN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/deps/vulkan/includelinux)
elseif(WIN32)
    set(VULKAN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/deps/vulkan/includewindows)
else()
    message(FATAL_ERROR "Unsupported platform for Vulkan include directory")
endif()

# Add GLFW as a subdirectory (build from source)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})

# GLM is header-only
set(GLM_INCLUDE_DIR ${GLM_DIR})

# Collect source files (only from src/, excluding deps)
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE C_SOURCES "src/*.c")
list(APPEND SOURCES ${CPP_SOURCES} ${C_SOURCES})
list(FILTER SOURCES EXCLUDE REGEX "CMakeCXXCompilerId\\.cpp")
list(FILTER SOURCES EXCLUDE REGEX "CMakeCCompilerId\\.c")
list(FILTER SOURCES EXCLUDE REGEX "src/deps/glm/.*")
list(FILTER SOURCES EXCLUDE REGEX "src/deps/vulkan/.*")
list(FILTER SOURCES EXCLUDE REGEX "src/deps/glfw/examples/.*")
list(FILTER SOURCES EXCLUDE REGEX "src/deps/glfw/tests/.*")
# Ensure global.cpp is included
list(APPEND SOURCES src/vulkan/global.cpp)
message(STATUS "Sources: ${SOURCES}")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory")
endif()

# Define the executable
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
add_executable(main ${SOURCES})

# Include directories
target_include_directories(main PRIVATE
    ${VULKAN_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${GLFW_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/include
)

# Link GLFW and Vulkan (assumes system Vulkan loader is available)
find_package(Vulkan REQUIRED)
target_link_libraries(main PRIVATE glfw Vulkan::Vulkan)

# Copy Vulkan runtime library to output directory for Windows (optional)
if(WIN32)
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/deps/vulkan/includewindows/vulkan-1.dll"
        $<TARGET_FILE_DIR:main>/vulkan-1.dll
    )
endif()