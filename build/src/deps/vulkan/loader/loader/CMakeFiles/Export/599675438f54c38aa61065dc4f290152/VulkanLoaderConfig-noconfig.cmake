#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Vulkan::Loader" for configuration ""
set_property(TARGET Vulkan::Loader APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Vulkan::Loader PROPERTIES
  IMPORTED_IMPLIB_NOCONFIG "${_IMPORT_PREFIX}/lib/libvulkan-1.dll.a"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/vulkan-1.dll"
  )

list(APPEND _cmake_import_check_targets Vulkan::Loader )
list(APPEND _cmake_import_check_files_for_Vulkan::Loader "${_IMPORT_PREFIX}/lib/libvulkan-1.dll.a" "${_IMPORT_PREFIX}/bin/vulkan-1.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
