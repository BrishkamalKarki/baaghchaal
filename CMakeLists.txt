cmake_minimum_required(VERSION 3.28.3)
project(
    BaaghChaal
    VERSION 1.0
    DESCRIPTION "A traditional Nepali folk game"
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "BUILD TYPE" FORCE)
endif()

# SETTING THE SOURCE FILE
file(
    GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    )
# CREATING THE EXECUTABLE TARGET
add_executable(
    BaaghChaal
    ${SRC_FILES}
    )
# ALSO CHECK FOR THE HEADERS FILE
target_include_directories(
    BaaghChaal
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    )
if(WIN32)
    set(SDL3_DIR       "${CMAKE_SOURCE_DIR}/libraries/SDL/build_wn")
    set(SDL3_image_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL3_image/build_wn")
    set(SDL3_mixer_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL3_mixer/build_wn")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(SDL3_ttf_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL3_ttf/install_wn/Debug/cmake")
    else()
        set(SDL3_ttf_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL3_ttf/install_wn/Release/cmake")
    endif()
elseif(UNIX)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(SDL3_DIR       "${CMAKE_SOURCE_DIR}/libraries/SDL/build_ln/Debug")
        set(SDL3_image_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL3_image/build_ln/Debug")
        set(SDL3_ttf_DIR   "${CMAKE_SOURCE_DIR}/libraries/SDL3_ttf/install_ln/Debug/lib/cmake/SDL3_ttf")
        set(SDL3_mixer_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL3_mixer/build_ln/Debug")
    else()
        set(SDL3_DIR       "${CMAKE_SOURCE_DIR}/libraries/SDL/build_ln/Release")
        set(SDL3_image_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL3_image/build_ln/Release")
        set(SDL3_ttf_DIR   "${CMAKE_SOURCE_DIR}/libraries/SDL3_ttf/install_ln/Release/lib/cmake/SDL3_ttf")
        set(SDL3_mixer_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL3_mixer/build_ln/Release")
    endif()
endif()

list(APPEND CMAKE_PREFIX_PATH
    "${SDL3_DIR}"
    "${SDL3_image_DIR}"
    "${SDL3_ttf_DIR}"
    "${SDL3_mixer_DIR}"
    )

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_mixer REQUIRED)

# LINKING THE EXECUTABLE WITH SDL3 + EXTENSIONS
target_link_libraries(
    BaaghChaal
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
    )

# SETTING THE OUTPUT DIRECTORY
set(GAME_OUTPUT_DIR "${CMAKE_BINARY_DIR}")
# set_target_properties(
#     BaaghChaal
#     PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${GAME_OUTPUT_DIR}"
#     RUNTIME_OUTPUT_DIRECTORY_DEBUG "${GAME_OUTPUT_DIR}"
#     RUNTIME_OUTPUT_DIRECTORY_RELEASE "${GAME_OUTPUT_DIR}"
#     RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${GAME_OUTPUT_DIR}"
# )

if(WIN32)
    add_custom_command(TARGET BaaghChaal POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:BaaghChaal>
            $<TARGET_FILE_DIR:BaaghChaal>
        COMMAND_EXPAND_LISTS
    )
endif()