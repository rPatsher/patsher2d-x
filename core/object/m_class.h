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
#ifndef M_CLASS_H
#define M_CLASS_H


#include "core/templates/hash_map.h"
#include "core/templates/hash_set.h"
#include "core/object/m_object.h"
#include "core/object/ref_counted.h"
#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/string/ustring.h"
#include "core/templates/variant.h"
#include "core/error/error_macros.h"


class Array;
class Dictionary;


#include <functional>
#include <memory>
#include <unordered_map>


class MethodBind;

class Class {
public:
	struct PropertyInfo {
public:
	enum PropertyFlags {
		PROPERTY_USAGE_NONE = 0,
		PROPERTY_USAGE_STORAGE = 1 << 1,
		PROPERTY_USAGE_EDITOR = 1 << 2,
		PROPERTY_USAGE_INTERNAL = 1 << 3,
		PROPERTY_USAGE_CHECKABLE = 1 << 4,
		PROPERTY_USAGE_CHECKED = 1 << 5, 
		PROPERTY_USAGE_GROUP = 1 << 6, 
		PROPERTY_USAGE_CATEGORY = 1 << 7,
		PROPERTY_USAGE_SUBGROUP = 1 << 8,
		PROPERTY_USAGE_CLASS_IS_BITFIELD = 1 << 9,
		PROPERTY_USAGE_NO_INSTANCE_STATE = 1 << 10,
		PROPERTY_USAGE_RESTART_IF_CHANGED = 1 << 11,
		PROPERTY_USAGE_SCRIPT_VARIABLE = 1 << 12,
		PROPERTY_USAGE_STORE_IF_NULL = 1 << 13,
		PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED = 1 << 14,
		PROPERTY_USAGE_SCRIPT_DEFAULT_VALUE = 1 << 15, 
		PROPERTY_USAGE_CLASS_IS_ENUM = 1 << 16,
		PROPERTY_USAGE_NIL_IS_VARIANT = 1 << 17,
		PROPERTY_USAGE_ARRAY = 1 << 18, 
		PROPERTY_USAGE_ALWAYS_DUPLICATE = 1 << 19,
		PROPERTY_USAGE_NEVER_DUPLICATE = 1 << 20, 
		PROPERTY_USAGE_HIGH_END_GFX = 1 << 21,
		PROPERTY_USAGE_NODE_PATH_FROM_SCENE_ROOT = 1 << 22,
		PROPERTY_USAGE_RESOURCE_NOT_PERSISTENT = 1 << 23,
		PROPERTY_USAGE_KEYING_INCREMENTS = 1 << 24, 
		PROPERTY_USAGE_DEFERRED_SET_RESOURCE = 1 << 25, 
		PROPERTY_USAGE_EDITOR_INSTANTIATE_OBJECT = 1 << 26, 
		PROPERTY_USAGE_EDITOR_BASIC_SETTING = 1 << 27, 
		PROPERTY_USAGE_READ_ONLY = 1 << 28, 
		PROPERTY_USAGE_SECRET = 1 << 29, 
		PROPERTY_USAGE_DEFAULT = PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_EDITOR,
		PROPERTY_USAGE_NO_EDITOR = PROPERTY_USAGE_STORAGE,
};
public:
    String name;
    Type type;
    Variant default_value;  // Default value for the property
    PropertyFlags usage;   // Property usage flag

    // Constructor with a default value and usage flag
    PropertyInfo(const Variant& defaultVal, const VariantType& t, const String& n, PropertyUsage u = PropertyUsage::DEFAULT)
        : default_value(defaultVal), type(t), name(n), usage(u) {}

    PropertyInfo(const Type& t, const String& n, PropertyUsage u = PropertyUsage::DEFAULT)
        : type(t), name(n), usage(u) {}
};

public:
	struct MethodDefinition {
    using MethodFunction = std::function<void(void*)>;

    String method_name;
    MethodFunction method_function;

    MethodDefinition(const String& name, MethodFunction function)
        : method_name(name), method_function(function) {}
};

struct PropertySetGet {
    using GetterFunction = std::function<void*(void*)>;
    using SetterFunction = std::function<void(void*, void*)>;

    String property_name;
    GetterFunction getter_function;
    SetterFunction setter_function;

    PropertySetGet(const String& name, GetterFunction getter, SetterFunction setter)
        : property_name(name), getter_function(getter), setter_function(setter) {}
};
public:
	struct Property {
        PropertyInfo pinfo;
        String setter;
        String getter;
        int index;
        Variant default_value; 

        Property(const PropertyInfo& info, const String& set, const String& get, int idx)
            : pinfo(info), setter(set), getter(get), index(idx) {}
    };
    struct PropertySubgroup {
        String name;
        String prefix;
        int indent_depth;

        PropertySubgroup(const String& n, const String& pre, int depth)
            : name(n), prefix(pre), indent_depth(depth) {}
    };

    struct PropertyArrayCount {
        String label;
        String count_property;
        String count_setter;
        String count_getter;
        String array_element_prefix;
        uint32_t count_usage;

        PropertyArrayCount(const String& lbl, const String& countProp, const String& countSet,
                           const String& countGet, const String& elemPrefix, uint32_t countUsage)
            : label(lbl), count_property(countProp), count_setter(countSet),
              count_getter(countGet), array_element_prefix(elemPrefix), count_usage(countUsage) {}
    };
    
    using SignalRegistry = std::unordered_map<String, std::vector<MethodInfo>>;

    static SignalRegistry& signal_registry() {
        static SignalRegistry registry;
        return registry;
    }

    using PropertySubgroupRegistry = std::unordered_map<String, std::vector<PropertySubgroup>>;
    using PropertyArrayCountRegistry = std::unordered_map<String, std::vector<PropertyArrayCount>>;
    using PropertyRegistry = std::unordered_map<sString, Vector<Property>>;
    static PropertyRegistry& property_registry() {
        static PropertyRegistry registry;
        return registry;
    }
    

public:
	template <typename T>
    static void register_class(const String& class_name) {
        class_registry()[class_name] = &create_instance<T>;
    }
    template <typename T>
    static T* create(const String& class_name) {
        auto it = class_registry().find(class_name);
        if (it != class_registry().end()) {
            return static_cast<T*>(it->second());
        }
        return nullptr;
    }
    
    template <typename T>
    static void set_property(T* instance, const String& property_name, void* value) {
        auto class_name = typeid(T).name();
        auto properties = property_registry()[class_name];

        for (const auto& property : properties) {
            if (property.property_name == property_name) {
                property.setter_function(instance, value);
                return;
            }
        }
    } 
    template <typename T>
    static void* get_property(T* instance, const String& property_name) {
        auto class_name = typeid(T).name();
        auto properties = property_registry()[class_name];

        for (const auto& property : properties) {
            if (property.property_name == property_name) {
                return property.getter_function(instance);
            }
        }

        return nullptr;
    }
    static void get_class_list(List<String>* p_classes) {
        for (const auto& entry : class_registry()) {
            p_classes->push_back(entry.first);
        }
    }


public:
	void is_property_value(const String& p_class, const String& p_name, const String& p_value);
	static String get_property_setter(const String& p_class, const String& p_property, bool* r_is_valid = nullptr);
	static String get_property_getter(const String& p_class, const String& p_property, bool* r_is_valid = nullptr);
	static String get_property_type(const String& p_class, const String& p_property, bool* r_is_valid = nullptr);
	static void add_linked_property(const String& p_class, const String& p_property, const String& p_linked_property);
	static void add_property(const String& p_class, const PropertyInfo& p_pinfo, const String& p_setter, const String& p_getter, int p_index = -1);
	static void set_property_default_value(const String& p_class, const String& p_name, const Variant& p_default);
	static void add_property_subgroup(const String& p_class, const String& p_name,
	const String& p_prefix = "", int p_indent_depth = 0);
	static void add_signal(const String& p_class, const MethodInfo& p_signal);
	static bool has_method(const String& p_class, const String& p_method, bool p_no_inheritance = false);
	static void get_method_list(const String& p_class, List<MethodInfo>* p_methods, bool p_no_inheritance = false, bool p_exclude_from_properties = false);
	static bool get_method_info(const String& p_class, const String& p_method, MethodInfo* r_info, bool p_no_inheritance = false, bool p_exclude_from_properties = false);
	static MethodDefinition get_method_with_compatibility(const String& p_class, const String& p_name, uint64_t p_hash, bool* r_method_exists = nullptr, bool* r_is_deprecated = nullptr);
	static Vector<uint64_t> get_method_compatibility_hashes(const String& p_class, const String& p_name);
	static void add_virtual_method(const String& p_class, const MethodInfo& p_method, bool p_virtual = true, const Vector<String>& p_arg_names = Vector<String>(), bool p_object_core = false);
	
	
	static void bind_integer_constant(const String &p_class, const String &p_enum, const String &p_name, int64_t p_constant, bool p_is_bitfield = false);
	static void get_integer_constant_list(const String &p_class, List<String> *p_constants, bool p_no_inheritance = false);
	static int64_t get_integer_constant(const String &p_class, const String &p_name, bool *p_success = nullptr);
	static bool has_integer_constant(const String &p_class, const String &p_name, bool p_no_inheritance = false);
	
	static void set_class_enabled(const String &p_class, bool p_enable);
	static bool is_class_enabled(const String &p_class);
	static bool is_class_exposed(const String &p_class);
	static bool is_class_reloadable(const String &p_class);
	static void add_resource_base_extension(const String &p_extension, const String &p_class);
	
	get_native_struct_list(List<String> *r_names);
	static String get_native_struct_code(const String &p_name);
	static uint64_t get_native_struct_size(const String &p_name);
	
                                      
	
	
	template <typename N, typename M, typename... VarArgs>
static void bind_method(const String& p_class, N p_method_name, M p_method, VarArgs... p_args) {
    auto class_it = class_registry().find(p_class);
    if (class_it != class_registry().end()) {
        auto& methods = method_registry()[p_class];
        auto method_it = std::find_if(methods.begin(), methods.end(),
            [&p_method_name](const MethodDefinition& method) {
                return method.method_name == p_method_name;
            });
        if (method_it != methods.end()) {
            ERR_PRINT("Method already bound for class\n", p_class);
        } else {
            methods.emplace_back(p_method_name, std::bind(p_method, p_args...));
            ERR_PRINT("Method bound successfully for class\n" , p_class);
        }
    } else {
        ERR_PRINT("Class not registered\n" , p_class);
    }
}

template <typename N, typename M, typename... VarArgs>
void bind_static_method(const String& p_class, N p_method_name, M p_method, VarArgs... p_args) {
    auto class_it = class_registry().find(p_class);
    if (class_it != class_registry().end()) {
        auto& methods = method_registry()[p_class];
        auto method_it = std::find_if(methods.begin(), methods.end(),
            [&p_method_name](const MethodDefinition& method) {
                return method.method_name == p_method_name;
            });

        if (method_it != methods.end()) {
            ERR_PRINT("Static method already bound for class\n" , p_class);
        } else {
            methods.emplace_back(p_method_name, std::bind(p_method, p_args...));
            ERR_PRINT("Static method bound successfully for class\n" , p_class);
        }
    } else {
        ERR_PRINT("Class not registered\n" , p_class);
    }
}

// Utility to get member function traits
template <typename T>
struct member_function_traits;

template <typename R, typename C, typename... Args>
struct member_function_traits<R (C::*)(Args...)> {
    using return_type = R;
};

// Function to create method bind
template <typename M, typename... Args>
auto create_method_bind(M p_method, Args&&... args) {
    return std::bind(p_method, std::forward<Args>(args)...);
}

static bool class_exists(const String& p_class) {
        return class_registry().find(p_class) != class_registry().end();
    }

public:
	Class();
	~Class();
	
	
protected:
	friend class Object;
	friend void register_core_types();



private:
	Map<String , void*> mclass; // Map for store classes
	Map<String, String> properties;
	Map<String , String> m_map;
    Map<String, Vector<String>> property_map;
    Map<String, std::map<String, String>> ptr_class; 
    Map<String, std::map<String, Vector<String>>> array_class; // Map of class array properties and default values
    Map<String, Vector<String>> p_property;
    Map<String, std::map<String, Vector<String>>> mcls_ptr; // Map of class array properties and default values
    Map<String, void*> m_cls;
    Map<String, std::map<String, Vector<String>>> cls_array; // Map of class array properties and default values
    
    Map<String , std::map<String, int>> p_dir;
    Map<String, Vector<String>> p_res;
    Map<String, std::function<void()>> m_method;
    Map<String, std::shared_ptr<void>> m_obj; // Map to store object extension instances
	Map<String, Vector<String>> c_map; // Map to store compatibility classes
    Map<String , Vector<String>> m_items;
	
	List<String> global_class; 
private:
	using CreatorFunction = std::function<void*>;
    using MethodRegistry = std::unordered_map<String, std::vector<MethodDefinition>>;
    using PropertyRegistry = std::unordered_map<String, std::vector<PropertySetGet>>;

    static std::unordered_map<String, CreatorFunction>& class_registry() {
        static std::unordered_map<String, CreatorFunction> registry;
        return registry;
    }

    static MethodRegistry& method_registry() {
        static MethodRegistry registry;
        return registry;
    }

    static PropertyRegistry& property_registry() {
        static PropertyRegistry registry;
        return registry;
    }

    template <typename T>
    static void* create_instance() {
        return new T();
    }

}


#define BIND_ENUM_CONSTANT(m_constant) \
	::Class::bind_integer_constant(get_class_static(), __constant_get_enum_name(m_constant, #m_constant), #m_constant, m_constant);

#define BIND_BITFIELD_FLAG(m_constant) \
	::Class::bind_integer_constant(get_class_static(), __constant_get_bitfield_name(m_constant, #m_constant), #m_constant, m_constant, true);

#define BIND_CONSTANT(m_constant) \
	::Class::bind_integer_constant(get_class_static(), String(), #m_constant, m_constant);
	






#endif // 