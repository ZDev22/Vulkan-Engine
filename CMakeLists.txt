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

# ---- Platform-specific: Ensure a real window backend is enabled for GLFW ----
# Set these before adding GLFW subdirectory to ensure they take effect
if(WIN32)
    set(GLFW_BUILD_WIN32 ON CACHE BOOL "Enable Win32 backend" FORCE)
    set(GLFW_BUILD_X11 OFF CACHE BOOL "Disable X11 backend" FORCE)
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "Disable Wayland backend" FORCE)
elseif(UNIX AND NOT APPLE)
    set(GLFW_BUILD_X11 ON CACHE BOOL "Enable X11 backend" FORCE)
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Enable Wayland backend" FORCE)
    set(GLFW_BUILD_WIN32 OFF CACHE BOOL "Disable Win32 backend" FORCE)
else()
    message(FATAL_ERROR "Unsupported platform for GLFW backend")
endif()

# Add GLFW subdirectory
add_subdirectory(${GLFW_DIR})

# Verify GLFW backend configuration
if(UNIX AND NOT APPLE)
    if(NOT GLFW_BUILD_X11 AND NOT GLFW_BUILD_WAYLAND)
        message(FATAL_ERROR "GLFW requires either X11 or Wayland backend enabled. Ensure required libraries are installed.")
    endif()
elseif(WIN32)
    if(NOT GLFW_BUILD_WIN32)
        message(FATAL_ERROR "GLFW requires Win32 backend enabled.")
    endif()
endif()

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

# Platform-specific Vulkan library linking
if(WIN32)
    # Use Vulkan loader import library and copy runtime DLL for Windows
    find_package(Vulkan REQUIRED)
    target_link_libraries(main PRIVATE glfw Vulkan::Vulkan)
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/deps/vulkan/includewindows/vulkan-1.dll"
        $<TARGET_FILE_DIR:main>/vulkan-1.dll
    )
elseif(UNIX AND NOT APPLE)
    # Prefer system Vulkan, fallback to local loader if available
    find_package(Vulkan REQUIRED)
    target_link_libraries(main PRIVATE glfw Vulkan::Vulkan dl pthread)
endif()

# Ensure correct entry point for Windows console app (not WIN32 GUI)
set_target_properties(main PROPERTIES WIN32_EXECUTABLE FALSE)