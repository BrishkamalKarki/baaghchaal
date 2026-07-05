# Install script for directory: D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/external/opusfile

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/RelWithDebInfo/opusfile.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/Debug/opusfile.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/Release/opusfile.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/MinSizeRel/opusfile.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/RelWithDebInfo/opusfile-0.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/Debug/opusfile-0.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/Release/opusfile-0.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/MinSizeRel/opusfile-0.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/RelWithDebInfo/opusurl.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/Debug/opusurl.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/Release/opusurl.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/MinSizeRel/opusurl.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/RelWithDebInfo/opusurl.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/Debug/opusurl.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/Release/opusurl.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/MinSizeRel/opusurl.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opus" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/external/opusfile/include/opusfile.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/opusfile" TYPE FILE FILES
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/OpusFileConfig.cmake"
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/OpusFileConfigVersion.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_mixer/build_wn/external/opusfile-build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
