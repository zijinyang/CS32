cmake_minimum_required(VERSION 3.10)
project(MultiExecutableProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Parent Directory: Each .cpp file becomes its own executable ---
# GLOB only .cpp files in the current (parent) directory
file(GLOB PARENT_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(SRC_FILE ${PARENT_CPP_FILES})
    # Get the base name of the file to name the executable
    get_filename_component(EXE_NAME ${SRC_FILE} NAME_WE)
    add_executable(${EXE_NAME} ${SRC_FILE})
endforeach()

# --- Child Directories: All .cpp files in a child directory form one executable ---
# Find all directories in the current folder
file(GLOB CHILD_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/")
foreach(DIR ${CHILD_DIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}")
        # Glob all .cpp files in the child directory (non-recursive)
        file(GLOB CHILD_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.cpp")
        if(CHILD_CPP_FILES)
            # Use the directory name (without trailing slash) as the target name
            string(REPLACE "/" "" TARGET_NAME ${DIR})
            add_executable(${TARGET_NAME} ${CHILD_CPP_FILES})
        endif()
    endif()
endforeach()
