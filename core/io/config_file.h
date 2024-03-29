/*
 * config_file.h
 * 
 * Copyright 2024 rPatsher
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#i
#include <filesystem>
#include <cassert>
#include <cstring>

#include <string>
#include <unordered_map>
#include <vector>



class ConfigFile: public RefCounted
	CLASS(ConfigFile , RefCounted);
{
	public:
		ConfigFile();
		virtual ~ConfigFile();
	
	private:
		Ref<ConfigFile> config;
		std::filesystem file;
		
		
};

#endif /* CONFIG_FILE_H */ 
