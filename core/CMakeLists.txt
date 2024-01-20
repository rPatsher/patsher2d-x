#/*
 #* CMakeLists.txt
 #* 
 #* Copyright 2024 rPatsher
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


# This File `CMakeLists.txt` To Generate The Patsher2D-X Engine Libary 
# Build The LibPatsher2D-X
# Build The LibNative-X 

set(PATSHER2D-X VERSION 2.5)

set(PATSHER2D-X_CORE_LIB patsher2d)

project(libpatsher2d-x) 


# Include Core Sources
include(config/CMakeLists.txt)
include(error/CMakeLists.txt)
include(event/CMakeLists.txt)
include(input/CMakeLists.txt)
include(extension/CMakeLists.txt)
include(io/CMakeLists.txt)
include(string/CMakeLists.txt)
include(math/CMakeLists.txt)
include(object/CMakeLists.txt)
include(os/CMakeLists.txt)
include(templates/CMakeLists.txt)
include(variant/CMakeLists.txt)

# Include Core Files

set(SOURCES
	core_bind.cpp
	core_bind.h,
	register_core_types.cpp,
	register_core_types.h,
	version.gen.h,
	typedefs.h
)

# Default Value For Extension To Build Patsher2D-X Exetnsion Modules With Sources  
option(BUILD_EXTENSION "Build Extension" ON)

# Default Value For Editor To Build Patsher2D-X Editor Interface With Sources
option(BUILD_EDITOR_INTERFACE "Build Editor" ON)

if(BUILD_EXTENSION)
	include(core/extension/CMakeLists.txt)
endif(BUILD_EXTENSION)

if(BUILD_EDITOR_INTERFACE)
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/editor/CMakeLists.txt")
		include(editor/CMakeLists.txt)
	else()
		message(WARNING "${CMAKE_CURRENT_SOURCE_DIR}/editor/CMakeLists.txt Not Found")
	endif()
		# Not Anyting Source Here
endif(BUILD_EDITOR_INTERFACE)
		
# Include Header

