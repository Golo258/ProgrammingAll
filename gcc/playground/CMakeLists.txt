cmake_minimum_required(VERSION 3.20)
project(cpp_min LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(app src/main.cpp)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)

# delikatne ostrzeżenia (opcjonalnie – możesz wywalić)
if (MSVC)
  target_compile_options(app PRIVATE /W4)
else()
  target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic)
endif()
