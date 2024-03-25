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
#include "m_object.h"


#include "core/template/pair.h"
#include "core/variant/variant.h"
#include "core/variant/dictionary.h"
#include "core/variant/array.h"

#include <cstdlib>



Object::Object() {
    
}

Object::~Object() {

}

// Const version: Get the value for a given key
int Object::get(const String& key) const {
    auto it = dataMap.find(key);
    return (it != dataMap.end()) ? it->value : 0;
}

void Object::set(const String& key, int value) const {
    const_cast<std::map<String, int>&>(dataMap)[key] = value;
}

String Object::get_property(const String& key) const {
    auto it = propertyMap.find(key);
    return (it != propertyMap.end()) ? it->value : "";
}

Object::zero_fill_memory(size_t size) {
    if (dynamicMemory) {
        std::memset(dynamicMemory.get(), 0, size);
    }
}

void Object::set_memory_value(size_t offset, int value) {
    if (dynamicMemory) {
        int* memoryInt = reinterpret_cast<int*>(dynamicMemory.get() + offset);
        *memoryInt = value;
    }
}

int Object::get_memory_value(size_t offset) const {
    if (dynamicMemory) {
        const int* memoryInt = reinterpret_cast<const int*>(dynamicMemory.get() + offset);
        return *memoryInt;
    }
    return 0; 
}

std::vector<String> Object::get_property_array(const String& key) const {
    auto it = propertyArrayMap.find(key);
    return (it != propertyArrayMap.end()) ? it->value : std::vector<String>();
}

// Get and set properties with a single function call
String Object::getset(const String& key, const String& value) {
    if (!value.empty()) {
        // If value is provided, set the property and return the previous value
        auto it = propertyMap.find(key);
        String previousValue = (it != propertyMap.end()) ? it->value : "";
        propertyMap[key] = value;
        return previousValue;
    } else {
        // If no value is provided, get the current property value
        return get_property(key);
    }
}

void Object::setget(const String& key, const String& value) {
    // Set the property value
    propertyMap[key] = value;
}

// Get the class name from the property map
String Object::get_class_name() const {
    return get_property("class_name");
}

// Get a copy of the property map
std::map<String, String> Object::get_from_property_map() const {
    return propertyMap;
}

// Insert an object into the object map
void Object::get_obj_insert(const String& objKey, const Object& objToInsert) {
    objectMap[objKey] = objToInsert;
}

// Get a map of objects associated with a key
std::map<String, Object> Object::get_obj_map(const String& objKey) const {
    auto it = objectMap.find(objKey);
    return (it != objectMap.end()) ? std::map<String, Object>{{objKey, it->value}} : std::map<String, Object>();
}




Object::allocate_memory(size_t size) {
    dynamicMemory = std::make_unique<char[]>(size);
    return dynamicMemory.get();
}

void Object::deallocate_memory(void* ptr) {
    if (ptr == dynamicMemory.get()) {
        dynamicMemory.reset(); 
    }
}

// Memory-related function: Copy data from another Object
void Object::copy_data_from(const Object& other) {
    if (dynamicMemory && other.dynamicMemory) {
        std::memcpy(dynamicMemory.get(), other.dynamicMemory.get(), sizeof(char));
    }
}

Object::get_obj_max_property(const String& objKey, const String& propertyKey) const {
    auto it = objectMap.find(objKey);
    if (it != objectMap.end()) {
        const Object& obj = it->value;
        auto objIt = obj.dataMap.find(propertyKey);
        if (objIt != obj.dataMap.end()) {
            return objIt->value;
        }
    }
    return 0; 
}
int Object::get_obj_min_property(const String& objKey, const String& propertyKey) const {
    auto it = objectMap.find(objKey);
    if (it != objectMap.end()) {
        const Object& obj = it->value;
        auto objIt = obj.dataMap.find(propertyKey);
        if (objIt != obj.dataMap.end()) {
            return objIt->value;
        }
    }
    return 0;
}


size_t Object::find(const String& substring) const {
    String concatenatedData;
    for (const auto& entry : dataMap) {
        concatenatedData += std::to_string(entry.value);
    }
    return concatenatedData.find(substring);
}

size_t Object::rfind(const String& substring) const {
    String concatenatedData;
    for (const auto& entry : dataMap) {
        concatenatedData += std::to_string(entry.value);
    }
    return concatenatedData.rfind(substring);
}

bool Object::is_null() const {
    return dataMap.empty() && propertyMap.empty() && propertyArrayMap.empty() && objectMap.empty();
}

bool Object::is_valid() const {
    return !is_null();
}