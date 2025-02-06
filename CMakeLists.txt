#
# Copyright (c) 2019-2025, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# SPDX-License-Identifier: BSD-3-Clause
#

cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(gmicqt-digiKam)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/gmicqt/cmake/modules ${CMAKE_MODULE_PATH})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message("PREFIX_ext_gmic: ${PREFIX_ext_gmic}")
message("GmicQt_Conf: ${GmicQt_Conf}")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/gmicqt/src)

add_subdirectory(gmicqt)
