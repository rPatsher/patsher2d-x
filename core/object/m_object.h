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


#ifndef M_OBJECT_H
#define M_OBJECT_H

class Callable;

#include "core/templates/map.h"
#include "core/object/callback_func.h"
#include "core/templates/vector.h"
#include "core/templates/hash_map.h"
#include "core/variant/signals.h"



#include <map>
#include <string>
#include <vector>
#include <functional>
#include <algorithm> // for std::max_element and std::min_element


struct PropertyInfo {
    std::map<std::string, std::string> attributes;
    std::vector<std::string> amenities;
    double price;
    
    PropertyInfo();
    ~PropertyInfo();

    PropertyInfo(const std::map<std::string, std::string>& attributes,
                 const std::vector<std::string>& amenities,
                 double price);

    // Getter for attributes
    std::string get(const std::string& key) const;

    // Setter for attributes
    void set(const std::string& key, const std::string& value);

    // Find function for amenities
    bool find(const std::string& amenity) const;

    // End function for amenities (returns an iterator to the end)
    std::vector<std::string>::const_iterator end() const;
    
    std::vector<PropertyInfo> get_property_list();
   
    void insert(const std::string& amenity);

    // Function to erase an amenity
    void erase(const std::string& amenity);


    PropertyInfo::PropertyInfo(const std::map<std::string, std::string>& attributes,
                           const std::vector<std::string>& amenities,
                           double price)
    : attributes(attributes), amenities(amenities), price(price) {}

std::string PropertyInfo::get(const std::string& key) const {
    auto it = attributes.find(key);
    return (it != attributes.end()) ? it->second : "";
}

void PropertyInfo::set(const std::string& key, const std::string& value) {
    attributes[key] = value;
}

bool PropertyInfo::find(const std::string& amenity) const {
    return std::find(amenities.begin(), amenities.end(), amenity) != amenities.end();
}

std::vector<std::string>::const_iterator PropertyInfo::end() const {
    return amenities.end();
}

void PropertyInfo::insert(const std::string& amenity) {
    amenities.push_back(amenity);
}

void PropertyInfo::erase(const std::string& amenity) {
    auto it = std::find(amenities.begin(), amenities.end(), amenity);
    if (it != amenities.end()) {
        amenities.erase(it);
    }
}


};



GCLASS_PROPERTY(property_name, default_value) \
private: \
    return_type property_name##_impl = default_value; \
public: \
    return_type get_##property_name() const { return property_name##_impl; } \
    void set_##property_name(return_type value) { property_name##_impl = value; }

#define GCLASS_METHOD(method_name, return_type, ...)                   \
public:                                                                 \
    return_type method_name(__VA_ARGS__) { return method_name##_impl(__VA_ARGS__); } \
private:                                                                \
    return_type method_name##_impl(__VA_ARGS__);


#define CLASS(class_name, base_class_name)                                      \
public:                                                                            \
    static const char* get_class_name_static() { return #class_name; }              \
    virtual const char* get_class_name() const { return get_class_name_static(); } \
    static Object* get_class_ptr_static() { return _create(); }                   \
    static Object* get_class_static() { return _create(); }                       \
    static const std::vector<std::string>& get_inheritance_list_static() {           \
        static std::vector<std::string> inheritance_list = { #base_class_name };     \
        return inheritance_list;                                                   \
    }                                                                               \
    static bool is_class(const char* class_name) {                                  \
        return (strcmp(class_name, #class_name) == 0) || is_base_class(class_name); \
    }                                                                               \
    static bool is_class_ptr(const Object* obj) {                                 \
        return dynamic_cast<const class_name*>(obj) != nullptr;                     \
    }                                                                               \
    static const std::vector<std::string>& get_valid_parents_static() {             \
        static std::vector<std::string> valid_parents = { #base_class_name };        \
        return valid_parents;                                                        \
    }                                                                               \
    static return_type get_set(return_type value) {                                \
        return _instance->get_set_impl(value);                                      \
    }                                                                               \
    static return_type set_get(return_type value) {                                \
        return _instance->set_get_impl(value);                                      \
    }                                                                               \
    static return_type setv(return_type value) {                                   \
        return _instance->setv_impl(value);                                         \
    }                                                                               \
    static return_type getv() {                                                  \
        return _instance->getv_impl();                                              \
    }                                                                               \
    static void* get_get_property_list() {                                       \
        return _instance->get_get_property_list_impl();                            \
    }                                                                               \
    static void* _get_get() {                                                    \
        return _instance->_get_get_impl();                                         \
    }                                                                               \
    static void* _get_method_bind() {                                            \
        return _instance->_get_method_bind_impl();                                 \
    }                                                                               \
                                                                                   \
    static Object* _create() { return new class_name; }                           \
                                                                                   \
    static void _bind_methods();                                                   \
                                                                                   \


class Object {
public:
    Object();  // Constructor
    ~Object(); // Destructor

    // Const versions of get and set functions
    int get(const std::string& key) const;
    void set(const std::string& key, int value) const;

    // Additional member functions
    std::string get_property(const std::string& key) const;
    std::vector<std::string> get_property_array(const std::string& key) const;
    template <typename Callable> decltype(auto) get_property_call(const std::string& key, Callable&& func) const;

    // Get and set properties with a single function call
    std::string getset(const std::string& key, const std::string& value = "");
    void setget(const std::string& key, const std::string& value);


    // Additional functions
    std::string get_class_name() const;
    std::map<std::string, std::string> get_from_property_map() const;

    // New functions
    void get_obj_insert(const std::string& objKey, const Object& objToInsert);
    std::map<std::string, Object> get_obj_map(const std::string& objKey) const;

    // String manipulation functions
    size_t find(const std::string& substring) const;
    size_t rfind(const std::string& substring) const;

    // Null and validity checks
    bool is_null() const;
    bool is_valid() const;

    // Type casting functions
    template <typename T>
    T cast_to(const std::string& key) const;

   // New function for connecting signals
    template <typename... Args>
    void connect(const std::string& key, Signal<Args...>& signal, const typename Signal<Args...>::Slot& slot) {
        signal.connect(key, this, slot);
    }

    // New function for disconnecting signals
    template <typename... Args>
    void disconnect(const std::string& key, Signal<Args...>& signal) {
        signal.disconnect(key, this);
    }

    // New function for instantiating objects dynamically
    template <typename T, typename... Args>
    static T* instantiate(Args&&... args) {
        return new T(std::forward<Args>(args)...);
    }

    void* allocate_memory(size_t size);    // Allocate dynamic memory
    void deallocate_memory(void* ptr);      // Deallocate dynamic memory
    void copy_data_from(const Object& other);  // Copy data from another Object


    template <typename T>
    T static_cast_from(const Object& obj);

    // New function for static memory information
    static size_t get_static_memory();

    // New functions for variables and static pointers
    int get_var(const std::string& varName) const;
    void set_var(const std::string& varName, int value) const;
    
    int get_obj_max_property(const std::string& objKey, const std::string& propertyKey) const;

    // New function to get the minimum property value in the object map
    int get_obj_min_property(const std::string& objKey, const std::string& propertyKey) const;

    static Object* get_static_ptr();
    static void set_static_ptr(Object* ptr);

    // New functions for v
    int getv() const;
    void setv(int value) const;
    std::vector<std::string> get_property_listv() const;

    // New functions for indexed bindings
    int get_indexed_bind(size_t index) const;
    void set_indexed_bind(size_t index, int value) const;

    // New functions
    void call_bind(const std::string& method_name) const;
    void initialize_classv(const std::vector<std::string>& properties);

    // New function for checking if a property can revert
    bool property_can_revert(const std::string& key) const;

    // New function for getting the revert value of a property
    int property_get_revert(const std::string& key) const;
   
    void zero_fill_memory(size_t size);      // Fill dynamic memory with zeros
    void set_memory_value(size_t offset, int value);  // Set a value at a specific offset in dynamic memory
    
    
    // Method binding functions
    template <typename Func>
    decltype(auto) bind_method(const std::string& method_name, Func&& func);

    template <typename ReturnType, typename... Args>
    decltype(auto) get_method(const std::string& method_name) const;
    
    
    int get_memory_value(size_t offset) const; // Get a value from a specific offset in dynamic memory

protected:
    friend class RefCounted;
    friend class MClass;
    friend class ClassDB;
    friend class ObjectDB;
    friend class Extension;

private:
    mutable std::map<std::string, int> dataMap; // Mutable to allow modification in const functions
    std::map<std::string, std::string> propertyMap;
    std::map<std::string, std::vector<std::string>> propertyArrayMap;
    std::map<std::string, std::function<int(const Object&)>> methodBindings;

    // New member variables for object insertion
    std::map<std::string, Object> objectMap;
   // Unique pointer to dynamically allocated memory
    std::unique_ptr<char[]> dynamicMemory;

    // New member variable for variables
    mutable std::map<std::string, int> variableMap;

    // New static pointer
    static Object* staticPointer;
};
// Template implementation for get_method, bind_method, and emit_signal
template <typename ReturnType, typename... Args>
decltype(auto) Object::get_method(const std::string& method_name) const {
    auto it = methodBindings.find(method_name);
    if (it != methodBindings.end()) {
        return it->second;
    } else {
        // Default return if the method is not found
        return [](const Object
        &) -> ReturnType { return ReturnType(); };
    }
    
}

template <typename Func>
decltype(auto) Object::bind_method(const std::string& method_name, Func&& func) {
    methodBindings[method_name] = std::forward<Func>(func);
}



#endif // M_OBJECT_H
