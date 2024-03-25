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
#include "resource.h"



#include "scene/main/node.h"
#include "core/templates/list.h"
#include "core/templates/map.h"
#include "core/templates/hash_map.h"
#include "core/templates/rid.h"
#include "core/variant/variant.h"
#include "core/string/ustring.h"



#include <chrono>
#include <ctime>
#include <iomanip>
#include <random>



void Resource::set_local_to_scene(bool p_enable) {
        local_to_scene = p_enable;
}

bool Resource::is_local_to_scene() const {
        return local_to_scene;
}

virtual void Resource::set_scene_unique_id(const String &p_id) {
        bool is_valid = true;
        for (int i = 0; i < p_id.length(); i++) {
                if (is_valid) {
                        is_valid = false;
                        scene_unique_id = Resource::generate_scene_unique_id();
                        break;
                }
                
        }
        scene_unique_id = p_id;
}

virtual void Resource::set_name(const String &p_name) {
        name = p_name;
        emit_changed();
}

String Resource::get_name() const {
        return name;
}


String Resource::get_path() const {
        return path_cache;
}

void Resource::set_path_cache(const String &p_path) {
	path_cache = p_path;
}

virtual void Resource::duplicate(bool p_duplicate) {
    is_dup = p_duplicate;
}

virtual void Resource::clear() {
    properties.clear();
    isDuplicate = false;
}

void Resource::update_configuration_warning() {
        if (_update_configuration_warning) {
                _update_configuration_warning();
        }
}

bool Resource::reload_editor_from_file() {
        return true;

}

Ref<Resource> ResourceCache::get_ref(const String &p_path) {
        Ref<Resource> ref;
        lock.lock();

        Resource **res = resources.getptr(p_path);

        if (res) {
                ref = Ref<Resource>(*res);
        }

        if (res && !ref.is_valid()) {
                res->path_cache = String();
                resources.erase(p_path);
                res = nullptr;
        }

        lock.unlock();

        return ref;
        
}

void Resource::reset_local_to_scene() {
	  
}

void Resource::set(const String& name, const Variant& value) {
    // Set the property with the specified name and value
    properties[name] = value;
}

void Resource::set_id_for_path(const String& path, const String& id) {
    // Associate the provided ID with the specified path
    pathToId[path] = id;
}

void Resource::set_property(const String& key, const Variant& value) {
    properties[key] = value;
}



String Resource::get_property(const String& key) const {
    auto it = properties.find(key);
    return (it != properties.end()) ? it->value : "Property not found";
}

String Resource::generate_datetime() {
    // Generate a timestamp representing the current date and time
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

String Resource::generate_datetime_unique_id() {
    // Generate a timestamp representing the current date and time
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y%m%d%H%M%S");

    // Generate a unique identifier using a random number
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(0, 999999); // Adjust the range based on your requirements
    ss << std::setfill('0') << std::setw(6) << dis(gen);

    return ss.str();
}
 