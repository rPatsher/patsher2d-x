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
#include "project_settings.h"



#include "core/os/os.h"
#include "core/io/file_access.h"
#include "core/io/dir_access.h"
#include "core/variant/variant.h"
#include "core/variant/array.h"
#include "core/object/class.h"
#include "core/string/ustring.h"


ProjectSettings *ProjectSettings::get_singleton() {
        return singleton;
}

String ProjectSettings::get_project_data_dir_name() const {
        return project_data_dir_name;
}

String ProjectSettings::get_project_data_path() const {
        return "res://" + get_project_data_dir_name();
}

String ProjectSettings::get_resource_path() const {
        return resource_path;
}

String ProjectSettings::get_imported_files_path() const {
        return get_project_data_path().path_join("imported");
}

void ProjectSettings::set_order(const String &p_name, int p_order) {
        props[p_name].order = p_order;
}

void ProjectSettings::set_builtin_order(const String &p_name) {
        if (props[p_name].order >= NO_BUILTIN_ORDER_BASE) {
                props[p_name].order = last_builtin_order++;
        }
}

bool ProjectSettings::is_builtin_setting(const String &p_name) const {
        return props[p_name];
}

void ProjectSettings::clear(const String &p_name) {
        props.erase(p_name);
}


const PackedStringArray ProjectSettings::get_unsupported_features(const PackedStringArray &p_project_features) {
        PackedStringArray unsupported_features;
        PackedStringArray supported_features;
        for (int i = 0; i < p_project_features.size(); i++) {
                if (!supported_features.has(p_project_features[i])) {
                        if (p_project_features[i].begins_with("OpenGL")) {
                                continue;
                        }
                        unsupported_features.append(p_project_features[i]);
                }
        }
        unsupported_features.sort();
        return unsupported_features;
}


bool ProjectSettings::is_using_datapack() const {
        return using_datapack;
}

bool ProjectSettings::is_project_loaded() const {
        return project_loaded;
}

bool ProjectSettings::_property_can_revert(const StringName &p_name) const {
        if (!props.has(p_name)) {
                return false;
        }

        return props[p_name].initial != props[p_name].variant;
}

bool ProjectSettings::_property_get_revert(const StringName &p_name, Variant &r_property) const {
        if (!props.has(p_name)) {
                return false;
        }
        r_property = props[p_name].initial.duplicate();

        return true;
}

void ProjectSettings::set_setting(const String &p_setting, const Variant &p_value) {
        set(p_setting, p_value);
}



