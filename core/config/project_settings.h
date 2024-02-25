/**
 * MIT License

Copyright (c) 2024/2025 rPatsher

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

#include <cstring>
#include <cstdlib>

#include "core/config/engine.h"
#include "core/error/error_list.h"
#include "core/object/m_class.h"
#include "core/templates/list.h"
#include "core/templates/vector.h"


class Array;
class FileAccess
class DirAccess;
class Dictionary;


template <typename T>
class TypedArray;



class ProjectSettings : public Object {
    CLASS(ProjectSettings , Object);
public:
	static const int CONFIG_VERSION = 5;

	void set_setting(const String &p_setting, const Variant &p_value);
	Variant get_setting(const String &p_setting, const Variant &p_default_value = Variant()) const;
	TypedArray<Dictionary> get_global_class_list();
	void store_global_class_list(const Array &p_classes);
	String get_global_class_list_path() const;

	bool has_setting(String p_var) const;
	String localize_path(const String &p_path) const;
	String globalize_path(const String &p_path) const;

	void set_initial_value(const String &p_name, const Variant &p_value);
	void set_as_basic(const String &p_name, bool p_basic);
	void set_as_internal(const String &p_name, bool p_internal);
	void set_restart_if_changed(const String &p_name, bool p_restart);
	void set_ignore_value_in_docs(const String &p_name, bool p_ignore);
	bool get_ignore_value_in_docs(const String &p_name) const;
	void add_hidden_prefix(const String &p_prefix);

	String get_project_data_dir_name() const;
	String get_project_data_path() const;
	String get_resource_path() const;
	String get_imported_files_path() const;

	static ProjectSettings *get_singleton();

	void clear(const String &p_name);
	int get_order(const String &p_name) const;
	void set_order(const String &p_name, int p_order);
	void set_builtin_order(const String &p_name);
	bool is_builtin_setting(const String &p_name) const;

	Error setup(const String &p_path, const String &p_main_pack, bool p_upwards = false, bool p_ignore_override = false);
    

};



#endif // 