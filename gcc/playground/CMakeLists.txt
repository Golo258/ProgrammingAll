# ------------------------------

cmake_minimum_required(VERSION 3.20)
project(cpp_min LANGUAGES CXX)

# ------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------

# Library to all modules files 
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/modules/*.cpp)


add_library(core ${MODULE_SOURCES})
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(core PRIVATE ${WARNINGS})

# ── Helpers to create application
function(add_app name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} PRIVATE core)
  target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_compile_options(${name} PRIVATE ${WARNINGS})
endfunction()

# ─Aplikacje (po jednym w katalogu)
#   Dodajemy po prostu add  add_app dla każdego apps/<nazwa>/main.cpp
add_app(playground ${CMAKE_SOURCE_DIR}/apps/playground/main.cpp)
# add_app(mytool     ${CMAKE_SOURCE_DIR}/apps/mytool/main.cpp)

#------------------