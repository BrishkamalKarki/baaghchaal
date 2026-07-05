# Install script for directory: D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/external/libpng

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SDL3_image")
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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/RelWithDebInfo/libpng16-16.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Debug/libpng16-16.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Release/libpng16-16.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/MinSizeRel/libpng16-16.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/RelWithDebInfo/libpng16-16.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Debug/libpng16-16.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Release/libpng16-16.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/MinSizeRel/libpng16-16.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/RelWithDebInfo/libpng16_static.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Debug/libpng16_staticd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Release/libpng16_static.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/MinSizeRel/libpng16_static.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/external/libpng/png.h"
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/external/libpng/pngconf.h"
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/pnglibconf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libpng16" TYPE FILE FILES
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/external/libpng/png.h"
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/external/libpng/pngconf.h"
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/pnglibconf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/RelWithDebInfo/pngfix.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Debug/pngfix.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Release/pngfix.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/MinSizeRel/pngfix.exe")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/RelWithDebInfo/png-fix-itxt.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Debug/png-fix-itxt.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/Release/png-fix-itxt.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/MinSizeRel/png-fix-itxt.exe")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man3" TYPE FILE FILES
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/external/libpng/libpng.3"
    "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/external/libpng/libpngpf.3"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man5" TYPE FILE FILES "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/external/libpng/png.5")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/libraries/SDL3_image/build_wn/external/libpng-build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
