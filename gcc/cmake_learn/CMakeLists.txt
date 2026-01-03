

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