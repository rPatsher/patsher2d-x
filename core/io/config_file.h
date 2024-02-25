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



#include <unordered_map>
#include <variant>

#include "core/object/ref_counted.h"
#include "core/templates/vector.h"
#include "core/templates/list.h"
#include "core/object/m_object.h"

class String;
class Variant;

class ConfigFile : public RefCounted {
    CLASS(ConfigFile , RefCounted);

public:
	ConfigFile();
	 ~ConfigFile();
public:

    void set_value(const String &section, const String &key, const Variant &value);
	std::variant<int, double, String> get_value(const String& section, const String& key, const Variant& p_default) const;
	String get_value(const String& key) const;
    void set_value(const String& key, const Variant& value);
    bool has_section(const String& section) const;
    bool has_section_key(const String& section, const String& key) const;
    void get_sections(List<String>& sections) const;
    void erase_section(const String& section);
    void get_section_keys(const String& section,List<String>& keys) const;
    void save(const String& path);
    void erase_section_key(const String& section, const String& key);
    bool load(const String& path);
    bool parse(const String& data);
    
    
protected:
	void _bind_methods() {}

private:
	String filename;
	std::unordered_map<std::string , std::string> data;
};

#endif /* CONFIG_FILE_H */ 
