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

#include "m_class.h"

#include "core/templates/map.h"
#include "core/templates/hash_map.h"
#include "core/templates/hash_set.h"
#include "core/templates/vector.h"
#include "core/object/m_object.h"


#include <unordered_map>
#include <unordered_set>
#include <typeindex>


static void Class::add_property_group(const String& p_class, const String& p_name, const String& p_prefix = "", int p_indent_depth = 0) {
        auto class_it = class_registry().find(p_class);
        if (class_it != class_registry().end()) {
            auto& property_groups = property_group_registry()[p_class];
            property_groups.emplace_back(p_name, p_prefix, p_indent_depth);
            ERR_PRINT("Property group added for class\n");
        } else {
            ERR_PRINT("Class not registered\n");
        }

}
    
static String Class::get_property_getter(const String& p_class, const String& p_property, bool* r_is_valid = nullptr) {
        auto class_it = class_registry().find(p_class);
        if (class_it != class_registry().end()) {
            auto& properties = property_registry()[p_class];
            auto property_it = std::find_if(properties.begin(), properties.end(),
                [&p_property](const Property& property) {
                    return property.pinfo.get_name() == p_property;
                });

            if (property_it != properties.end()) {
                if (r_is_valid) {
                    *r_is_valid = true;
                }
                return property_it->getter;
            } else {
                if (r_is_valid) {
                    *r_is_valid = false;
                }
                ERR_PRINT("Property not found in class\n", p_class);
            }
        } else {
            if (r_is_valid) {
                *r_is_valid = false;
            }
            ERR_PRINT("Class not registered\n" , p_class);
        }

        return String(); 
    }
    
static String Clsss::get_property_setter(const String& p_class, const String& p_property, bool* r_is_valid = nullptr) {
        auto class_it = class_registry().find(p_class);
        if (class_it != class_registry().end()) {
            auto& properties = property_registry()[p_class];
            auto property_it = std::find_if(properties.begin(), properties.end(),
                [&p_property](const Property& property) {
                    return property.pinfo.get_name() == p_property;
                });

            if (property_it != properties.end()) {
                if (r_is_valid) {
                    *r_is_valid = true;
                }
                return property_it->setter;
            } else {
                if (r_is_valid) {
                    *r_is_valid = false;
                }
                ERR_PRINT("Property not found in class\n", p_class);
            }
        } else {
            if (r_is_valid) {
                *r_is_valid = false;
            }
            ERR_PRINT("Class not registered\n" , p_class);
        }

        return String(); 
    }


static void Class::bind_integer_constant(const String& p_class, const String& p_enum, const String& p_name, int64_t p_constant, bool p_is_bitfield = false) { 
        String full_enum_name = p_enum.empty() ? p_name : (p_enum + "::" + p_name);
        IntegerConstant constant_info{full_enum_name, p_constant, p_is_bitfield};
        integer_constant_registry()[p_class].push_back(constant_info);
        ERR_PRINT("Integer constant bound for class\n");
}

static void Class::get_integer_constant_list(const String& p_class, List<String>* p_constants, bool p_no_inheritance = false) {
	auto& constants = integer_constant_registry()[p_class];
	for (const auto& constant : constants) {
            p_constants->push_back(constant.name);
        }
        if (!p_no_inheritance) {
            const auto& class_info = class_registry()[p_class];
            for (const auto& base_class : class_info.base_classes) {
                get_integer_constant_list(base_class, p_constants, false);
            }
        }
}

static int64_t Class::get_integer_constant(const String& p_class, const String& p_name, bool* p_success = nullptr) {
        auto& constants = integer_constant_registry()[p_class];
        for (const auto& constant : constants) {
            if (constant.name == p_name) {
                if (p_success) {
                    *p_success = true;
                }
                return constant.value;
            }
        }
        if (p_success) {
            *p_success = false;
        }
        return 0; 
}

static bool Class::has_integer_constant(const String& p_class, const String& p_name, bool p_no_inheritance = false) {
        auto& constants = integer_constant_registry()[p_class];
        for (const auto& constant : constants) {
            if (constant.name == p_name) {
                return true;
            }
        }
        if (!p_no_inheritance) {
            const auto& class_info = class_registry()[p_class];
            for (const auto& base_class : class_info.base_classes) {
                if (has_integer_constant(base_class, p_name, false)) {
                    return true;
                }
            }
        }
        return false;
}

static bool Class::is_class_enabled(const String& p_class) {
        return class_enabled_registry().count(p_class) > 0 && class_enabled_registry()[p_class];

}

static void Class::set_class_enabled(const String& p_class, bool p_enabled) {
        class_enabled_registry()[p_class] = p_enabled;
}

static void Class::cleanup_defaults() {}

static void Class::cleanup() {
	integer_constant_registry().clear();
    class_enabled_registry().clear();
  }

static void Class::add_resource_base_extension(const String& p_extension, const String& p_class) {
    	resource_extension_registry()[p_extension] = p_class;
        ERR_WARN("Resource base extension added\n");
    }

static void Class::register_native_struct(const String& p_name, const String& p_code, uint64_t p_current_size) {
        NativeStructInfo native_struct_info{p_code, p_current_size};
        native_struct_registry()[p_name] = native_struct_info;
        ERR_INFO("Native struct registered\n");
    }

static void Class::get_extensions_for_type(const String& p_class, List<String>* p_extensions) {
        if (resource_extension_registry().count(p_class) > 0) {
            p_extensions->push_back(resource_extension_registry()[p_class]);
        }

}

static void add_virtual_method(const String& p_class, const MethodInfo& p_method, bool p_virtual = true, const Vector<String>& p_arg_names = Vector<String>(), bool p_object_core = false) {
        auto& methods = method_registry()[p_class];
        methods.emplace_back(p_method.get_name(), p_method, false);
}


static Vector<uint64_t>Class::get_method_compatibility_hashes(const String& p_class, const String& p_name) {
        Vector<uint64_t> compatibility_hashes;
        auto class_it = class_registry().find(p_class);
        if (class_it != class_registry().end()) {
            auto& methods = method_registry()[p_class];
            for (const auto& method : methods) {
                if (method.method_name == p_name) {
                    compatibility_hashes.push_back(method.info.get_hash());
                }
            }
            // Check inherited methods if needed
            if (class_it->second.base_classes.size() > 0) {
                for (const auto& base_class : class_it->second.base_classes) {
                    auto base_hashes = get_method_compatibility_hashes(base_class, p_name);
                    compatibility_hashes.insert(compatibility_hashes.end(), base_hashes.begin(), base_hashes.end());
                }
            }
        } else {
            ERR_WARN("Class not registered\n");
        }

        return compatibility_hashes;
}

static bool Class::get_method_info(const String& p_class, const String& p_method, MethodInfo* r_info, bool p_no_inheritance = false, bool p_exclude_from_properties = false) {
        auto class_it = class_registry().find(p_class);
        if (class_it != class_registry().end()) {
            auto& methods = method_registry()[p_class];
            auto method_it = std::find_if(methods.begin(), methods.end(),
                [&p_method](const MethodDefinition& method) {
                    return method.method_name == p_method;
                });

            if (method_it != methods.end()) {
                // Exclude properties if needed
                if (p_exclude_from_properties && method_it->is_property) {
                    std::cout << "Error: Method " << p_method << " is a property and excluded." << std::endl;
                    return false;
                }

                if (r_info) {
                    *r_info = method_it->info;
                }
                return true;
            } else if (!p_no_inheritance) {
                // Check inherited methods if inheritance is allowed
                for (const auto& base_class : class_it->second.base_classes) {
                    if (get_method_info(base_class, p_method, r_info, p_no_inheritance, p_exclude_from_properties)) {
                        return true;
                    }
                }
            }
            std::cout << "Error: Method " << p_method << " not found in class " << p_class << std::endl;
            return false;
        } else {
            std::cout << "Error: Class " << p_class << " not registered." << std::endl;
            return false;
        }
}

static bool Class::has_method(const String& p_class, const String& p_method, bool p_no_inheritance = false) {
        auto class_it = class_registry().find(p_class);
        if (class_it != class_registry().end()) {
            auto& methods = method_registry()[p_class];
            auto method_it = std::find_if(methods.begin(), methods.end(),
                [&p_method](const MethodDefinition& method) {
                    return method.method_name == p_method;
                });

            if (method_it != methods.end()) {
                return true;
            } else if (!p_no_inheritance) {
                // Check inherited methods if inheritance is allowed
                for (const auto& base_class : class_it->second.base_classes) {
                    if (has_method(base_class, p_method, p_no_inheritance)) {
                        return true;
                    }
                }
            }
            return false;
        } else {
            ERR_PRINT("class not registered\n");
            return false;
        }
    }

    static void Class::get_method_list(const String& p_class, List<MethodInfo>* p_methods, bool p_no_inheritance = false, bool p_exclude_from_properties = false) {
        auto class_it = class_registry().find(p_class);
        if (class_it != class_registry().end()) {
            auto& methods = method_registry()[p_class];
            for (const auto& method : methods) {
                if (p_exclude_from_properties && method.is_property) {
                    continue;
                }
                p_methods->push_back(method.info);
            }
            if (!p_no_inheritance) {
                for (const auto& base_class : class_it->second.base_classes) {
                    get_method_list(base_class, p_methods, p_no_inheritance, p_exclude_from_properties);
                }
            }
        } else {
            ERR_PRINT("CLASS NOT REGISTERED TRY AGAIN\n");
        }
}

static void Class::get_direct_inheriters_from_class(const String& p_class, Vector<String>* p_classes) {
        std::unordered_set<String> direct_inheriters;

        for (const auto& entry : class_registry()) {
            if (is_direct_base_class(entry.first, p_class)) {
                direct_inheriters.insert(entry.first);
            }
        }

        p_classes->assign(direct_inheriters.begin(), direct_inheriters.end());
}