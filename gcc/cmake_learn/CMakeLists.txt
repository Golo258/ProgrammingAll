

# ----------------------  PROJECT SETTINGS  ------------------- #
cmake_minimum_required(VERSION 3.20)                            #
project(CmakeLearn LANGUAGES CXX)                           #
# ------------------------------------------------------------- #

# ------------------- C++ STANDARD SETTINGS  -------------------#
set(CMAKE_CXX_STANDARD 20)                                      #
set(CMAKE_CXX_STANDARD_REQUIRED ON)                             #
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)                           #
# ------------------------------------------------------------- #

#ustawianie zmiennych
set(NAME "John")
set(SURNAME "Bordom")
set(FULL_NAME "${NAME}/${SURNAME}")

message(STATUS "Full name from variables: ${FULL_NAME}")

set(target_app_alias "cmake_learn_app")

add_executable(${target_app_alias} main.cpp)
target_include_directories(
    ${target_app_alias}
    PRIVATE
    inc
)

# dodawanie bibliotek
add_library(math_lib STATIC my_libraries/math_lib.cpp)
target_include_directories(
    math_lib
    PUBLIC
    my_libraries   
)

target_link_libraries(${target_app_alias} PRIVATE math_lib)

# dodawanie zewnętrzych bibliotek
find_package(CURL REQUIRED)
target_link_libraries(${target_app_alias} PRIVATE CURL::libcurl)

# header only library 
target_include_directories(${target_app_alias} PRIVATE external)

function(space)
    message(STATUS "========================================================")
endfunction()

function(log_messages param1 param2)
    message(STATUS "First param: ${param1}")
    message(STATUS "Second param: ${param2}")
endfunction()

log_messages("one" "two")
space()

# instrukcje warunkowe w funkcji
function(configure_module module_name)
    if(module_name STREQUAL "graphics")
        message(STATUS "COnfiguring graphics")
    elseif(module_name STREQUAL "sound")
        message(STATUS "COnfiguring sounds")
    else()
        message(STATUS "WARNING: Unknown module: ${module_name}")
    endif()
endfunction()

configure_module("graphics")
configure_module("sound")
configure_module("other")
space()

function(module_exists module_name)
    if(EXISTS ${module_name} OR IS_DIRECTORY ${module_name})
        message(STATUS "Module: ${module_name} exists")
    else()
        message(STATUS "Module: ${module_name} does not exist")
    endif()
endfunction()

module_exists("/usr/bin/ls")

space()
function(search_files files_dir)
    set(FILES "main.cpp" "logger.cpp" "variables.cpp")
    foreach(file ${FILES})
        set(FULL_PATH "${files_dir}/${file}")
        message (STATUS "Searching in ${FULL_PATH}")
        if(EXISTS ${FULL_PATH})
            message (STATUS "File ${file} exists")
        else()
            message (STATUS "File ${file} does not exists")
        endif()
        
    endforeach()
endfunction()

search_files("${CMAKE_CURRENT_SOURCE_DIR}") # folder gdzie jest CmakeLists.txt
search_files("../utils/")

space()
function(search_global_matching_files)
    # glob - tylko w danym folderze 
    file(GLOB MY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    foreach(SOURCE ${MY_SOURCES})
        message(STATUS "Found source: ${SOURCE}")
    endforeach()
    # globrecurse - także w podfolderah
    space()
    file(GLOB_RECURSE MY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
    foreach(HEADER ${MY_HEADERS})
        message(STATUS "Found header: ${HEADER}")
    endforeach()
endfunction()

search_global_matching_files()
space()
