#/*
#* CMakeLists.txt
 #* 
 #* Copyright 2024 Unknown <rPatsher@localhost>
 #* 
 #* This program is free software; you can redistribute it and/or modify
 #* it under the terms of the GNU General Public License as published by
 #* the Free Software Foundation; either version 2 of the License, or
 #* (at your option) any later version.
 #* 
 #* This program is distributed in the hope that it will be useful,
 #* but WITHOUT ANY WARRANTY; without even the implied warranty of
 #* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #* GNU General Public License for more details.
 #* 
 #* You should have received a copy of the GNU General Public License
 #* along with this program; if not, write to the Free Software
 #* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 #* MA 02110-1301, USA.
 #* 
 #* 
# */
 

# Cmake Version
cmake_minimum_required(VERSION 3.16.3)

# Project 
project(patsher2d-x VERSION 2.5) 



# Include Engine Sources
include(core/CMakeLists.txt)
include(main/CMakeLists.txt)
include(scene/CMakeLists.txt)
include(servers/CMakeLists.txt)
include(editor/CMakeLists.txt)
include(external/CMakeLists.txt)
include(thirdparty/CMakeLists.txt)
include(tools/CMakeLists.txt)
include(drivers/CMakeLists.txt)
include(resources/CMakeLists.txt)
include(module/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build RayLib And Link Ray With Patsher2DX
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(BUILD_PATSHER2DX OFF CACHE BOOL "" FORCE)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)





add_executable(main main/main.cpp)
