# Install script for directory: /home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/examples

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-load-and-play" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-load-and-play")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-load-and-play"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer" TYPE EXECUTABLE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/basics-load-and-play")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-load-and-play" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-load-and-play")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-load-and-play"
         OLD_RPATH "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug:/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL/build_ln/Debug:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-load-and-play")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/CMakeFiles/basics-load-and-play.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-with-options" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-with-options")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-with-options"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer" TYPE EXECUTABLE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/basics-play-with-options")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-with-options" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-with-options")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-with-options"
         OLD_RPATH "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug:/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL/build_ln/Debug:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-with-options")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/CMakeFiles/basics-play-with-options.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-multiple-sounds" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-multiple-sounds")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-multiple-sounds"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer" TYPE EXECUTABLE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/basics-play-multiple-sounds")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-multiple-sounds" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-multiple-sounds")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-multiple-sounds"
         OLD_RPATH "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug:/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL/build_ln/Debug:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-play-multiple-sounds")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/CMakeFiles/basics-play-multiple-sounds.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-metadata" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-metadata")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-metadata"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer" TYPE EXECUTABLE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/basics-metadata")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-metadata" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-metadata")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-metadata"
         OLD_RPATH "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug:/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL/build_ln/Debug:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-metadata")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/CMakeFiles/basics-metadata.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-sinewave" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-sinewave")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-sinewave"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer" TYPE EXECUTABLE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/basics-sinewave")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-sinewave" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-sinewave")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-sinewave"
         OLD_RPATH "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug:/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL/build_ln/Debug:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-sinewave")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/CMakeFiles/basics-sinewave.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-seeking" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-seeking")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-seeking"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer" TYPE EXECUTABLE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/basics-seeking")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-seeking" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-seeking")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-seeking"
         OLD_RPATH "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug:/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL/build_ln/Debug:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/basics-seeking")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/CMakeFiles/basics-seeking.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/advanced-tag-tracks" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/advanced-tag-tracks")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/advanced-tag-tracks"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer" TYPE EXECUTABLE FILES "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/advanced-tag-tracks")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/advanced-tag-tracks" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/advanced-tag-tracks")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/advanced-tag-tracks"
         OLD_RPATH "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug:/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL/build_ln/Debug:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer/advanced-tag-tracks")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_ln/Debug/examples/CMakeFiles/advanced-tag-tracks.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/installed-examples/SDL3_mixer" TYPE FILE FILES
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/examples/music.mp3"
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/examples/splash.wav"
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/examples/spring.wav"
    "/home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/examples/sword.wav"
    )
endif()

