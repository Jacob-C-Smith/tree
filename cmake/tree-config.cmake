# TREE CMake configuration file:
# This file is meant to be placed in a cmake subfolder of TREE-devel-2.x.y-VC

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)
set_package_properties(TREE PROPERTIES
    URL "https://g10.app/status/#abstract_data_ii"
    DESCRIPTION "Tree ADT"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(TREE_FOUND TRUE)

# For compatibility with autotools TREE-config.cmake, provide TREE_* variables.

set_and_check(TREE_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(TREE_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(TREE_INCLUDE_DIR  "${TREE_PREFIX}/include")
set(TREE_INCLUDE_DIRS           "${TREE_INCLUDE_DIR}")
set_and_check(TREE_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(TREE_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(TREE_LIBRARIES TREE::TREE)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated TREE-target.cmake files.

set(_TREE_library     "${TREE_LIBDIR}/tree.lib")
set(_TREE_dll_library "${TREE_BINDIR}/tree.dll")
if(EXISTS "${_TREE_library}" AND EXISTS "${_TREE_dll_library}")
    if(NOT TARGET TREE::TREE)
        add_library(TREE::TREE SHARED IMPORTED)
        set_target_properties(TREE::TREE
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${TREE_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_TREE_library}"
                IMPORTED_LOCATION "${_TREE_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "TREE_SHARED"
                INTERFACE_TREE_SHARED "ON"
        )
    endif()
    set(TREE_TREE_FOUND TRUE)
else()
    set(TREE_TREE_FOUND FALSE)
endif()
unset(_TREE_library)
unset(_TREE_dll_library)

check_required_components(TREE)
