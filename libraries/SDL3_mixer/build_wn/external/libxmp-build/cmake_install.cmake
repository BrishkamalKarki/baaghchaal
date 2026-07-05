# Install script for directory: D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/external/libxmp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SDL3_mixer")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/RelWithDebInfo/libxmp.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/Debug/libxmp.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/Release/libxmp.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/MinSizeRel/libxmp.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/RelWithDebInfo/libxmp.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/Debug/libxmp.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/Release/libxmp.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/MinSizeRel/libxmp.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/libxmp-shared-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/libxmp-shared-targets.cmake"
         "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/CMakeFiles/Export/272ceadb8458515b2ae4b5630a6029cc/libxmp-shared-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/libxmp-shared-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/libxmp-shared-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/CMakeFiles/Export/272ceadb8458515b2ae4b5630a6029cc/libxmp-shared-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/CMakeFiles/Export/272ceadb8458515b2ae4b5630a6029cc/libxmp-shared-targets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/CMakeFiles/Export/272ceadb8458515b2ae4b5630a6029cc/libxmp-shared-targets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/CMakeFiles/Export/272ceadb8458515b2ae4b5630a6029cc/libxmp-shared-targets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/CMakeFiles/Export/272ceadb8458515b2ae4b5630a6029cc/libxmp-shared-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/external/libxmp/libxmp-config.cmake"
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/libxmp-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/external/libxmp/include/xmp.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/libxmp.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/examples/cmake_install.cmake")
  include("D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/docs/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/libxmp-build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
