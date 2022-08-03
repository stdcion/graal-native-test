#
# Executable name and options
#

# Target name
set(target test_foo)

# Output name
set(output_name ${target})

# Add project prefix to target name
set(target ${META_PROJECT_NAME}.${target})

# Print status
message(STATUS "App ${target}")


#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/")

file(GLOB headers CONFIGURE_DEPENDS
        "${include_path}/*.h"
        "${include_path}/*.hpp"
        )
file(GLOB sources CONFIGURE_DEPENDS
        "${source_path}/*.c"
        "${source_path}/*.cpp"
        "${source_path}/*.h"
        "${source_path}/*.hpp"
        )


#
# Create executable
#

# Build executable
add_executable(${target}
        #MACOSX_BUNDLE
        ""
        )

# Add sources to target
target_sources(${target}
        PRIVATE
        "${headers}"
        "${sources}"
        )

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})


#
# Project options
#

set_target_properties(${target}
        PROPERTIES
        ${DEFAULT_PROJECT_OPTIONS}
        FOLDER "${IDE_FOLDER}"
        OUTPUT_NAME "${output_name}"
        )


#
# Include directories
#

target_include_directories(${target}
        PRIVATE
        ${DEFAULT_INCLUDE_DIRECTORIES}
        ${PROJECT_BINARY_DIR}/include
        ${PROJECT_BINARY_DIR}/source/include
        )


#
# Libraries
#

target_link_libraries(${target}
        PRIVATE
        ${DEFAULT_LIBRARIES}
        Catch2::Catch2WithMain
        )


#
# Compile definitions
#

target_compile_definitions(${target}
        PRIVATE
        ${DEFAULT_COMPILE_DEFINITIONS}
        )


#
# Compile options
#

target_compile_options(${target}
        PRIVATE
        ${DEFAULT_COMPILE_OPTIONS}
        )


#
# Linker options
#

target_link_options(${target}
        PRIVATE
        ${DEFAULT_LINKER_OPTIONS}
        )

#
# Testing
#

add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
