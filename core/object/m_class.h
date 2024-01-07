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



#include <map>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <assert.h>


#include "core/typedefs.h"
#include "core/object/ref_counted.h"
#include "core/templates/hash_map.h"
#include "core/templates/list.h"
#include "core/templates/map.h"
#include "core/error/error_list.h"
#include "core/error/error_macros.h"
#include "core/string/string.h"

#include "core/templates/vector.h"
#include "thirdparty/logger/src/logger.h"
#include "thirdparty/logger/src/loggerconf.h"


#define DEBUG_TOOLS 



class PropertyUtils;

struct MethodInfo {
    std::string name;
    uint32_t flags;
    int id = 0;
    Ref<std::list<PropertyUtils>> args;
    std::vector<int> meta_data;
    Map<MethodInfo, void*> map;

    int get_argument_meta(int p_arg) const { 
        if (p_arg == -1) {
            return;
        }
        return meta_data.size() > p_arg ? meta_data[p_arg] : 0;
    }
    inline bool operator==(const MethodInfo &p_method) const { return id == p_method.id && name == p_method.name; }
    inline bool operator<(const MethodInfo &p_method) const { return id == p_method.id ? (name < p_method.name) : (id < p_method.id); }

    MethodInfo(const std::string& p_name) { name = p_name; }
    template <class VarArgs>
    MethodInfo(const PropertyUtils& p_args , const std::string& p_name, VarArgs p_prms) {
        args = p_args;
        name = p_name;
        _push_params(p_prms...);
    }
    MethodInfo(const PropertyUtils& p_args , const std::string& p_name) {
        name = p_name;
    }

    template <typename VarArgs>
    MethodInfo(const std::string& p_name , VarArgs p_prms) {
        name  = p_prms;
        _push_params(p_prms...);
    }

    void _push_params(const PropertyUtils &p_param) {
		args->push_back(p_param);
	}

};

class MClass {


private: 
    Map<std::string , std::string> m_map;
    Map<std::string, std::map<std::string, std::string>> ptr_class; 
    Map<std::string, std::map<std::string, std::vector<std::string>>> array_class; // Map of class array properties and default values
    Map<std::string, std::vector<std::string>> p_property;
    Map<std::string, std::map<std::string, std::vector<std::string>>> mcls_ptr; // Map of class array properties and default values
    Map<std::string, void*> m_cls;
    Map<std::string , std::map<std::string, int>> p_dir;
    Map<std::string , std::vector<std::string>> m_items;
    static MClass* m_sign;
public:


    static MClass* get_signleton()  {
        if (!m_sign) {
            m_sign = nullptr;
        }
        return m_sign;
        
    }
    enum APIType {
		API_CORE,
		API_EDITOR,
		API_EXTENSION,
		API_EDITOR_EXTENSION,
		API_NONE
	};

#define MCLASS_API

#define MCLASS(m_class , m_inshit) \
private: \
    void operator=(const m_class eval) {} \
    friend class MClass; \
public: \ 
    static void get_mclass() {} \
    std::string get_static_mclass() { \
        return m_class; \
    } \
    static int get_index_value() { \
        static int* ptr; \
        return ptr; \
    } \
    static void set_data_ptr() { \ 
        const std::vector<std::string>* p_vec; \
        p_vec->push_back(m_class); \
        p_vec->push_back(m_inshit); \
    } \
    static std::vector<std::string> get_data_ptr() { \
        return p_vec; \
    } \
    m_inshit::get_class_static_ptr() \
    std::vector<std::string> get_class_static_ptr() { \
    return p_vec; \
    } \ 
    static std::string get_saved_class() { return #m_class; } \
    m_inshit::get_class_name() \
    std::string get_class_name(const std::string& p_str) { \
        get_class_name(m_class); \
    }\
    template <typename T> \
        T* get_extension_class() const { \
            return dynamic_cast<T*>(this); \
        } \
    int get_dictionary_index_value(const std::string& key) const { \
            auto keyIter = p_dir[#m_class].find(key); \
            if (keyIter != p_dir[#m_class].end()) { \
                return keyIter->second; \
            } \
            return 0; \
            m_inshit::get_ptr() const {} \
            m_inshit* get_ptr() const { \
                return static_cast<m_inshit*>(this);\
            } \
        } /

#define OBJ_SAVE_TYPE(m_class) \
    ::MClass::save_type(#m_class, #m_class);
public: 
    void add_property(const std::string& m_class, const std::string& name, const std::string& value);
    std::string get_property(const std::string& m_class, const std::string& name) const;

    Map<std::string, std::string> get_class_properties(const std::string& m_class) const;
    void add_dictionary_value(const std::string& className, const std::string& key, int value);
    int get_dictionary_index_value(const std::string& className, const std::string& key) const;

    void add_array_property_with_default(const std::string& className, const std::string& propertyName, const std::vector<std::string>& defaultValue);
    std::string get_default_property_value(const std::string& className, const std::string& propertyName) const;

    bool is_class_enabled() const;
public:
    struct MethodDef {
        String name;
        Vector<String> p_args;
        MethodDef() {}
        MethodDef(const char* s) :
            name(s) {}
        MethodDef(const String &p_name)
            {}

    };
    struct MClassInfo {
        APIType api = API_NONE;
        MClassInfo* ptr = nullptr;
        void* class_ptr = nullptr;

        bool disabled = false;
		bool exposed = false;
		bool reloadable = false;
		bool is_virtual = false;

        List<MethodDef , MClassInfo>* p_ref;
        List<String, Vector<void*>>* vec;
        Vector<PropertyUtils> ptr;

        MClassInfo() {}
        ~MClassInfo() {}




    };


    struct PropertySetGet {
        int index;
        String setter;
        String getter;
    };

    void save_type(const std::string& className, const std::string& typeName);



    template<typename T>
    void register_class(bool p_bool =false) {
        MClassInfo* it = T::get_class();
        it->exposed = true;
        it->is_virtual = p_bool;
        it->api = NULL;
    }

    template<typename T>
    Ref<T>* get_class(const std::string& name) {
        auto it = m_cls.find(name);
        if (it != m_cls.end()) {
            return static_cast<Ref<T>*>(it->second);
        }
        return nullptr;
    }


#define ADD_PROPERTY(m_type , m_name , m_method) \
    MClass::add_property(m_type , m_name , m_method) 

#define MCLASSDB(m_class) \
    if (MClass::is_class_enabled) { \
        ::MClass::register_class<m_class>(true); \
    }
#define BIND_ENUM(type, enumValue) \
    type::enumValue



public:
    MClass() {}
    ~MClass() {}

protected:
    friend class Object;
};




#endif // 