# Install script for directory: /home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3_ttf.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3_ttf.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/libSDL3_ttf.so.0.1.0"
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/libSDL3_ttf.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3_ttf.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3_ttf.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL/build_ln/Debug:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/libSDL3_ttf.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL3_ttf" TYPE FILE FILES
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/include/SDL3_ttf/SDL_textengine.h"
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/include/SDL3_ttf/SDL_ttf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3_ttf" TYPE FILE FILES
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/SDL3_ttfConfig.cmake"
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/SDL3_ttfConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3_ttf" TYPE FILE FILES
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/cmake/PkgConfigHelper.cmake"
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/cmake/Findharfbuzz.cmake"
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/cmake/Findplutosvg.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3_ttf/SDL3_ttf-shared-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3_ttf/SDL3_ttf-shared-targets.cmake"
         "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/CMakeFiles/Export/1aef9053b29433b7b1ad141cf388ac90/SDL3_ttf-shared-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3_ttf/SDL3_ttf-shared-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3_ttf/SDL3_ttf-shared-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3_ttf" TYPE FILE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/CMakeFiles/Export/1aef9053b29433b7b1ad141cf388ac90/SDL3_ttf-shared-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3_ttf" TYPE FILE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/CMakeFiles/Export/1aef9053b29433b7b1ad141cf388ac90/SDL3_ttf-shared-targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/sdl3-ttf.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/SDL3_ttf" TYPE FILE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/LICENSE.txt")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_ttf/build_ln/Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
