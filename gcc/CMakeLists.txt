

# ----------------------  PROJECT SETTINGS  ------------------- #
cmake_minimum_required(VERSION 3.20)                            #
project(ProgrammingAll LANGUAGES CXX)                           #
# ------------------------------------------------------------- #

# ------------------- C++ STANDARD SETTINGS  -------------------#
set(CMAKE_CXX_STANDARD 20)                                      #
set(CMAKE_CXX_STANDARD_REQUIRED ON)                             #
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)                           #
# ------------------------------------------------------------- #

# --------------------------  RESORUCES FOLDER  SETTINGS  --------------------------#
set(RES_DIR "${CMAKE_SOURCE_DIR}/resources" CACHE PATH "Directory with resources")  #
function(attach_resources target resource_dir)                                      #
    if (EXISTS "${resource_dir}")                                                   #
        file(GLOB_RECURSE RES_FILES CONFIGURE_DEPENDS "${resource_dir}/*")          #
        if (RES_FILES)                                                              #
            add_custom_target(${target}_resources_stamp DEPENDS ${RES_FILES})       #
            add_dependencies(${target} ${target}_resources_stamp)                   #
        endif()                                                                     #
        add_custom_command(                                                         #
            TARGET ${target} POST_BUILD                                             #
            COMMAND ${CMAKE_COMMAND} -E copy_directory                              #
                    "${resource_dir}" "$<TARGET_FILE_DIR:${target}>/resources"      #
            COMMENT "Coping resources to binary: ${target}"                      #
        )                                                                           #
    endif()                                                                         #
endfunction()                                                                       #       
# ----------------------------------------------------------------------------------#


# ------------------- UTILS LIBRARY SETTINGS  ------------------#
add_library(                                                    #
    utils_lib STATIC                                            #
    utils/src/logger.cpp                                        #
)                                                               #
target_include_directories(utils_lib PUBLIC utils/include)      #
# --------------------------------------------------------------#


# -------------- LEADERBOARD LIBRARY SETTINGS  -----------------#
add_library(                                                    #
    leaderboard_lib STATIC                                      #
    dev/leaderboard/src/leaderboard.cpp                         #    
    dev/leaderboard/src/parse.cpp                               #
)                                                               #
target_include_directories(                                     #
    leaderboard_lib PUBLIC dev/leaderboard/include              #
)                                                               #
target_link_libraries(leaderboard_lib PUBLIC utils_lib)         #
# --------------------------------------------------------------#
# ---------------- MAIN APP FOR LEADERBAORD  -------------------#
add_executable(leaderboard_app dev/leaderboard/app/main.cpp)    #
target_link_libraries(leaderboard_app PRIVATE leaderboard_lib)  #
attach_resources(leaderboard_app "${RES_DIR}")                  #
# --------------------------------------------------------------#

# --------------- PLAYGROUND LIBRARY SETTINGS  -----------------#
add_library(playground_lib STATIC                               # 
    dev/playground/src/knowledge.cpp                            #
)                                                               #
target_include_directories(                                     #
    playground_lib PUBLIC dev/playground/include                #
)                                                               #
target_link_libraries(playground_lib PUBLIC utils_lib)          #
# --------------------------------------------------------------#
# ---------------- MAIN APP FOR PLAYGROUND  --------------------#
add_executable(playground_app dev/playground/app/main.cpp)      #
target_link_libraries(playground_app PRIVATE playground_lib)    #
attach_resources(playground_app "${RES_DIR}")                   #
# --------------------------------------------------------------#


# ----------------- TRACKER LIBRARY SETTINGS  ------------------#
find_package(OpenSSL REQUIRED)                                  #
add_library(tracker_lib STATIC dev/tracker/src/tracker.cpp)     #                                                               #
target_include_directories(                                     #
    tracker_lib PUBLIC dev/tracker/include                      #
)                                                               #
target_link_libraries(tracker_lib PUBLIC utils_lib)             #
# --------------------------------------------------------------#
# ------------------ MAIN APP FOR TRACKER  ---------------------#
add_executable(tracker_app dev/tracker/app/main.cpp)            #
target_include_directories(                                     #
    tracker_app PRIVATE third_party/httplib                     #
)                                                               #
target_compile_definitions(                                     #
    tracker_app PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT              #
)                                                               #
target_link_libraries(tracker_app PRIVATE                       #
    tracker_lib                                                 #
    OpenSSL::SSL                                                #
    OpenSSL::Crypto                                             #
)                                                               #
attach_resources(tracker_app "${RES_DIR}")                      #
include_directories(third_party/nlohmann)                       #
# --------------------------------------------------------------#


# -------------------- TESTS SETTINGS  -------------------------#
enable_testing()                                                #
include_directories(third_party/doctest)                        #
                                                                #
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)                     #
add_executable(unit_tests ${TEST_SOURCES})                      #
target_link_libraries(                                          #
    unit_tests PRIVATE leaderboard_lib playground_lib utils_lib #
)                                                               #
add_test(NAME AllTests COMMAND unit_tests)                      #
# --------------------------------------------------------------#

