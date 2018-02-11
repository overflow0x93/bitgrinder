# Install script for directory: /home/overflow/Code/git/prereqs/akumuli/libakumuli

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libakumuli.so.0.7.37"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libakumuli.so.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libakumuli.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/overflow/Code/git/prereqs/akumuli/libakumuli/libakumuli.so.0.7.37"
    "/home/overflow/Code/git/prereqs/akumuli/libakumuli/libakumuli.so.0"
    "/home/overflow/Code/git/prereqs/akumuli/libakumuli/libakumuli.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libakumuli.so.0.7.37"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libakumuli.so.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libakumuli.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/overflow/Code/git/prereqs/akumuli/libakumuli/../include/akumuli_version.h"
    "/home/overflow/Code/git/prereqs/akumuli/libakumuli/../include/akumuli_config.h"
    "/home/overflow/Code/git/prereqs/akumuli/libakumuli/../include/akumuli.h"
    "/home/overflow/Code/git/prereqs/akumuli/libakumuli/../include/akumuli_def.h"
    )
endif()

