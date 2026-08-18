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
    set (VCPKG_TRIPLET_DIR "${CMAKE_SOURCE_DIR}/third_party/x64-windows")
elseif(UNIX)
    set (VCPKG_TRIPLET_DIR "${CMAKE_SOURCE_DIR}/third_party/x64-linux")
endif()

list(APPEND CMAKE_PREFIX_PATH "${VCPKG_TRIPLET_DIR}")

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

if(WIN32)
    add_custom_command(TARGET BaaghChaal POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            $<TARGET_RUNTIME_DLLS:BaaghChaal>
            $<TARGET_FILE_DIR:BaaghChaal>
        COMMAND_EXPAND_LISTS
    )
endif()