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

# === RESOURCES (konfiguracja globalna) ===
# Katalog z zasobami; możesz zmienić przez -DRES_DIR=... przy konfiguracji
set(RES_DIR "${CMAKE_SOURCE_DIR}/resources" CACHE PATH "Directory with runtime resources")

# Helper: podpięcie resources/ do dowolnego targetu wykonywalnego
function(attach_resources tgt res_dir)
  if (EXISTS "${res_dir}")
    # Wszystkie pliki zasobów – jako zależność, aby zmiany triggerowały kopiowanie
    file(GLOB_RECURSE RES_FILES CONFIGURE_DEPENDS "${res_dir}/*")
    if (RES_FILES)
      add_custom_target(${tgt}_resources_stamp DEPENDS ${RES_FILES})
      add_dependencies(${tgt} ${tgt}_resources_stamp)
    endif()

    # Kopiowanie całego katalogu obok binarki
    add_custom_command(
      TARGET ${tgt} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              "${res_dir}" "$<TARGET_FILE_DIR:${tgt}>/resources"
      COMMENT "Copying resources/ for target '${tgt}'"
    )

    # Sprzątanie skopiowanych zasobów przy 'cmake --build . --target clean'
    set_property(TARGET ${tgt} APPEND PROPERTY
      ADDITIONAL_CLEAN_FILES "$<TARGET_FILE_DIR:${tgt}>/resources")
  else()
    message(STATUS "attach_resources: directory '${res_dir}' does not exist; skipping for ${tgt}")
  endif()
endfunction()


add_library(core ${MODULE_SOURCES})
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(core PRIVATE ${WARNINGS})

# ── Helpers to create application
function(add_app name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} PRIVATE core)
  target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_compile_options(${name} PRIVATE ${WARNINGS})
  attach_resources(${name} "${RES_DIR}")
endfunction()

# to get resources path
add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

#   Dodajemy po prostu add  add_app dla każdego apps/<nazwa>/main.cpp
add_app(playground ${CMAKE_SOURCE_DIR}/apps/playground/main.cpp)
# add_app(mytool     ${CMAKE_SOURCE_DIR}/apps/mytool/main.cpp)

# ================== TESTS ==================
include(CTest)
enable_testing()
# doctest header
include_directories(
  ${CMAKE_SOURCE_DIR}/third_party/doctest
)

add_executable(tests
    tests/test_main.cpp
    tests/test_explanation.cpp
)

target_link_libraries(tests PRIVATE core)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME unit COMMAND tests)