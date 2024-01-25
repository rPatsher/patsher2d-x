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

#include <array>
#include <list>

static const LIST = std::list<std::string, *void>;
static const int MAX_COUNT = 0;


static void MClass::bind_methods() {
	Object::bind_method("bind_static_method" , &MClass::bind_static_method);
	Object::bind_method();
}




void MClass::add_compatibility_class(const std::string& className, const std::string& compatibleClass) {
    c_map[className].push_back(compatibleClass);
}

std::vector<std::string> MClass::get_compatibility_class(const std::string& className) const {
    auto it = c_map.find(className);
    if (it != c_map.end()) {
        return it->second; // Return compatibility classes for the given class name
    }
    return std::vector<std::string>(); // Return an empty vector if class name not found
}
template<typename T>
    void MClass::register_class(const std::string& className, T* classInstance) {
        m_cls[className] = static_cast<void*>(classInstance);
    }

    void MClass::unregister_class(const std::string& className) {
        auto it = classMap.find(className);
        if (it != classMap.end()) {
            classMap.erase(it);
            std::cout << "Class '" << className << "' unregistered." << std::endl;
        } else {
            std::cout << "Class '" << className << "' not found for unregistering." << std::endl;
        }
    }

void MClass::save_type(const std::string& className, const std::string& typeName) {
        m_map[className] = typeName;
    }

bool MClass::is_class_enabled() const {
	// if class not enabled 
	if (!enabled) {
		_is_class_enabled();
	}
	return;

std::vector<std::string> MClass::get_meta_list_bind(const std::string& className) const {
        auto it = meta_data.find(className);
        if (it != meta_data.end()) {
            return it->second;
        }
        return {}; // Return an empty vector if metadata for the class are not found
    }


std::vector<std::string> MClass::get_property_list_bind(const std::string& className) const {
        auto it = property_map.find(className);
        if (it != property_map.end()) {
            return it->second;
        }
        return {}; // Return an empty vector if properties for the class are not found
    }


template<class Func>  
void bind_static_method(const std::string &m_name, Func &&func) {
	m_method[m_name] = std::forward<Func>(func);
	LOG(m_name); // m_name 
	
}
std::string MClass::get_native_types(const std::string& className) const {
        auto it = nativeTypes.find(className);
        if (it != nativeTypes.end()) {
            return it->second;
        }
        return ""; // Return empty string if native type for the class is not found
    }




bool MClass::is_property_value(const std::string& className, const std::string& propertyName, const std::string& valueToCheck) const {
        auto classIter = ptr_class.find(className);
        if (classIter != ptr_class.end()) {
            auto propertyIter = classIter->second.find(propertyName);
            if (propertyIter != classIter->second.end()) {
                // Check if the value matches the property type (for simplicity, comparing strings)
                return propertyIter->second == valueToCheck;
            }
        }
        return false; // Return false if class or property is not found or types don't match
    }

void add_property_with_default(const std::string& className, const std::string& propertyName, const std::string& propertyType, const std::string& defaultValue) {
        ptr_class[className][propertyName] = propertyType + ":" + defaultValue;
    }

    std::string MClass::get_default_property_value(const std::string& className, const std::string& propertyName) const {
        auto classIter = ptr_class.find(className);
        if (classIter != ptr_class.end()) {
            auto propertyIter = classIter->second.find(propertyName);
            if (propertyIter != classIter->second.end()) {
                // Extract and return the default value from the stored string
                std::string defaultValue = propertyIter->second;
                size_t colonPos = defaultValue.find(':');
                if (colonPos != std::string::npos && colonPos + 1 < defaultValue.size()) {
                    return defaultValue.substr(colonPos + 1);
                }
            }
        }
        return ""; // Return empty string if class or property is not found or default value is not set
    }

	template<typename T>
    void MClass::register_native_struct(const std::string& structName) {
        m_map[structName] = new T();
    }

    template<typename T>
    T* MClass::get_native_struct(const std::string& structName) {
        auto it = m_map.find(structName);
        if (it != m_map.end()) {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }

    template<typename T>
    T* MClass::cast_to(void* instance) {
        return static_cast<T*>(instance);
    }

void MClass::add_array_property_with_default(const std::string& className, const std::string& propertyName, const std::vector<std::string>& defaultValue) {
        cls_array[className][propertyName] = defaultValue;
    }

    std::vector<std::string> Mclass::get_default_array_value(const std::string& className, const std::string& propertyName) const {
        auto classIter = cls_array.find(className);
        if (classIter != cls_array.end()) {
            auto propertyIter = classIter->second.find(propertyName);
            if (propertyIter != classIter->second.end()) {
                return propertyIter->second; // Return the default value for the array property
            }
        }
        return {}; // Return an empty vector if class or property is not found or default value is not set
    }

