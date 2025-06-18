cmake_minimum_required(VERSION 3.10)
project(VulkanProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define paths to local dependencies in src/deps
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/src/deps/glfw)
set(GLM_DIR ${CMAKE_SOURCE_DIR}/src/deps/glm)
set(VULKAN_DIR ${CMAKE_SOURCE_DIR}/src/deps/vulkan)
set(VULKAN_LOADER_DIR ${VULKAN_DIR}/loader)
set(VULKAN_HEADERS_DIR ${VULKAN_DIR}/headers)

# Add GLFW as a subdirectory (build from source)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})

# GLM is header-only
set(GLM_INCLUDE_DIR ${GLM_DIR})

# Vulkan Headers (for include paths)
set(Vulkan_INCLUDE_DIRS ${VULKAN_HEADERS_DIR}/include)

# Add Vulkan Loader as a subdirectory
set(BUILD_WSI_XCB_SUPPORT OFF CACHE BOOL "" FORCE)  # Disable XCB if not needed
set(BUILD_WSI_XLIB_SUPPORT OFF CACHE BOOL "" FORCE)  # Disable Xlib if not needed
set(BUILD_WSI_WAYLAND_SUPPORT OFF CACHE BOOL "" FORCE)  # Disable Wayland if not needed
set(BUILD_WSI_WIN32_SUPPORT ${WIN32} CACHE BOOL "" FORCE)  # Enable Win32 support on Windows
add_subdirectory(${VULKAN_HEADERS_DIR})
add_subdirectory(${VULKAN_LOADER_DIR})

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
    ${Vulkan_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIR}
    ${GLFW_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/include
)

# Link libraries
target_link_libraries(main PRIVATE glfw vulkan)

# Copy Vulkan runtime library to output directory for Windows
if(WIN32)
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:vulkan>
        $<TARGET_FILE_DIR:main>/vulkan-1.dll
    )
endif()