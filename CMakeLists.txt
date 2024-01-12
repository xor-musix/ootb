# The OOTB MIDI Platform

cmake_minimum_required(VERSION 3.15)

project(OOTB VERSION 0.0.1)

#First, we'll add the CMake folder
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(juce REQUIRED)

find_package(LibXml2 REQUIRED)
find_package(LibXslt REQUIRED)

include_directories(${LIBXML2_INCLUDE_DIR} ${LIBXSLT_INCLUDE_DIR})

add_subdirectory(plugin/source)

#adding any custom modules you might have:
#add_subdirectory(modules)