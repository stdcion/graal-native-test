#
# Library name and options
#

# Target
set(target GraalSample)

# Print status
message(STATUS "Imported lib ${target}")


#
# Create target
#

# Add imported library
add_library(${target} SHARED IMPORTED GLOBAL)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Set empty library extension
set(lib_extension)

# Add platform specific variable
if (WIN32)
    set(lib_extension dll)
elseif (APPLE)
    set(lib_extension dylib)
elseif (UNIX)
    set(lib_extension so)
endif ()


#
# Project options
#

# Target properties
set_target_properties(${target}
        PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/${target}.${lib_extension}"
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/${target}.${lib_extension}"
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/${target}.${lib_extension}"
        IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/${target}.lib"
        IMPORTED_IMPLIB_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/${target}.lib"
        IMPORTED_IMPLIB_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/${target}.lib"
        )

