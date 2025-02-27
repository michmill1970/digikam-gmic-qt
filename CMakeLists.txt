#
# Copyright (c) 2019-2025, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# SPDX-License-Identifier: BSD-3-Clause
#

# mm added
# set(ZLIB_LIBRARY "/d/dk/x64-windows/lib/")
# set(ZLIB_INCLUDE_DIR "/d/dk/x64-windows/include/")
# set(ZLIB_ZLIB_INCLUDE_DIR "/d/dk/x64-windows/include/")
# set(PNG_LIBRARY "/d/dk/x64-windows/lib/")
# set(PNG_PNG_INCLUDE_DIR "/d/dk/x64-windows/include/libpng16/")
set(CMAKE_TOOLCHAIN_FILE "c:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows")
set(VCPKG_ROOT "c:\\vcpkg")
set(INSTALL_ROOT "E:\\dk")
# set(VCPKG_VERBOSE ON)
set(CMAKE_FIND_DEBUG_MODE TRUE)
# set(CMAKE_TOOLCHAIN_FILE $env{CMAKE_TOOLCHAIN_FILE})

cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(gmicqt-digiKam)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/gmicqt/cmake/modules ${CMAKE_MODULE_PATH})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${CMAKE_SOURCE_DIR}/gmicqt/src)

add_subdirectory(gmicqt)
