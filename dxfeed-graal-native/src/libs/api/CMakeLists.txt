#
# Library name and options
#

# Target
set(target api)

# Print status
message(STATUS "Lib ${target}")

# Set API export file and macro
string(MAKE_C_IDENTIFIER ${target} target_id)
string(TOUPPER ${target_id} target_id)

# Target name
set(target_name ${target})

# Output name
set(output_name ${target})

# Add project prefix to target name
set(target ${META_PROJECT_NAME}.${target})


#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target_name}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB headers CONFIGURE_DEPENDS
        "${include_path}/*.h"
        "${include_path}/*.hpp"
        "${include_path}/jni_wrapper/*.h"
        "${include_path}/jni_wrapper/*.hpp"
        )
file(GLOB sources CONFIGURE_DEPENDS
        "${source_path}/*.c"
        "${source_path}/*.cpp"
        "${source_path}/*.h"
        "${source_path}/*.hpp"
        )


#
# Create library
#

# Build library
add_library(${target}
        ${sources}
        ${headers}
        )

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target_name} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)


#
# Project options
#

set_target_properties(${target}
        PROPERTIES
        ${DEFAULT_PROJECT_OPTIONS}
        FOLDER "${IDE_FOLDER}"
        VERSION ${META_VERSION}
        SOVERSION ${META_VERSION_MAJOR}
        OUTPUT_NAME ${output_name}
        )


#
# Include directories
#

target_include_directories(${target}
        PRIVATE
        ${PROJECT_BINARY_DIR}/include
        ${PROJECT_BINARY_DIR}/source/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/include

        PUBLIC
        ${DEFAULT_INCLUDE_DIRECTORIES}

        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )


#
# Libraries
#

target_link_libraries(${target}
        PRIVATE

        PUBLIC
        ${DEFAULT_LIBRARIES}
        ${META_PROJECT_NAME}::GraalSample

        INTERFACE
        )


#
# Compile definitions
#

target_compile_definitions(${target}
        PRIVATE

        PUBLIC
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_id}_STATIC_DEFINE>
        ${DEFAULT_COMPILE_DEFINITIONS}

        INTERFACE
        )


#
# Compile options
#

target_compile_options(${target}
        PRIVATE

        PUBLIC
        ${DEFAULT_COMPILE_OPTIONS}

        INTERFACE
        )


#
# Linker options
#

target_link_options(${target}
        PRIVATE

        PUBLIC
        ${DEFAULT_LINKER_OPTIONS}

        INTERFACE
        )


#
# Custom commands
#

# Copy shared library to output directory
add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:GraalSample> $<TARGET_FILE_DIR:${target}>
        )
