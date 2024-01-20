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

set(SOURCES_HEADER 
	config/engine.h,
	config/project_settings.h,
	event/event_screen_touch.h,
	event/event_screen_drag.h,
	event/event_mouse_button.h,
	event/event_mouse_motion.h,
	event/event_mouse_button_touch.h,
	error/error_list.h,
	error/error_macros.h,
	input/input.h,
	input/input_map.h,
	input/input_list.h,
	io/file_access.h,
	io/file_system.h,
	io/file_access_dock,
	io/resources.h,
	io/dir_access.h,
	io/http_client.h,
	io/http_server.h,
	io/file_utils.h,
	io/config_file.h,
	extension/extension.h,
	extension/extension_manager.h,
	os/os.h,
	os/time.h
	os/thread.h,
	os/thread_safe.h,
	os/memory.h,
	os/time_enum.h
	object/m_class.h,
	object/m_object.h,
	object/script.h,
	object/ref_counted.h,
	object/callback_func.h,
	object/callback_signals.h,
	object/script_instance.h,
	object/script_native.h
	object/undo_redo.h,
	
	
	
)

set(SOURCES 
	config/engine.cpp,
	config/project_settings.cpp,
	event/event_screen_touch.cpp,
	event/event_screen_drag.cpp,
	event/event_mouse_button.cpp,
	event/event_mouse_motion.cpp,
	event/event_mouse_button_touch.cpp,
	error/error_list.cpp,
	error/error_macros.cpp,
	input/input.cpp,
	input/input_map.cpp,
	input/input_list.cpp,
	io/file_access.cpp,
	io/file_system.cpp,
	io/file_access_dock,
	io/resources.cpp,
	io/dir_access.cpp,
	io/http_client.cpp,
	io/http_server.cpp,
	io/file_utils.cpp,
	io/config_file.cpp,
	extension/extension.cpp,
	extension/extension_manager.cpp,
	os/os.cpp,
	os/time.cpp
	os/thread.cpp,
	os/thread_safe.cpp,
	os/memory.cpp,
	os/time_enum.cpp
	object/m_class.cpp,
	object/m_object.cpp,
	object/script.cpp,
	object/ref_counted.cpp,
	object/callback_func.cpp,
	object/callback_signals.cpp,
	object/script_instance.cpp,
	object/script_native.cpp,
	object/undo_redo.cpp,
	object/undo_redo_manager.cpp,
	string/string.cpp,
	string/cstring.cpp,
	string/print_string.cpp,
	string/string_buffer.cpp
			
	
)
