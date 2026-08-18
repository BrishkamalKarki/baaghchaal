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
    
if(WIN32)
    set (VCPKG_TRIPLET_DIR "${CMAKE_SOURCE_DIR}/libraries/x64-windows")
elseif(UNIX)
    set (VCPKG_TRIPLET_DIR "${CMAKE_SOURCE_DIR}/libraries/x64-linux")
endif()

# ALSO CHECK FOR THE HEADERS FILE
if (WIN32)
    target_include_directories(
        BaaghChaal  
        PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
    )
elseif (UNIX)
    target_include_directories(
        BaaghChaal
        PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        "${VCPKG_TRIPLET_DIR}/include"
    )
endif()


if (WIN32)
list(APPEND CMAKE_PREFIX_PATH "${VCPKG_TRIPLET_DIR}")
endif()

if (WIN32)
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
    find_package(SDL3_ttf REQUIRED)
    find_package(SDL3_mixer REQUIRED)
    find_library(BZIP2_LIB bz2 PATHS "${VCPKG_TRIPLET_DIR}/lib" REQUIRED)
    find_library(BROTLIDEC_LIB brotlidec PATHS "${VCPKG_TRIPLET_DIR}/lib" REQUIRED)
    find_library(BROTLICOMMON_LIB brotlicommon PATHS "${VCPKG_TRIPLET_DIR}/lib" REQUIRED)
endif()

if (WIN32)
    find_package(Freetype CONFIG REQUIRED)
endif()



# LINKING THE EXECUTABLE WITH SDL3 + EXTENSIONS
if (WIN32)
    target_link_libraries(
        BaaghChaal
        PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
    )
elseif(UNIX)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(SDL3_LIB_DIR "${VCPKG_TRIPLET_DIR}/lib")
    else()
        set(SDL3_LIB_DIR "${VCPKG_TRIPLET_DIR}/debug/lib")
    endif()
    target_link_libraries(
        BaaghChaal
        PRIVATE
        -Wl,--start-group
        "${SDL3_LIB_DIR}/libSDL3.a"
        "${SDL3_LIB_DIR}/libSDL3_image.a"
        "${SDL3_LIB_DIR}/libSDL3_ttf.a"
        "${SDL3_LIB_DIR}/libSDL3_mixer.a"
        "${VCPKG_TRIPLET_DIR}/lib/libfreetype.a"
        "${VCPKG_TRIPLET_DIR}/lib/libpng.a"
        "${VCPKG_TRIPLET_DIR}/lib/libjpeg.a"
        "${VCPKG_TRIPLET_DIR}/lib/libz.a"
        "${VCPKG_TRIPLET_DIR}/lib/libbz2.a"
        "${VCPKG_TRIPLET_DIR}/lib/libbrotlidec.a"
        "${VCPKG_TRIPLET_DIR}/lib/libbrotlicommon.a"
        -Wl,--end-group
        -lm
        -pthread
    )
endif()