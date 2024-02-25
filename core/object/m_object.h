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
class Dictionary;

#include "core/templates/map.h"
#include "core/templates/list.h"
#include "core/object/callback_func.h"
#include "core/templates/vector.h"
#include "core/templates/hash_map.h"
#include "core/templates/hash_set.h"
#include "core/variant/signals.h"

#include <algorithm> 
#include <functional>
#include <memory>



struct PropertyInfo {
    Map<String, String> attributes;
    Vector<String> amenities;
    double price;
    
    PropertyInfo();
    ~PropertyInfo();

    PropertyInfo(const Map<String, String>& attributes,
                 const Vector <String>& amenities,
                 double price);

    // Getter for attributes
    String get(const String& key) const;

    // Setter for attributes
    void set(const String& key, const String& value);

    // Find function for amenities
    bool find(const String& amenity) const;

    // End function for amenities (returns an iterator to the end)
    Vector<String>::const_iterator end() const;
    
    Vector<PropertyInfo> get_property_list();
   
    void insert(const String& amenity);

    // Function to erase an amenity
    void erase(const String& amenity);


    PropertyInfo::PropertyInfo(const Map<String, String>& attributes,
                           const Vector <String>& amenities,
                           double price)
    : attributes(attributes), amenities(amenities), price(price) {}

String PropertyInfo::get(const String& key) const {
    auto it = attributes.find(key);
    return (it != attributes.end()) ? it->second : "";
}

void PropertyInfo::set(const String& key, const String& value) {
    attributes[key] = value;
}

bool PropertyInfo::find(const String& amenity) const {
    return std::find(amenities.begin(), amenities.end(), amenity) != amenities.end();
}

Vector<String>::const_iterator PropertyInfo::end() const {
    return amenities.end();
}

void PropertyInfo::insert(const String& amenity) {
    amenities.push_back(amenity);
}

void PropertyInfo::erase(const String& amenity) {
    auto it = std::find(amenities.begin(), amenities.end(), amenity);
    if (it != amenities.end()) {
        amenities.erase(it);
    }
}


};

struct MethodInfo {
	String name;
	PropertyInfo return_val;
	uint32_t flags = METHOD_FLAGS_DEFAULT;
	int id = 0;
	List<PropertyInfo> arguments;
	Vector<Variant> default_arguments;
	int return_val_metadata = 0;
	Vector<int> arguments_metadata;
};


#define CLASS(class_name, base_class_name)                                      \
private:																				\
		void operator=(const class_name &p_rval) {}									\
		friend class ::Class;								 						\
public:																				\
	typedef m_class self_type; 														\
public:                                                                            \
    static const char* get_class_name_static() { return #class_name; }              \
    virtual const char* get_class_name() const { return get_class_name_static(); } \
    static Object* get_class_ptr_static() { return _create(); }                   \
    static Object* get_class_static() { return _create(); }                       \
    static const Vector<String>& get_inheritance_list_static() {           \
        static Vector<String> inheritance_list = { #base_class_name };     \
        return inheritance_list;                                                   \
    }                                                                               \
    static bool is_class(const char* class_name) {                                  \
        return (strcmp(class_name, #class_name) == 0) || is_base_class(class_name); \
    }                                                                               \
    static bool is_class_ptr(const Object* obj) {                                 \
        return dynamic_cast<const class_name*>(obj) != nullptr;                     \
    }                                                                               \
    static const Vector<String>& get_valid_parents_static() {             \
        static Vector<String> valid_parents = { #base_class_name };        \
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
    Object(); 
    ~Object(); 
    int get(const String& key) const;
    void set(const String& key, int value) const;
    String get_property(const String& key) const;
    Vector<String> get_property_array(const String& key) const;
    template <typename Callable> decltype(auto) get_property_call(const String& key, Callable&& func) const;
    String getset(const String& key, const String& value = "");
    void setget(const String& key, const String& value);
    String get_class_name() const;
    Map<String, String> get_from_property_map() const;
    void get_obj_insert(const String& objKey, const Object& objToInsert);
    Map<String, Object> get_obj_map(const String& objKey) const;
    size_t find(const String& substring) const;
    size_t rfind(const String& substring) const;
    bool is_null() const;
    bool is_valid() const;
    template <typename T>
    T cast_to(const String& key) const;
    template <typename... Args>
    void connect(const String& key, Signal<Args...>& signal, const typename Signal<Args...>::Slot& slot) {
        signal.connect(key, this, slot);
    }
    template <typename... Args>
    void disconnect(const String& key, Signal<Args...>& signal) {
        signal.disconnect(key, this);
    }
    template <typename T, typename... Args>
    static T* instantiate(Args&&... args) {
        return new T(std::forward<Args>(args)...);
    }
    void* allocate_memory(size_t size);   
    void deallocate_memory(void* ptr);   
    void copy_data_from(const Object& other);
    template <typename T>
    T static_cast_from(const Object& obj);
    static size_t get_static_memory();
    int get_var(const String& varName) const;
    void set_var(const String& varName, int value) const;
    int get_obj_max_property(const String& objKey, const String& propertyKey) const;
    int get_obj_min_property(const String& objKey, const String& propertyKey) const;
    static Object* get_static_ptr();
    static void set_static_ptr(Object* ptr);
    int getv() const;
    void setv(int value) const;
    Vector<String> get_property_listv() const;
    int get_indexed_bind(size_t index) const;
    void set_indexed_bind(size_t index, int value) const;
    void call_bind(const String& method_name) const;
    void initialize_classv(const Vector <String>& properties);
    bool property_can_revert(const String& key) const;
    int property_get_revert(const String& key) const;
    void zero_fill_memory(size_t size);
    void set_memory_value(size_t offset, int value);
    int get_memory_value(size_t offset) const; 
    
    template <class T>
	static T *cast_to(Object *p_object) {
		return dynamic_cast<T *>(p_object);
	}

	template <class T>
	static const T *cast_to(const Object *p_object) {
		return dynamic_cast<const T *>(p_object);
	}
    
    static void get_inheritance_list_static(List<String> *p_inheritance_list) { p_inheritance_list->push_back("Object"); }

	static String get_class_static() { return "Object"; }
	static String get_parent_class_static() { return String(); }
	

protected:
    friend class RefCounted;
    friend class Class;

private:
	Map<String, int> dataMap;
    Map<String, String> propertyMap;
    Map<String, Vector<String>> propertyArrayMap;
    Map<String, std::function<int(const Object&)>> methodBindings;
    Map<String, Object> objectMap;
    std::unique_ptr<char[]> dynamicMemory;
    Map<String, int> variableMap;
    static Object* staticPointer;
};




#endif // M_OBJECT_H
